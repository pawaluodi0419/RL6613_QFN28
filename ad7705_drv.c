/*
 * ad7994_drv.c
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#include "platform.h"

/******************************************************************************/
/**
*
* ADC write operation
*
* @param    AdcCRegSel
*
* @param    AdcWrData
*
* @return	None
*
* @note		None
*
*******************************************************************************/
void AdcWrOpa(u32 devAddr, u8 AdcCRegSel,u32 AdcWrData)
{
	u8 AdcCrConfig=0;
    u8 SdDataByteNum=1;
    u8 SdBuf;

	AdcCrConfig=(AdcCRegSel<<4)&(~ADC_CR_RD_MASK)&(~ADC_CR_STBY_MASK)&(~ADC_CR_NDRDY_MASK);

	//write data to the communication reg
	XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0x1);  //selected the adc manually
	Spi_SendByte(devAddr,0,AdcCrConfig);

	//decide the Number of bytes need to be send
	if((AdcCRegSel==0x6)|(AdcCRegSel==0x7)){
		SdDataByteNum=3;
	}

	//write data to the adc reg that selected by communication reg
	while(SdDataByteNum){
		SdBuf=(u8)(AdcWrData>>((SdDataByteNum-1)*8));
		Spi_SendByte(devAddr,0,SdBuf);

		SdDataByteNum--;
	}

	XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0); //deassert the SS of the ADC dev

}


/******************************************************************************/
/**
*
* ADC read operation
*
* @param    AdcCRegSel
*
* @return	RecDataBuf
*
* @note		None
*
*******************************************************************************/
u32 AdcRdOpa(u32 devAddr, u8 AdcCRegSel)
{
	u8 AdcCrConfig=0;
    u8 RecDataByteNum;
    u8 i;
    u32 RecDataBuf=0;
    AdcCrConfig=(AdcCRegSel<<4)|(ADC_CR_RD_MASK&(~ADC_CR_STBY_MASK)&(~ADC_CR_NDRDY_MASK));

    //write data to adc communication reg
//    while(Xil_In8(RDAC_RDYSTUS_ADDR)&0x8);
    XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0x1); //assert the SS to select the adc slave
    Spi_SendByte(devAddr,0,AdcCrConfig);


    //decide how many byte should be read
    if(AdcCRegSel==0x3)
    	RecDataByteNum=2;
    else
    	if((AdcCRegSel==0x6)|(AdcCRegSel==0x7))
    		RecDataByteNum=3;
    	else
    		RecDataByteNum=1;

    //read data from adc reg selected by communication reg
    for(i=0;i<RecDataByteNum;i++){

        XSpi_ReadReg(devAddr,XSP_DRR_OFFSET);  // clear SPI receive buffer
//        while(Xil_In8(RDAC_RDYSTUS_ADDR)&0x8);

        Spi_SendByte(devAddr,0,0x0);  //read data from adc
        RecDataBuf|=Spi_GetReceByte(devAddr)<<((RecDataByteNum-i-1)*8); //get data from SPI buff


    }
    XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0);  //deassert the SS of the ADC dev

    return RecDataBuf;



}


/******************************************************************************/
/**
*
* Config the AD7705
*
* @param    OpaMode : operation Mode select
*
* @param    GainSel : Gain Selection
*
* @param    BUSel : Bipolar/Unipolar Operation select
*
* @return	None
*
* @note		None
*
*******************************************************************************/

void ConfigAdc(u32 devAddr, u8 OpaMode,u8 GainSel,u8 BUSel,u8 AinBufSel)
{
	u8 AdcConfigValue=0;

	AdcConfigValue=(OpaMode<<6)|(GainSel<<3)|(BUSel<<2)|(AinBufSel<<1);
	AdcWrOpa(devAddr,ADC_CRRGSEL_STPR_SEL,(u32)AdcConfigValue);

	//delay to let the Calibration complete if it is selected
	if(OpaMode){
		msdelay(300);
	}

}



/******************************************************************************/
/**
*
*
* @return	0: read ad7705 fail 1:read ad7705 succeed
*
* @note		None
*
*******************************************************************************/
u8 AD7705Initial(u32 devAddr)
{
	//initial the AD7705
	//reset the ADC by send 4 byte continous "FF" to sync its SPI interface
	XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0x1);
	Spi_SendByte(devAddr,0,0xFF);
	Spi_SendByte(devAddr,0,0xFF);
	Spi_SendByte(devAddr,0,0xFF);
	Spi_SendByte(devAddr,0,0xFF);
	XSpi_WriteReg(devAddr, XSP_SSR_OFFSET, ~0);

	AdcWrOpa(devAddr,ADC_CRRGSEL_CLKR_SEL,0x0c); //config the AD7705 clock

	ConfigAdc(devAddr,ADC_OPAMODE_SC,ADC_GAINSEL_16,ADC_UNIPOLAR_SEL,ADC_AIN_UNBUF);// configure adc at Gain 16 and start self-calibration

	while(XGpio_0_ReadBit(0,ADC_DRDY_OFFSET)); //polling drdy pin to wait for the end of the self-calibration

	//read the Full-scale/Zero-scale calibration data from the adc, if not the default value alarm the user
	if((AdcRdOpa(devAddr,ADC_CRRGSEL_GAINR_SEL)!=0x5761ab)|(AdcRdOpa(devAddr,ADC_CRRGSEL_OFSTR_SEL)!=0x1f4000))
	{
	//   	XGpio_0_WriteBit(0,LED_D7_OFFSET,0);
		return 0;
	}
	else
	{
		return 1;
	}

}



u16 AD7705ReadCvsData(u32 devAddr, u8 chNum)

{

	u16 i;
	u16 adcData;
	//if the adc conversion channel has been changed, delay enough time for the signal to be settled
	//
	if(1){
		if(!chNum){
			i=dut0_FT2_PWR_CTRL_OFFSET;
		}
		else{
			i=ADC_CH0_OFFSET+chNum-1;
		}
		//turn on the channel
		XGpio_0_WriteBit(0,i,1);

		//turn off other channels as ?ms delay
		msdelay(50);
		if(i!=dut0_FT2_PWR_CTRL_OFFSET){
			XGpio_0_WriteBit(0,dut0_FT2_PWR_CTRL_OFFSET,0);
		}
		if(i!=ADC_CH0_OFFSET){
			XGpio_0_WriteBit(0,ADC_CH0_OFFSET,0);
		}
		if(i!=ADC_CH1_OFFSET){
			XGpio_0_WriteBit(0,ADC_CH1_OFFSET,0);
		}
		if(i!=ADC_CH2_OFFSET){
			XGpio_0_WriteBit(0,ADC_CH2_OFFSET,0);
		}

		msdelay(100);

		//read the conversion for ? times, and discard them
		for(i=0;i<3;i++){
			while(XGpio_0_ReadBit(0,ADC_DRDY_OFFSET)); //polling drdy pin to decide when adc has update the conversion data
			AdcRdOpa(devAddr,ADC_CRRGSEL_DATR_SEL);    //get the conversion data of adc
		}


	}

	while(XGpio_0_ReadBit(0,ADC_DRDY_OFFSET)); //polling drdy pin to decide when adc has update the conversion data
	adcData=AdcRdOpa(devAddr,ADC_CRRGSEL_DATR_SEL);    //get the conversion data of adc

	return adcData;



}
