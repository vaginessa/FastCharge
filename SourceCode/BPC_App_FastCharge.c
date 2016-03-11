/*
***************************************************************************
**
** Copyright 2015 LETV, Inc. All rights reserved.
**
** LETV Proprietary Information.
** This document contains proprietary and confidential information and is
** tendered for information and evaluation purposes only; no copy or other
** use or dissemination by a third party can be made of this information
** without the express written permission of LETV.
**
***************************************************************************
*/

/*
***************************************************************************
** Filename:	BPC_App_FastCharge.c
** Author:      
** Date:        
** Description:	Define fast charge control main functions
***************************************************************************
**/


/* include other application header file */
#include "BPC_App_FastCharge.h"

/*******************************************************************************
** Global Variable define
********************************************************************************/
// message enable flag define
static uint8_t bem_msg_enable;
static uint8_t bhm_msg_enable;
static uint8_t brm_msg_enable;
static uint8_t bcp_msg_enable;
static uint8_t bro_msg_enable;
static uint8_t bcl_msg_enable;
static uint8_t bcs_msg_enable;
static uint8_t bst_msg_enable;
static uint8_t bsd_msg_enable;

// fast charger message receive flag

static uint8_t chm_msg_received;
static uint8_t crm_msg_received;
static uint8_t cml_msg_received;
static uint8_t cro_msg_received;
static uint8_t ccs_msg_received;
static uint8_t csd_msg_received;

// fast charger CAN signal

uint8_t SPN2560_ID_feedback_result;
uint8_t SPN2829_BMS_chging_pre_status;
uint8_t SPN2830_offcharger_pre_status;

// bem signal variable define
static uint8_t bem_crm_timeout;
static uint8_t bem_crm_pass_timeout;
static uint8_t bem_cml_timeout;
static uint8_t bem_cro_timeout;
static uint8_t bem_ccs_timeout;
static uint8_t bem_cst_timeout;
static uint8_t bem_csd_timeout;

static float32_t ccs_timer;
static uint8_t   fastchg_restart_needed;
void Initialize_FastChg(void)
{

}

