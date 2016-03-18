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
static bool_t bem_msg_enable;
static bool_t bhm_msg_enable;
static bool_t brm_msg_enable;
static bool_t bcp_msg_enable;
static bool_t bro_msg_enable;
static bool_t bcl_msg_enable;
static bool_t bcs_msg_enable;
static bool_t bst_msg_enable;
static bool_t bsd_msg_enable;

// fast charger message receive flag

static bool_t chm_msg_received;
static bool_t crm_msg_received;
static bool_t cml_msg_received;
static bool_t cro_msg_received;
static bool_t ccs_msg_received;
static bool_t csd_msg_received;

// fast charger CAN signal

static uint8_t SPN2560_ID_feedback_result;
static uint8_t SPN2829_BMS_chging_pre_status;
static uint8_t SPN2830_offcharger_pre_status;

// bem signal variable define
static uint8_t bem_crm_timeout;
static uint8_t bem_crm_pass_timeout;
static uint8_t bem_cml_timeout;
static uint8_t bem_cro_timeout;
static uint8_t bem_ccs_timeout;
static uint8_t bem_cst_timeout;
static uint8_t bem_csd_timeout;

/*************************************************************************/
/* Private Function Prototypes (declare as static) */
/*************************************************************************/
static void Process_FastChg_CANRx(void);
static void Process_FastChg_CANTx(uint32_t dt_ms);
static void Process_FastChg_Cease(void);
static void Process_FastChg_Management(uint32_t dt_ms, bool_t init);
/*************************************************************************/
/* Functions */
/*************************************************************************/


/*************************************************************************
** Function: LoopMe
** Parameter(In):  
					value   current index
					limit   loop range
** Parameter(Out):
					uint16_t  loop result
** Description:
**************************************************************************/
uint16_t LoopMe(uint16_t value, uint16_t limit)
{

    if ( ++value > limit )
    {
        value = 0;
    }

    return(value);

}


/*************************************************************************
** Function: FastChg_Initialize
** Parameter(In):  None
** Parameter(Out): None
** Description: initialize fast charge parameters
**************************************************************************/
void FastChg_Initialize(void)
{
	bem_msg_enable = FALSE;
	bhm_msg_enable = FALSE;
	brm_msg_enable = FALSE;
	bcp_msg_enable = FALSE;
	bro_msg_enable = FALSE;
	bcl_msg_enable = FALSE;
	bcs_msg_enable = FALSE;
	bst_msg_enable = FALSE;
	bsd_msg_enable = FALSE;
	
	chm_msg_received = FALSE;
	crm_msg_received = FALSE;
	cml_msg_received = FALSE;
	cro_msg_received = FALSE;
	ccs_msg_received = FALSE;
	csd_msg_received = FALSE;
	
	bem_crm_timeout       = COMM_TIMEOUT_INVALID;
	bem_crm_pass_timeout  = COMM_TIMEOUT_INVALID;
	bem_cml_timeout       = COMM_TIMEOUT_INVALID;
	bem_cro_timeout       = COMM_TIMEOUT_INVALID;
	bem_ccs_timeout       = COMM_TIMEOUT_INVALID;
	bem_cst_timeout       = COMM_TIMEOUT_INVALID;
	bem_csd_timeout       = COMM_TIMEOUT_INVALID;
	
	SPN2560_ID_feedback_result      = BMS_RECOGNIZE_INVALID;
	SPN2829_BMS_chging_pre_status   = PREPARESTAT_INVALID;
	SPN2830_offcharger_pre_status   = PREPARESTAT_INVALID;
  }

 
/*************************************************************************
** Function: Process_FastChg_CANRx
** Parameter(In):  None
** Parameter(Out): None
** Description: receive fast charger CAN messages, called every 10ms
**************************************************************************/
static void Process_FastChg_CANRx(void)
{
	//TODO: read can messages
}

/*************************************************************************
** Function: Process_FastChg_CANTx
** Parameter(In):  
					dt_ms  delta timer
** Parameter(Out): None
** Description: transfer fast charger CAN messages
**************************************************************************/
static void Process_FastChg_CANTx(uint32_t dt_ms)
{
	static uint32_t loop_tmr =   0u;
	static uint8_t  taskloop =   0u;
	loop_tmr += dt_ms;
	if(dt_ms > 10u)
	{
		//TODO: add 10ms cycle tx task;
		switch (taskloop)
		{
			case 0:
			case 5:
			case 10:
			case 15:
			case 20:
			case 25:
			case 30:
			case 35:
			case 40:
			case 45:
				//TODO: add 50ms task
				break;
			case 1:
			case 26:
			    //TODO: add 250ms task
				break;
			case 2:
				//TODO: add 500ms task
				break;
			default:
				break;
		}
		taskloop = (uint8_t)LoopMe(taskloop, 50);
		loop_tmr = 0u;
	}
	else
	{
		/* do nothing */
	}
}


/*************************************************************************
** Function: Process_FastChg_Cease
** Parameter(In):  None
** Parameter(Out): None
** Description: Determin charge ceases, include battery pack cease and fast
                charger cease
**************************************************************************/
static void Process_FastChg_Cease(void)
{

}

/*************************************************************************
** Function: Process_FastChg_Management
** Parameter(In):
					dt_ms   delta time
					init    function initial requirements
** Parameter(Out):  None
** Description: Fast charge main state machine
**************************************************************************/
static void Process_FastChg_Management(uint32_t dt_ms, bool_t init)
{
	static enum_fast_chg_step       next_step ;
	static enum_fast_chg_step       last_step ;
	static float32_t                ccs_timer;
	static bool_t                   fastchg_restart_needed;
	static float_32t                step_tmr;
	
	if(TRUE == init)
	{  /* fast charge process management parameter initialize */
        step_tmr  = 0.0f;
		ccs_timer = 0.0f;
		fastchg_restart_needed = FALSE;
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
				fastchg_restart_needed = FALSE;
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
					/* do nothing */
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
					/* do nothing */
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
					/* do nothing */
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
					/* do nothing */
				}
			}
            //TODO: check charge done
            if(#battery charge done#)
            {
				next_step = FASTCHG_STEP_CHARGE_CEASE;
			}
			else
			{
				/* do nothing */
			}
			//TODO: check battery cease and charger cease
			if(# cease request#)
			{
				next_step = FASTCHG_STEP_CHARGE_CEASE;
			}
			else
			{
				/* do nothing */
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
				/* do nothing */
			}
			break;
			
			case FASTCHG_STEP_CHARGE_DONE:
			//TODO: create BSD message
			bsd_msg_enable = TRUE;
			if(TRUE == csd_msg_received)
			{
				/* charge done */
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
					/* do nothing */
				}
			}
			//TODO: other charge end process
			break;
			default:
				/* do nothing */
			break;
		}
		if(last_step != next_step)
		{
			/* fast charge step switch, rest step timer */
			step_tmr = 0.0f;
		}
		last_step = next_step;
		
	}

	
/*************************************************************************
** Function: FastChg_main
** Parameter(In):   None
** Parameter(Out):  None
** Description: Fast charge main function interface, called by OS
**************************************************************************/
void FastChg_main(void)
{
	
}