/*
 * gpio_irq_handle.c
 *
 *  Created on: 2017-6-19
 *      Author: kay_yin
 */

#include "platform.h"

void XGPIO_0_Intrq_Handle()
{
	u8 i;
	u8 FT2StartCnt=0;

	/*
	 *if the ft2 start last for ? us ,set the ft2 start flag
	 */
	for(i=0;i<10;i++)
	{
		if(XGpio_0_ReadBit(1,FT2_START_OFFSET))
		{
			FT2StartCnt++;
		}
	}

	if(FT2StartCnt==10){
		dut0.g_ft2StartFlg=1;
	}

	//clear the GPIO_0 interrupt
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_ISR_OFFSET,XGPIO_IR_CH2_MASK);
}