void Process_FastChg_Management(float dt_ms, const char init)
{
	static enum_fast_chg_step next_step ;
	static enum_fast_chg_step last_step ;
	
	static float_32t step_tmr;
	
	if(TRUE == init)
	{  /* fast charge process management parameter initialize */
        step_tmr = 0.0f;
		next_step = FASTCHG_STEP_HANDSHAKE_WAIT_CHM;
		last_step = FASTCHG_STEP_CHARGE_DONE;
		
	}
	else
	{
		switch(next_step)
		{
			case FASTCHG_STEP_HANDSHAKE_WAIT_CHM:
			//TODO:  add fast charge parameter initialize
			
			if(TRUE == chm_msg_received)
			{
				bhm_msg_enable = TRUE;
				chm_msg_received = FALSE;
				next_step = FASTCHG_STEP_HANDSHAKE_WAIT_CRM;
			}
			else if(TRUE == crm_msg_received)
			{
				next_step = FASTCHG_STEP_HANDSHAKE_WAIT_CRM;
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr > HANDSHAKE_CHM_TIMEOUT)
				{
					bem_crm_timeout = TRUE;
					bhm_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					/* do nothing */
				}
			}
			
			break;
			
			case FASTCHG_STEP_HANDSHAKE_WAIT_CRM:
			bst_msg_enable = FALSE;
			if((TRUE == crm_msg_received)&&(0x00 == SPN2560_ID_feedback_result))
			{
				//TODO: clear all bem flag
				crm_msg_received = FALSE;
				bhm_msg_enable = FALSE;
				brm_msg_enable = TRUE;
				next_step = FASTCHG_STEP_HANDSHAKE_WAIT_CRM_AA;
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr > HANDSHAKE_CRM_TIMEOUT)
				{
					bem_crm_timeout = TRUE;
					brm_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					/* do nothing */
				}
			}
			break;
			
			case FASTCHG_STEP_HANDSHAKE_WAIT_CRM_AA:
			if((TRUE == crm_msg_received)&&(0xAA == SPN2560_ID_feedback_result))
			{
				crm_msg_received = FALSE;
				brm_msg_enable = FALSE;
				//TODO: initial BCP message
				bcp_msg_enable = TRUE;
				next_step = FASTCHG_STEP_CONFIG_WAIT_CTS_CML;
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr > HANDSHAKE_CRM_AA_TIMEOUT)
				{
					bem_crm_pass_timeout = TRUE;
					crm_msg_received = FALSE;
					brm_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					
				}
			}
			break;
			
			case FASTCHG_STEP_CONFIG_WAIT_CTS_CML:
		    if(TRUE == cml_msg_received)
			{
				//TODO: check fast charger capability if can meet requirements
				bcp_msg_enable = FALSE;
				bro_msg_enable = TRUE;
				if( #charger requirements meet #)
				{
					//TODO: send command to close battery main relay and close fast charge relay
					if(# fast charge loop closed #)
					{
						SPN2829_BMS_chging_pre_status = 0xAA;    //battery pack ready
						next_step = FASTCHG_STEP_CONFIG_WAIT_CRO;
					}
					else
					{
						SPN2829_BMS_chging_pre_status = 0x00;
					}
				}
				else
				{
					SPN2829_BMS_chging_pre_status = 0x00;
				}
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr > CONFIG_CML_TIMEOUT)
				{
					bem_cml_timeout = TRUE;
					bro_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					
				}
			}
			break;
			
			case FASTCHG_STEP_CONFIG_WAIT_CRO:
			if((TRUE == cro_msg_received)&&(0xAA ==SPN2830_offcharger_pre_status))
			{// fast charger ready
				bro_msg_enable = FALSE;
				next_step = FASTCHG_STEP_CHARGE;
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr > FASTCHG_STEP_CHARGE)
				{
					bem_cro_timeout = TRUE;
					bro_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					
				}
			}
			break;
			
			case FASTCHG_STEP_CHARGE:
			//TODO: calculate charge voltage and current requirements
			//TODO: create BCS message and BCL message
			bcl_msg_enable = TRUE;
			bcs_msg_enable = TRUE;
			if(TRUE == ccs_msg_received)
			{
				ccs_timer = 0;
			}
			else
			{
				ccs_timer += dt_ms;
				if(ccs_timer > CHARGING_CCS_TIMEOUT)
				{
					/* CCS timeout */
					bcl_msg_enable = FALSE;
					bcs_msg_enable = FALSE;
					next_step = FASTCHG_STEP_CHARGE_CEASE;
				}
				else
				{
					
				}
			}
            //TODO: check charge done
            if(#battery charge done#)
            {
				next_step = FASTCHG_STEP_CHARGE_CEASE;
			}
			else
			{
				
			}
			//TODO: check battery cease and charger cease
			if(# cease request#)
			{
				next_step = FASTCHG_STEP_CHARGE_CEASE;
			}
			else
			{
				
			}
			break;
			
			case FASTCHG_STEP_CHARGE_CEASE:
			//TODO: create BST message
			bst_msg_enable = TRUE;
			//TODO: check battery current and open fast charge loop contactors
			if(# contactors opend #)
			{
				if(TRUE == fastchg_restart_needed)
				{
					//TODO: initial fast charge parameter
					next_step = FASTCHG_STEP_HANDSHAKE_WAIT_CRM;
				}
				else
				{
					next_step = FASTCHG_STEP_CHARGE_DONE;
				}
			}
			else
			{
				
			}
			break;
			
			case FASTCHG_STEP_CHARGE_DONE:
			//TODO: create BSD message
			bsd_msg_enable = TRUE;
			if(TRUE == csd_msg_received)
			{
				
			}
			else
			{
				step_tmr += dt_ms;
				if(step_tmr >　CHARGING_CSD_TIMEOUT)
				{
					bem_csd_timeout = TRUE;
				}
				else
				{
					
				}
			}
			//TODO: other charge end process
			break;
			default:
			break;
		}
		if(last_step != next_step)
		{
			/* fast charge step switch, rest step timer */
			step_tmr = 0.0f;
		}
		last_step = next_step;
		
	}
}