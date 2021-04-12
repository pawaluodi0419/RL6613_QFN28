/*
 * timer_irq_handle.c
 *
 *  Created on: 2017-6-19
 *      Author: kay_yin
 */
#include "platform.h"

// ------------------------------------------------------------
//axi timer 0 interrupt handle
//
//enter this interrupt every 1 ms
// ------------------------------------------------------------
void axi_tmr0_intrq_handle(){
	u32 a;
	u8 i,j=0;
	u8 FT2ResultGpio_Offset;

	//disable the count0
	//XTmrCtr_Disable(XPAR_AXI_TIMER_0_BASEADDR,0);

	//LED blink
	/*if((dut0.g_axiTmr0Cnt&0x7f)==0x64){
		XGpio_0_WriteBit(0,LED_D3_OFFSET,g_opaLedTg);
		g_opaLedTg=~g_opaLedTg;
	}
	*/

	//generate FT2 result waveform
	if(dut0.g_trigSendFT2ResultFlg){
		switch (dut0.g_ft2Result){
		case 0x00:{
			FT2ResultGpio_Offset=FT2_FAIL_OFFSET;
			break;
		}
		case 0x01:{
			FT2ResultGpio_Offset=FT2_PASS_OFFSET;
			break;
		}
		case 0x02:{
			FT2ResultGpio_Offset=FT2_PASS2_OFFSET;
			break;
		}
		}

		XGpio_0_WriteBit(0,FT2ResultGpio_Offset,FT2_RSLT_VALID_POL);
		dut0.g_ft2ResultCnt++;
		if(dut0.g_ft2ResultCnt==2){
			XGpio_0_WriteBit(0,FT2_EOT_OFFSET,FT2_EOT_VALID_POL);
		}
		if(dut0.g_ft2ResultCnt==3){
			XGpio_0_WriteBit(0,FT2_EOT_OFFSET,!FT2_EOT_VALID_POL);
		}
		if(dut0.g_ft2ResultCnt==9){
			XGpio_0_WriteBit(0,FT2ResultGpio_Offset,!FT2_RSLT_VALID_POL);
			dut0.g_trigSendFT2ResultFlg=0;
			dut0.g_ft2ResultCnt=0;

			// set FT2 start re-set flag
			if(!XGpio_0_ReadBit(0,FT2_MODE_0_SEL_OFFSET)) {
				for(i=0;i<10;i++){
					j++;
				}
				if(j==10){
					dut0.g_ft2StartReLoadFlg=1;
				}
			}
		}
	}

	//re-set FT2 start state if mode_sel_0 is low after 2s
	if(dut0.g_ft2StartReLoadFlg){
		dut0.g_ft2StartReloadCnt++;
		if(dut0.g_ft2StartReloadCnt==200){
			dut0.g_ft2StartReLoadFlg=0;
			dut0.g_ft2StartFlg=1;
			dut0.g_ft2StartReloadCnt=0;
		}
	}

	//enter interrupt count ++
	dut0.g_axiTmr0Cnt++;
	//clear the axi timer0 count0 interrupt flag
	a=XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR,0);
    XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_0_BASEADDR,0,a);
}



void axi_tmr1_intrq_handle(){

	u32 a;

	//disable the count0
	//XTmrCtr_Disable(XPAR_AXI_TIMER_0_BASEADDR,0);

/*
	//LED blink
	if((dut0.g_axiTmr1Cnt&0x7f)==0x64){
		XGpio_0_WriteBit(0,LED_D2_OFFSET,g_opaLedTg);
		g_opaLedTg=~g_opaLedTg;
	}
*/


/*	if((dut0.g_dut_start_state == 1) & (dut0.g_smbus_timer&0xff != 0x00))
	{

		if((dut0.g_smbus_timer&0xff)>0x0f)
		{
			return ;
		}
		else
		{
			dut0.g_smbus_timer--;
		}
	}

	if((dut1.g_dut_start_state == 1) & (dut1.g_smbus_timer&0xff != 0x00))
	{

		if((dut1.g_smbus_timer&0xff)>0x0f)
		{
			return ;
		}
		else
		{
			dut1.g_smbus_timer--;
		}
	}

	if((dut2.g_dut_start_state == 1) & (dut2.g_smbus_timer&0xff != 0x00))
	{

		if((dut2.g_smbus_timer&0xff)>0x0f)
		{
			return ;
		}
		else
		{
			dut2.g_smbus_timer--;

			//LED blink
			if((dut0.g_axiTmr1Cnt&0x7f)==0x64){
				XGpio_0_WriteBit(0,LED_D2_OFFSET,g_opaLedTg);
				g_opaLedTg=~g_opaLedTg;
			}
		}
	}

	if((dut3.g_dut_start_state == 1) & (dut3.g_smbus_timer&0xff != 0x00))
	{

		if((dut3.g_smbus_timer&0xff)>0x0f)
		{
			return ;
		}
		else
		{
			dut3.g_smbus_timer--;
		}
	}
*/

	//enter interrupt count ++
	dut0.g_axiTmr1Cnt++;
	//clear the axi timer1 count0 interrupt flag
	a=XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0);
    XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_1_BASEADDR,0,a);
}



