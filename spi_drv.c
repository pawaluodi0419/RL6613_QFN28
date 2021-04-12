/*
 * spi_drv.c
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#include "platform.h"



/******************************************************************************/
/**
*
* transmit a single 16bit data by SPI
*
* @param	BaseAddress is the BaseAddress of the SPI device
*
* @param	SlvNum : The slave SPI device Number that attached to SPI master.This parameter is dummy
*                    when SS is asserted manually . range:0-2
*
* @param	TransData :Master to the selected slave data
*
* @return	None
*
* @note		None
*
*******************************************************************************/

void Spi_SendByte(u32 BaseAddr,u8 SlvNum,u16 TransData)
{
	u32 SpiSSRValue;

	if(!(XSpi_ReadReg(BaseAddr,XSP_CR_OFFSET)&0x80)){       //if Manual Slave Select Assertion isn't enabled...
		SpiSSRValue=~((u32)1<<SlvNum);
		XSpi_WriteReg(BaseAddr, XSP_SSR_OFFSET, SpiSSRValue);  //select the slave device
	}


	while ((XSpi_ReadReg(BaseAddr, XSP_SR_OFFSET) &
				XSP_SR_TX_FULL_MASK) == XSP_SR_TX_FULL_MASK);
	XSpi_WriteReg(BaseAddr,XSP_DTR_OFFSET,TransData);

	while (!(XSpi_ReadReg(BaseAddr, XSP_SR_OFFSET) &
					XSP_SR_TX_EMPTY_MASK));
}



/******************************************************************************/
/**
*
* receove a single 16bit data by SPI
*
* @param	BaseAddress is the BaseAddress of the SPI device
*
* @return	SPI receive Buff value
*
* @note		None
*
*******************************************************************************/

u16 Spi_GetReceByte(u32 BaseAddr)
{
	u16 Buffer;
	while ((XSpi_ReadReg(BaseAddr, XSP_SR_OFFSET) &
			XSP_SR_RX_EMPTY_MASK) == 0) {
		Buffer= XSpi_ReadReg((BaseAddr),
						XSP_DRR_OFFSET);
	}
	return Buffer;
}




void SpiInitiToMaster()
{
//initial the SPI 0 master
   XSpi_WriteReg(XPAR_AXI_SPI_0_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the adc and spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_0_BASEADDR, XSP_SSR_OFFSET, ~0);

   //initial the dut0 SPI 1 master
   XSpi_WriteReg(XPAR_AXI_SPI_1_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the adc and spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_1_BASEADDR, XSP_SSR_OFFSET, ~0); //
   XGpio_0_WriteBit(0,DAC_LDAC_OFFSET,0); // always drive dac ldac signal low

   //dut0 SPI Master 2 Initial
   XSpi_WriteReg(XPAR_AXI_SPI_2_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_2_BASEADDR, XSP_SSR_OFFSET, SPI_SS_H);

   //dut0 SPI Master 3 Initial
   XSpi_WriteReg(XPAR_AXI_SPI_3_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_3_BASEADDR, XSP_SSR_OFFSET, SPI_SS_H);


   //initial the dut1 SPI 1 master
   XSpi_WriteReg(XPAR_AXI_SPI_DUT1_1_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the adc and spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_DUT1_1_BASEADDR, XSP_SSR_OFFSET, ~0); //

   //initial the dut2 SPI 1 master
   XSpi_WriteReg(XPAR_AXI_SPI_DUT2_1_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the adc and spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_DUT2_1_BASEADDR, XSP_SSR_OFFSET, ~0); //

   //initial the dut2 SPI 1 master
   XSpi_WriteReg(XPAR_AXI_SPI_DUT3_1_BASEADDR, XSP_CR_OFFSET, 0x9E);  //Manual Slave Select Assertion Enable,need to select the slave manually. Used to access the adc and spi flash
   XSpi_WriteReg(XPAR_AXI_SPI_DUT3_1_BASEADDR, XSP_SSR_OFFSET, ~0); //


}
