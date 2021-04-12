/*
 * timer_drv.c
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */


#include "platform.h"





/******************************************************************************
 * XPAR_AXI_TIMER_1_BASEADDR been only used for 100us counter
 *
 ********************************************************************************/

	/******************************************************************************
	*The following are the steps for running the 64-bit counter/timer in generate mode:
	*1. Clear the timer enable bits in control registers (TCSR0 and TCSR1).
	*2. Write the lower 32-bit timer/ counter load register (TLR0).
	*3. Write the higher 32-bit timer/counter load register (TLR1).
	*4. Set the CASC bit in Control register TCSR0.
	*5. Set other mode control bits in control register (TCSR0) as needed.
	*6. Enable the timer in Control register (TCSR0).
	*The following are the steps for reading the 64-bit counter/timer:
	*1. Read the upper 32-bit time r/counter register (TCR1).
	*2. Read the lower 32-bit timer/counter register (TCR0).
	*3. Read the upper 32-bit timer/counter register (TCR1) again. If the value is different from the 32-bit upper value
	*read previously, go back to previous step (reading  TCR0). Otherwise 64-bit timer counter value is correct.
	********************************************************************************/

void Tmr_Counter_100us(u32 BaseAddress , u32 TmrCtrNumber , u16 TmrCount)
{
	u16 i;
	u32 TmrLoadValue;
	u32 ControlStatus_intial;
	u32 ControlStatus;



	XTmrCtr_Disable(BaseAddress, TmrCtrNumber);
	XTmrCtr_DisableIntr(BaseAddress, TmrCtrNumber);

	//When the counter is set to count down,TIMING_INTERVAL = (TLRx + 2) x AXI_CLOCK_PERIOD
	//When the counter is set to count up, TIMING_INTERVAL = (MAX_COUNT - TLRx + 2) x AXI_CLOCK_PERIOD
	TmrLoadValue = XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ/1000-2;
	XTmrCtr_SetLoadReg(BaseAddress, TmrCtrNumber, TmrLoadValue);

	//Loads timer with value in TLR0
	XTmrCtr_LoadTimerCounterReg(BaseAddress, TmrCtrNumber);

	//disable cascade mode
	ControlStatus_intial = XTmrCtr_GetControlStatusReg(BaseAddress, TmrCtrNumber);
	ControlStatus = ControlStatus_intial&(~XTC_CSR_CASC_MASK);
	XTmrCtr_SetControlStatusReg(BaseAddress, TmrCtrNumber, ControlStatus);

	//Set other mode control bits in control register (TCSR0) as needed
	//
	//ControlStatus = ControlStatus & (XTC_CSR_ENABLE_ALL_MASK) &(~XTC_CSR_ENABLE_PWM_MASK)
	ControlStatus = XTmrCtr_GetControlStatusReg(BaseAddress, TmrCtrNumber);
	XTmrCtr_SetControlStatusReg(BaseAddress, TmrCtrNumber, (ControlStatus & (XTC_CSR_ENABLE_ALL_MASK) |XTC_CSR_INT_OCCURED_MASK
			                 & (~XTC_CSR_ENABLE_PWM_MASK) & XTC_CSR_AUTO_RELOAD_MASK & XTC_CSR_CAPTURE_MODE_MASK));

	XTmrCtr_Enable(BaseAddress, TmrCtrNumber);
	XTmrCtr_EnableIntr(BaseAddress, TmrCtrNumber);

	ControlStatus = XTmrCtr_GetControlStatusReg(BaseAddress, TmrCtrNumber);
	XTmrCtr_SetControlStatusReg(BaseAddress, TmrCtrNumber, (ControlStatus | XTC_CSR_INT_OCCURED_MASK));







}








/******************************************************************************/
/**
*
*Time Interval loaded into the TLR
*
* @param    TmrCtrNumber
*
* @param    TmrIntvlValue: the Time Interval with the unit of us
*
* @return	None
*
*******************************************************************************/

void TmrIntvlLoad(u32 BaseAddress,u8 TmrCtrNumber,u32 TmrIntvlValue)
{

	u32 TmrLoadValue;
	u32 ControlStatus;
	u32 Tmr_count = TmrIntvlValue/AXI_TIMER_0_CLOCK_PERD;


	if((XTmrCtr_GetControlStatusReg(BaseAddress,TmrCtrNumber)&XTC_CSR_DOWN_COUNT_MASK)==XTC_CSR_DOWN_COUNT_MASK)
	{
		TmrLoadValue = Tmr_count-2;



	}
	else
	{
		TmrLoadValue = 0xFFFFFFFF+2-Tmr_count;

	}

	/*
	 * Set the value that is loaded into the timer counter and cause it to
	 * be loaded into the timer counter
	 */
	XTmrCtr_SetLoadReg(BaseAddress, TmrCtrNumber, TmrLoadValue);
	XTmrCtr_LoadTimerCounterReg(BaseAddress, TmrCtrNumber);

	/*
	 * Clear the Load Timer bit in the Control Status Register
	 */
	ControlStatus = XTmrCtr_GetControlStatusReg(BaseAddress,
						 TmrCtrNumber);
	XTmrCtr_SetControlStatusReg(BaseAddress, TmrCtrNumber,
				 ControlStatus & (~XTC_CSR_LOAD_MASK));

}


/******************************************************************************/
/**
*
* delay function unit:ms range:0~65535
*
* @param
*
* @return	None
*
* @note		None
*
*******************************************************************************/

void msdelay(u16 DlyTimeValue)
{
	u16 TimeCnt;
	u16 i;
	for(TimeCnt=0;TimeCnt<DlyTimeValue;TimeCnt++){
		for(i=0;i<4166;i++);
	}

}
/******************************************************************************/
/**
*
* delay function, unit:us range:0~65535
*
* @param
*
* @return	None
*
* @note		None
*
*******************************************************************************/

void usdelay(u16 DlyTimeValue)
{
	u16 TimeCnt;
	u16 i;
	for(TimeCnt=0;TimeCnt<DlyTimeValue;TimeCnt++){
		for(i=0;i<4;i++);
	}

}
