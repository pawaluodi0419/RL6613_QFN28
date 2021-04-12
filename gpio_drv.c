/*
 * gpio_drv.c
 *
 *  Created on: 2018-05-18
 *      Author: ashely_su
 */

#include "platform.h"
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
void XGpio_dut0_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[])
{

	u32 Xgpio_data;
	u32 Xgpio_tri;
	u32 read_gpio_data;
	u32 read_gpio_tri;


	Xgpio_data = ((XGPIO_Data[6]<<24) &0xff000000) | ((XGPIO_Data[4]<<16) & 0x00ff0000) | ((XGPIO_Data[2]<<8) &0xff00) | ((XGPIO_Data[0]) & 0x00ff);
	Xgpio_tri =  ((XGPIO_Data[7]<<24) &0xff000000) | ((XGPIO_Data[5]<<16) & 0x00ff0000) | ((XGPIO_Data[3]<<8) &0xff00) | ((XGPIO_Data[1]) & 0x00ff);

	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);

	read_gpio_data = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET);
	read_gpio_tri = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET);

	dut0.g_relay_control_timer = 0x96;

	//xil_printf("XGpio_DUT2_Relay_WriteByte\r\n");
	//xil_printf("read_gpio_data = %x\r\n", read_gpio_data);
	//xil_printf("read_gpio_tri = %x\r\n", read_gpio_tri);

}


void XGpio_dut1_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[])
{

	u32 Xgpio_data;
	u32 Xgpio_tri;
	u32 read_gpio_data;
	u32 read_gpio_tri;


	Xgpio_data = ((XGPIO_Data[6]<<24) &0xff000000) | ((XGPIO_Data[4]<<16) & 0x00ff0000) | ((XGPIO_Data[2]<<8) &0xff00) | ((XGPIO_Data[0]) & 0x00ff);
	Xgpio_tri =  ((XGPIO_Data[7]<<24) &0xff000000) | ((XGPIO_Data[5]<<16) & 0x00ff0000) | ((XGPIO_Data[3]<<8) &0xff00) | ((XGPIO_Data[1]) & 0x00ff);

	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);

	read_gpio_data = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET);
	read_gpio_tri = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET);

	dut1.g_relay_control_timer = 0x96;

	//xil_printf("XGpio_DUT2_Relay_WriteByte\r\n");
	//xil_printf("read_gpio_data = %x\r\n", read_gpio_data);
	//xil_printf("read_gpio_tri = %x\r\n", read_gpio_tri);

}


void XGpio_dut2_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[])
{

	u32 Xgpio_data;
	u32 Xgpio_tri;
	u32 read_gpio_data;
	u32 read_gpio_tri;


	Xgpio_data = ((XGPIO_Data[6]<<24) &0xff000000) | ((XGPIO_Data[4]<<16) & 0x00ff0000) | ((XGPIO_Data[2]<<8) &0xff00) | ((XGPIO_Data[0]) & 0x00ff);
	Xgpio_tri =  ((XGPIO_Data[7]<<24) &0xff000000) | ((XGPIO_Data[5]<<16) & 0x00ff0000) | ((XGPIO_Data[3]<<8) &0xff00) | ((XGPIO_Data[1]) & 0x00ff);

	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);

	read_gpio_data = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET);
	read_gpio_tri = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET);

	dut2.g_relay_control_timer = 0x96;

	//xil_printf("XGpio_DUT2_Relay_WriteByte\r\n");
	//xil_printf("read_gpio_data = %x\r\n", read_gpio_data);
	//xil_printf("read_gpio_tri = %x\r\n", read_gpio_tri);

}


void XGpio_dut3_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[])
{

	u32 Xgpio_data;
	u32 Xgpio_tri;
	u32 read_gpio_data;
	u32 read_gpio_tri;


	Xgpio_data = ((XGPIO_Data[6]<<24) &0xff000000) | ((XGPIO_Data[4]<<16) & 0x00ff0000) | ((XGPIO_Data[2]<<8) &0xff00) | ((XGPIO_Data[0]) & 0x00ff);
	Xgpio_tri =  ((XGPIO_Data[7]<<24) &0xff000000) | ((XGPIO_Data[5]<<16) & 0x00ff0000) | ((XGPIO_Data[3]<<8) &0xff00) | ((XGPIO_Data[1]) & 0x00ff);

	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET,Xgpio_tri);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);
	usdelay(50);
	XGpio_WriteReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET,Xgpio_data);

	read_gpio_data = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_DATA_OFFSET);
	read_gpio_tri = XGpio_ReadReg(XPAR_AXI_GPIO_DUT_x_BASEADDR,XGPIO_TRI_OFFSET);

	dut3.g_relay_control_timer = 0x96;

	//xil_printf("XGpio_DUT2_Relay_WriteByte\r\n");
	//xil_printf("read_gpio_data = %x\r\n", read_gpio_data);
	//xil_printf("read_gpio_tri = %x\r\n", read_gpio_tri);

}



void XGpio_WriteBit(u32 XGPIO_BASEADDR,u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;


	//set the gpio corresponding bit as input
	a=XGpio_ReadReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	usdelay(100);
	XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));

	a=XGpio_ReadReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	if(OutState==0){
		XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	}
	else{
		XGpio_WriteReg(XGPIO_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	}
}



void XGpio_0_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as output
	a=XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	usdelay(100);
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));

	a=XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	if(OutState==0){
		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	}
	else{
		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	}
}


