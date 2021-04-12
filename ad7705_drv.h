/*
 * ad7705_drv.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef AD7705_DRV_H_
#define AD7705_DRV_H_



#define AD7705_DEV0_ADDR	XPAR_AXI_SPI_0_BASEADDR


//AD7705 Communications Register config define
#define 	ADC_CRRGSEL_CR_SEL     		0x0
#define 	ADC_CRRGSEL_STPR_SEL		0x1
#define 	ADC_CRRGSEL_CLKR_SEL        0x2
#define 	ADC_CRRGSEL_DATR_SEL        0x3
#define 	ADC_CRRGSEL_OFSTR_SEL       0x6
#define 	ADC_CRRGSEL_GAINR_SEL       0x7

#define 	ADC_CR_NDRDY_MASK           0x80
#define 	ADC_CR_RD_MASK              0x08
#define 	ADC_CR_STBY_MASK            0x04

//AD7705 operation Mode select
#define 	ADC_OPAMODE_NM              0x0  //Normal Mode
#define 	ADC_OPAMODE_SC              0x1  //Self-Calibration
#define 	ADC_OPAMODE_ZSSC            0x2  //Zero-Scale System Calibration
#define 	ADC_OPAMODE_FSSC            0x3  //Full-Scale System Calibration

//AD7705 Gain Selection
#define 	ADC_GAINSEL_1               0x0
#define 	ADC_GAINSEL_2               0x1
#define 	ADC_GAINSEL_4               0x2
#define 	ADC_GAINSEL_8               0x3
#define 	ADC_GAINSEL_16              0x4
#define 	ADC_GAINSEL_32              0x5
#define 	ADC_GAINSEL_64              0x6
#define 	ADC_GAINSEL_128             0x7

//AD7705 Bipolar/Unipolar Operation select
#define 	ADC_BIPOLAR_SEL             0x0   //Bipolar Operation
#define 	ADC_UNIPOLAR_SEL            0x1   //Unipolar Operation

//AD7705 Analog input buff/unbuff select
#define 	ADC_AIN_BUF                 0x1
#define 	ADC_AIN_UNBUF               0x0

//AD7705 reference voltage value
#define 	ADC_REFVOL_VALUE            2500





void AdcWrOpa(u32 devAddr, u8 AdcCRegSel,u32 AdcWrData);

u32 AdcRdOpa(u32 devAddr, u8 AdcCRegSel);

void ConfigAdc(u32 devAddr, u8 OpaMode,u8 GainSel,u8 BUSel,u8 AinBufSel);

u8 AD7705Initial(u32 devAddr);

u16 AD7705ReadCvsData(u32 devAddr, u8 chNum);

#endif /* AD7994_DRV_H_ */
