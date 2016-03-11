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
** Filename:	BPC_App_FastCharge.h
** Author:      
** Date:        
** Description:	 Define data type used in fast charge control application
***************************************************************************
**/

#ifndef _HEAD_APP_FASTCHARGE

#define  _HEAD_APP_FASTCHARGE

/** Typedef fast charge control step  **/
typedef enum{
	
	FASTCHG_STEP_WAIT,
	FASTCHG_STEP_HANDSHAKE_WAIT_CHM,
	FASTCHG_STEP_HANDSHAKE_WAIT_CRM,
	FASTCHG_STEP_HANDSHAKE_WAIT_CRM_AA,
	FASTCHG_STEP_CONFIG_WAIT_CTS_CML,
	FASTCHG_STEP_CONFIG_WAIT_CRO,
	FASTCHG_STEP_CHARGE,
	FASTCHG_STEP_CHARGE_CEASE,
	FASTCHG_STEP_CHARGE_DONE,	
}enum_fast_chg_step;


#endif