void axi_tmr2_intrq_handle(){
	u32 a;
	u8 i,j=0;
	u8 FT2ResultGpio_Offset;

	//disable the count0
	//XTmrCtr_Disable(XPAR_AXI_TIMER_0_BASEADDR,0);

	//LED blink
	if((dut0.g_axiTmr2Cnt&0x7f)==0x64){
		XGpio_0_WriteBit(0,LED_D2_OFFSET,g_ledD2Tg);
		g_ledD2Tg=~g_ledD2Tg;
	}

	if(dut0.g_dut_start_ready == 1)
	{
		////////////////smbus_timer/////////////
		if(dut0.g_smbus_timer&0xff == 0x00)
		{

		}
		else if((dut0.g_smbus_timer&0xff)> 0x00)
		{
			if((dut0.g_smbus_timer&0xff)>0x0f)
			{

			}
		else
		{
			dut0.g_smbus_timer--;
		}
	}

		////////////////relay control_timer/////////////
		if(dut0.g_relay_control_timer&0xffff == 0x00)
		{

		}

		else if((dut0.g_relay_control_timer&0xffff)> 0x00)
		{
			if((dut0.g_relay_control_timer&0xff)>0xffff)
			{
				//something wrong
			}
			else
			{
				dut0.g_relay_control_timer--;
				//xil_printf("dut0_relay_control_timer = %d\r\n", dut0.g_relay_control_timer);
			}
		}

		////////////////smbus_start_timer/////////////
		if(dut0.g_start_smbus_timer&0xffffffff == 0x00)
		{

		}
		else if((dut0.g_start_smbus_timer&0xffffffff)> 0x00)
		{
			dut0.g_start_smbus_timer--;
		}

		////////////////pattern_timer/////////////
		if(dut0.g_pattern_timer&0xffffffff == 0x00)
		{
			dut0.g_result_fail = 0x01;
			xil_printf("dut0.g_pattern_timer = %x\r\n\r\n",dut0.g_pattern_timer);
		}
		else if((dut0.g_pattern_timer&0xffffffff)> 0x00)
		{
			dut0.g_pattern_timer--;
		}
	}


	if(dut1.g_dut_start_ready == 1)
	{
		////////////////smbus_timer/////////////
		if(dut1.g_smbus_timer&0xff == 0x00)
		{

		}
		else if((dut1.g_smbus_timer&0xff)> 0x00)
		{
			if((dut1.g_smbus_timer&0xff)>0x0f)
			{

			}
			else
			{
				dut1.g_smbus_timer--;
			}
		}

		////////////////relay_control_timer/////////////
		if(dut1.g_relay_control_timer&0xffff == 0x00)
		{

		}
		else if((dut1.g_relay_control_timer&0xffff)> 0x00)
		{
			if((dut1.g_relay_control_timer&0xff)>0xffff)
			{
				//something wrong
			}
			else
			{
				dut1.g_relay_control_timer--;
				//xil_printf("dut1_relay_control_timer = %d\r\n", dut2.g_relay_control_timer);
			}
		}

		////////////////smbus_start_timer/////////////
		if(dut1.g_start_smbus_timer&0xffffffff == 0x00)
		{

		}
		else if((dut1.g_start_smbus_timer&0xffffffff)> 0x00)
		{
			dut1.g_start_smbus_timer--;
		}

		////////////////pattern_timer/////////////
		if(dut1.g_pattern_timer&0xffffffff == 0x00)
		{
			dut1.g_result_fail = 0x01;
			xil_printf("dut1.g_pattern_timer = %x\r\n\r\n",dut1.g_pattern_timer);
		}
		else if((dut1.g_pattern_timer&0xffffffff)> 0x00)
		{
			dut1.g_pattern_timer--;
		}
	}


	if(dut2.g_dut_start_ready == 1)
	{
		////////////////smbus_timer/////////////
		if(dut2.g_smbus_timer&0xff == 0x00)
		{

		}
		else if((dut2.g_smbus_timer&0xff)> 0x00)
		{
			if((dut2.g_smbus_timer&0xff)>0x0f)
			{

			}
			else
			{
				dut2.g_smbus_timer--;
			}
		}

		////////////////relay_control_timer/////////////
		if(dut2.g_relay_control_timer&0xffff == 0x00)
		{

		}
		else if((dut2.g_relay_control_timer&0xffff)> 0x00)
		{
			if((dut2.g_relay_control_timer&0xff)>0xffff)
			{
				//something wrong
			}
			else
			{
				dut2.g_relay_control_timer--;
				//xil_printf("dut2_relay_control_timer = %d\r\n", dut2.g_relay_control_timer);
			}
		}

		////////////////smbus_start_timer/////////////
		if(dut2.g_start_smbus_timer&0xffffffff == 0x00)
		{

		}
		else if((dut2.g_start_smbus_timer&0xffffffff)> 0x00)
		{
			dut2.g_start_smbus_timer--;
		}

		////////////////pattern_timer/////////////
		if(dut2.g_pattern_timer&0xffffffff == 0x00)
		{
			dut2.g_result_fail = 0x01;
			xil_printf("dut2.g_pattern_timer = %x\r\n\r\n",dut2.g_pattern_timer);
		}
		else if((dut2.g_pattern_timer&0xffffffff)> 0x00)
		{
			dut2.g_pattern_timer--;
		}
	}


	if(dut3.g_dut_start_ready == 1)
	{
		////////////////smbus_timer/////////////
		if(dut3.g_smbus_timer&0xff == 0x00)
		{

		}
		else if((dut3.g_smbus_timer&0xff)> 0x00)
		{
			if((dut3.g_smbus_timer&0xff)>0x0f)
			{

			}
			else
			{
				dut3.g_smbus_timer--;
			}
		}

		////////////////relay_control_timer/////////////
		if(dut3.g_relay_control_timer&0xffff == 0x00)
		{

		}
		else if((dut3.g_relay_control_timer&0xffff)> 0x00)
		{
			if((dut3.g_relay_control_timer&0xff)>0xffff)
			{
				//something wrong
			}
			else
			{
				dut3.g_relay_control_timer--;
				//xil_printf("dut3_relay_control_timer = %d\r\n", dut3.g_relay_control_timer);
			}
		}

		////////////////smbus_start_timer/////////////
		if(dut3.g_start_smbus_timer&0xffffffff == 0x00)
		{

		}
		else if((dut3.g_start_smbus_timer&0xffffffff)> 0x00)
		{
			dut3.g_start_smbus_timer--;
		}

		////////////////pattern_timer/////////////
		if(dut3.g_pattern_timer&0xffffffff == 0x00)
		{
			dut3.g_result_fail = 0x01;
			xil_printf("dut3.g_pattern_timer = %x\r\n\r\n",dut3.g_pattern_timer);
		}
		else if((dut3.g_pattern_timer&0xffffffff)> 0x00)
		{
			dut3.g_pattern_timer--;
			//xil_printf("dut3.g_pattern_timer = %x\r\n\r\n",dut3.g_pattern_timer);
		}
	}


	//enter interrupt count ++
	dut0.g_axiTmr2Cnt++;
	//clear the axi timer0 count0 interrupt flag
	a=XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_2_BASEADDR,0);
    XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_2_BASEADDR,0,a);
}


/*
 * void axi_tmr3_intrq_handle(){
	u32 a;
	u8 i,j=0;
	u8 FT2ResultGpio_Offset;

	//disable the count0
	//XTmrCtr_Disable(XPAR_AXI_TIMER_0_BASEADDR,0);

	//LED blink
	if((dut0.g_axiTmr2Cnt&0x7f)==0x64){
		XGpio_0_WriteBit(0,LED_D4_OFFSET,g_opaLedTg);
		g_opaLedTg=~g_opaLedTg;
	}




	//enter interrupt count ++
	dut0.g_axiTmr2Cnt++;
	//clear the axi timer0 count0 interrupt flag
	a=XTmrCtr_GetControlStatusReg(XPAR_AXI_TIMER_3_BASEADDR,0);
    XTmrCtr_SetControlStatusReg(XPAR_AXI_TIMER_3_BASEADDR,0,a);

}
*/


