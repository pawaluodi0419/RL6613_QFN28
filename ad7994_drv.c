/*
 * ad7994_drv.c
 *
 *  Created on: 2017-6-19
 *      Author: kay_yin
 */

#include "platform.h"

/******************************************************************************/
/**
*
* Config the AD7705
*
* @param    devAddr :
*
* @param    chNum :
*
* @param    avgPoints :
*
* @return	adc conversion data
*
* @note		None
*
*******************************************************************************/

u16 _byAD7994ReadCvsData_dut0(u8 Device_addr,u8 CH_number, u8 avgPoints)
{
	dut0.g_uartRecDataBuf = CH_number;
	dut0.g_ad7994ChSel = (dut0.g_uartRecDataBuf&0x06)>>1; //channel selection bits
	dut0.g_ad7994ConversionStart = dut0.g_uartRecDataBuf&0x01; //start AD7994 conversion bit

	if(dut0.g_ad7994ConversionStart)
	{
		dut0.g_as7994Cvsdata=0;

		dut0.g_as7994Cvsdata=AD7994ReadCvsData(AD7994_DEV0_ADDR,Device_addr,dut0.g_ad7994RrevCh,dut0.g_ad7994ChSel,avgPoints);

		dut0.g_ad7994DataHighByte=((u8)(dut0.g_as7994Cvsdata>>8))&0xFF;
		dut0.g_ad7994DataLowByte=(u8)(dut0.g_as7994Cvsdata&0xFF);

		dut0.g_ad7994RrevCh=dut0.g_ad7994ChSel; //save the previous select channel number

		dut0.g_ad7994ConversionStart=0; //clear the start flag.
		//xil_printf("dut0_g_as7994Cvsdata = %x\r\n", dut0.g_as7994Cvsdata);
	}

	return dut0.g_as7994Cvsdata;
}


u16 _byAD7994ReadCvsData_dut1(u8 Device_addr,u8 CH_number, u8 avgPoints)
{
	dut1.g_uartRecDataBuf = CH_number;
	dut1.g_ad7994ChSel = (dut1.g_uartRecDataBuf&0x06)>>1; //channel selection bits
	dut1.g_ad7994ConversionStart = dut1.g_uartRecDataBuf&0x01; //start AD7994 conversion bit

	if(dut1.g_ad7994ConversionStart)
	{
		dut1.g_as7994Cvsdata=0;

		dut1.g_as7994Cvsdata=AD7994ReadCvsData(AD7994_DEV1_ADDR,Device_addr,dut1.g_ad7994RrevCh,dut1.g_ad7994ChSel,avgPoints);

		dut1.g_ad7994DataHighByte=((u8)(dut1.g_as7994Cvsdata>>8))&0xFF;
		dut1.g_ad7994DataLowByte=(u8)(dut1.g_as7994Cvsdata&0xFF);

		dut1.g_ad7994RrevCh=dut1.g_ad7994ChSel; //save the previous select channel number

		dut1.g_ad7994ConversionStart=0; //clear the start flag.
		//xil_printf("dut1_g_as7994Cvsdata = %x\r\n", dut1.g_as7994Cvsdata);
	}

	return dut1.g_as7994Cvsdata;
}




u16 _byAD7994ReadCvsData_dut2(u8 Device_addr,u8 CH_number, u8 avgPoints)
{
	dut2.g_uartRecDataBuf = CH_number;
	dut2.g_ad7994ChSel = (dut2.g_uartRecDataBuf&0x06)>>1; //channel selection bits
	dut2.g_ad7994ConversionStart = dut2.g_uartRecDataBuf&0x01; //start AD7994 conversion bit

	if(dut2.g_ad7994ConversionStart)
	{
		dut2.g_as7994Cvsdata=0;

		dut2.g_as7994Cvsdata=AD7994ReadCvsData(AD7994_DEV2_ADDR,Device_addr,dut2.g_ad7994RrevCh,dut2.g_ad7994ChSel,avgPoints);

		dut2.g_ad7994DataHighByte=((u8)(dut2.g_as7994Cvsdata>>8))&0xFF;
		dut2.g_ad7994DataLowByte=(u8)(dut2.g_as7994Cvsdata&0xFF);

		dut2.g_ad7994RrevCh=dut2.g_ad7994ChSel; //save the previous select channel number

		dut2.g_ad7994ConversionStart=0; //clear the start flag.
		//xil_printf("dut2_g_as7994Cvsdata = %x\r\n", dut2.g_as7994Cvsdata);
	}

	return dut2.g_as7994Cvsdata;
}



u16 _byAD7994ReadCvsData_dut3(u8 Device_addr,u8 CH_number, u8 avgPoints)
{
	dut3.g_uartRecDataBuf = CH_number;
	dut3.g_ad7994ChSel = (dut3.g_uartRecDataBuf&0x06)>>1; //channel selection bits
	dut3.g_ad7994ConversionStart = dut3.g_uartRecDataBuf&0x01; //start AD7994 conversion bit

	if(dut3.g_ad7994ConversionStart)
	{
		dut3.g_as7994Cvsdata=0;

		dut3.g_as7994Cvsdata=AD7994ReadCvsData(AD7994_DEV3_ADDR,Device_addr,dut3.g_ad7994RrevCh,dut3.g_ad7994ChSel,avgPoints);

		dut3.g_ad7994DataHighByte=((u8)(dut3.g_as7994Cvsdata>>8))&0xFF;
		dut3.g_ad7994DataLowByte=(u8)(dut3.g_as7994Cvsdata&0xFF);

		dut3.g_ad7994RrevCh=dut3.g_ad7994ChSel; //save the previous select channel number

		dut3.g_ad7994ConversionStart=0; //clear the start flag.
		//xil_printf("dut3_g_as7994Cvsdata = %x\r\n", dut3.g_as7994Cvsdata);
	}

	return dut3.g_as7994Cvsdata;
}



u16 AD7994ReadCvsData(u32 devAddr,u8 slaveAddr,u8 preChNum,u8 chNum, u8 avgPoints)
{

    u8 TempBuff[5];
    u8 i;
    float adcCvsData=0;

	//select the conversion channel
	TempBuff[0]=AD7994_CR_ADDR;
	TempBuff[1]=((1<<chNum)<<4)|0x8;
	XIic_Send(devAddr,slaveAddr,TempBuff,2,XIIC_STOP);


	//start ADC conversion

	if(preChNum!=chNum){  // if the channel is changed, read and discard the first conversion data
		//ADC enable active for 10us
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x0);
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x1);
		usdelay(3);
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x0);
		usdelay(10); // for conversion complete

		//receive adc conversion data
		TempBuff[0]=AD7994_CDR_ADDR;
		XIic_Send(devAddr,slaveAddr,TempBuff,1,XIIC_STOP); // select data register
		XIic_Recv(devAddr,slaveAddr,TempBuff,2, XIIC_STOP);
	}

	for(i=0;i<=avgPoints;i++){

		//ADC enable active for 10us
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x0);
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x1);
		usdelay(3);
		XIic_WriteReg(devAddr,XIIC_GPO_REG_OFFSET,0x0);
		usdelay(10); // for conversion complete

		//receive adc conversion data
		TempBuff[0]=AD7994_CDR_ADDR;
		XIic_Send(devAddr,slaveAddr,TempBuff,1,XIIC_STOP); // select data register
		XIic_Recv(devAddr,slaveAddr,TempBuff,2, XIIC_STOP);
		adcCvsData+=(((TempBuff[0]&0x0f)<<8)+TempBuff[1])/(float)(avgPoints+1);

		usdelay(1);
	}

	return (u16)adcCvsData;


}