/******************************************************************************/
/**
*
* @param
* OutState:
* 0 = drive low; other value = drive high
*
* XGPIO_CH:
* 0 = channel 1
* other value = channel 1
*
* @return
*
* @note
*
*******************************************************************************/
void XGpio_1_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as output
	a=XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	usdelay(100);
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));

	a=XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	if(OutState==0){
		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	}
	else{
		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	}
}







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
void XGpio_2_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as output
	a=XGpio_ReadReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	usdelay(100);
	XGpio_WriteReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));

	a=XGpio_ReadReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	if(OutState==0){
		XGpio_WriteReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	}
	else{
		XGpio_WriteReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	}
}




/******************************************************************************/
/**
*
* @param
* OutState:
* 0 = drive low; other value = drive high
*
* XGPIO_CH:
* 0 = channel 1
* other value = channel 3
*
* @return
*
* @note
*
*******************************************************************************/
/*void XGpio_3_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as output
	a=XGpio_ReadReg(XPAR_AXI_GPIO_3_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XPAR_AXI_GPIO_3_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));

	a=XGpio_ReadReg(XPAR_AXI_GPIO_3_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset);

	if(OutState==0){
		XGpio_WriteReg(XPAR_AXI_GPIO_3_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a&~(1<<XGPIO_BitOffset));
	}
	else{
		XGpio_WriteReg(XPAR_AXI_GPIO_3_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	}
}
*/



/******************************************************************************/
/*
* @param
* OutState:
*
* @return
*
* @note
*
*******************************************************************************/
u32 XGpio_0_ReadBit(u8 XGPIO_CH,u8 XGPIO_BitOffset)
{
	u32 a;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as input
	a=XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));

	return (XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_DATA_OFFSET+XGPIO_ChOffset)&(1<<XGPIO_BitOffset))==(1<<XGPIO_BitOffset);


}


u32 XGpio_Dutx_ReadBit(u32 XGPIO_BaseAddr,u8 XGPIO_CH,u8 XGPIO_BitOffset)
{
	u32 a;
	u32 b;
	u8 XGPIO_ChOffset=XGPIO_CH?XGPIO_CHAN_OFFSET:0;

	//set the gpio corresponding bit as input
	a=XGpio_ReadReg(XGPIO_BaseAddr,XGPIO_TRI_OFFSET+XGPIO_ChOffset);
	XGpio_WriteReg(XGPIO_BaseAddr,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	usdelay(2);
	XGpio_WriteReg(XGPIO_BaseAddr,XGPIO_TRI_OFFSET+XGPIO_ChOffset,a|(1<<XGPIO_BitOffset));
	usdelay(2);
	b=XGpio_ReadReg(XGPIO_BaseAddr,XGPIO_DATA_OFFSET+XGPIO_ChOffset)&(1<<XGPIO_BitOffset);
	usdelay(2);
	b=XGpio_ReadReg(XGPIO_BaseAddr,XGPIO_DATA_OFFSET+XGPIO_ChOffset)&(1<<XGPIO_BitOffset);
	return (b==(1<<XGPIO_BitOffset));


}



void GpioIniti()
{
    //initial the gpio_0 status
    XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET,~0); // set all gpio_0 channel 1 as input
    XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET+XGPIO_CHAN_OFFSET,~0); // set all gpio_0 channel 2 as input
    XGpio_WriteReg(XPAR_AXI_GPIO_2_BASEADDR,XGPIO_TRI_OFFSET,~0); // set all gpio_2 channel 1 as input

    //XGpio_0_WriteBit(0,FT2_EOT_OFFSET,!(FT2_EOT_VALID_POL));
    //XGpio_0_WriteBit(0,FT2_FAIL_OFFSET,!(FT2_RSLT_VALID_POL));
    //XGpio_0_WriteBit(0,FT2_PASS_OFFSET,!(FT2_RSLT_VALID_POL));
    //XGpio_0_WriteBit(0,FT2_PASS2_OFFSET,!(FT2_RSLT_VALID_POL));

    XGpio_0_WriteBit(0,FT2_PWR_DSCHG_OFFSET,1);   //enable the FT2 QA board power discharge
    XGpio_2_WriteBit(0,dut0_FT2_PWR_CTRL_OFFSET,1);	  //disable DUT0 QA board power
    XGpio_2_WriteBit(0,dut1_FT2_PWR_CTRL_OFFSET,1);	  //disable DUT1 QA board power
    XGpio_2_WriteBit(0,dut2_FT2_PWR_CTRL_OFFSET,1);	  //disable DUT2 QA board power
    XGpio_2_WriteBit(0,dut3_FT2_PWR_CTRL_OFFSET,1);	  //disable DUT3 QA board power


    //initial the gpio_1 status
    XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR,XGPIO_TRI_OFFSET,~0); // set dut0 gpio_1 channel 1 as input
    XGpio_WriteReg(XPAR_AXI_GPIO_DUT1_1_BASEADDR,XGPIO_TRI_OFFSET,~0); // set dut1 gpio_1 channel 1 as input
    XGpio_WriteReg(XPAR_AXI_GPIO_DUT2_1_BASEADDR,XGPIO_TRI_OFFSET,~0); // set dut2 gpio_1 channel 1 as input
    XGpio_WriteReg(XPAR_AXI_GPIO_DUT3_1_BASEADDR,XGPIO_TRI_OFFSET,~0); // set dut3 gpio_1 channel 1 as input

}

