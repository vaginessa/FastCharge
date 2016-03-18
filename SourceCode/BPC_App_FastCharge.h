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

#ifndef _BPC_APP_FASTCHARGE_H

#define  _BPC_APP_FASTCHARGE_H

/*** Define MISRA C datatype ***/

typedef signed char 				int8_t;
typedef unsigned char 				uint8_t;
typedef volatile signed char 		vint8_t;
typedef volatile unsigned char 		vuint8_t;
typedef signed short 				int16_t;
typedef unsigned short 				uint16_t;
typedef volatile signed short 		vint16_t;
typedef volatile unsigned short 	vuint16_t;
typedef signed long int 			int32_t;
typedef unsigned long int 			uint32_t;
typedef volatile signed long int 	vint32_t;
typedef volatile unsigned long int 	vuint32_t;
typedef float 						float32_t;
typedef long double 				float64_t;
typedef uint8_t                     bool_t;


#define     FALSE   0U
#define     TRUE    1U

/*** communication timeout definition ***/
#define  HANDSHAKE_CHM_TIMEOUT     5.0
#define  HANDSHAKE_CRM_TIMEOUT     5.0
#define  HANDSHAKE_CRM_AA_TIMEOUT  5.0
#define  CONFIG_CML_TIMEOUT        5.0
#define  CONFIT_CRO_TIMEOUT        5.0
#define  CHARGING_CCS_TIMEOUT      5.0
#define  CHARGING_CSD_TIMEOUT      5.0

/*** definition communication timeout flag  ***/
#define  COMM_TIMEOUT_NORMAL      0x00
#define  COMM_TIMEOUT_ABNORMAL    0x01
#define  COMM_TIMEOUT_INVALID     0x02

/*** CRM macro ***/
#define BMS_RECOGNIZE_FAIL               0x00u
#define BMS_RECOGNIZE_PASS               0xAAu
#define BMS_RECOGNIZE_INVALID            0xFFu

/*** CRO/BRO macro ***/
#define PREPARESTAT_INVALID              0xFFu
#define PREPARESTAT_NOT_READY            0x00u
#define PREPARESTAT_READY                0xAAu



/** Typedef fast charge control step  **/
typedef enum{
	FASTCHG_STEP_HANDSHAKE_WAIT_CHM,
	FASTCHG_STEP_HANDSHAKE_WAIT_CRM,
	FASTCHG_STEP_HANDSHAKE_WAIT_CRM_AA,
	FASTCHG_STEP_CONFIG_WAIT_CTS_CML,
	FASTCHG_STEP_CONFIG_WAIT_CRO,
	FASTCHG_STEP_CHARGE,
	FASTCHG_STEP_CHARGE_CEASE,
	FASTCHG_STEP_CHARGE_DONE,	
}enum_fast_chg_step;


/**************************************************************************
** Global Function Prototypes
**************************************************************************/
void FastChg_Initialize(void);
void FastChg_main(void);


#endif