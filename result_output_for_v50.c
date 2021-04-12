/*
 * gpio_drv.c
 *
 *  Created on: 2018-05-18
 *      Author: ashely_su
 */

#include "platform.h"
#include "result_output_for_v50.h"
#include "xgpio.h"
/******************************************************************************/
/**
*
* @param
* OutState:
* 0 = drive low; other value = drive high
*
* XGPIO_CH:
* 0 = channel 1
* other value = channel 2
*
* @return
*
* @note
*
*******************************************************************************/
void result_output_for_v50(u32 XGPIO_BASEADDR,u8 result_data)
{

	//u32 Xgpio_data;
	//u32 Xgpio_tri;
	//u32 read_gpio_data;
	//u32 read_gpio_tri;

	u32 a;
	u32 b;
	u32 c1;
	u32 c2;
	u32 write_result_data;
	u8 XGPIO_ChOffset = 0;  //default gpio ch0


	//set the gpio corresponding bit as input
	a=XGpio_ReadReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(0x1f<<16));
	usdelay(10);
	XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(0x1f<<16));

	//read gpio data
	a=XGpio_ReadReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	//keep gpio data besides gpio16~20
	write_result_data = ((a&(~(0x1f<<16))) | ((result_data&0x1f)<<16));

	//write gpio data 16~20
	b = XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,write_result_data);
	usdelay(10);
	b = XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,write_result_data);
	usdelay(10);



	//xil_printf("a = 0x%x\r\n",a);
	//xil_printf("write_result_data = 0x%x\r\n",write_result_data);
	//xil_printf("b = 0x%x\r\n",b);
	//xil_printf("writedata = 0x%x gpio16~20 = 0x%x\r\n",b,(b>>16)&0x1f);

}
