/*
 * gpio_drv.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef GPIO_DRV_H_
#define GPIO_DRV_H_

/*
 * DUT define
 */
#define		dut_0		dut0
#define		dut_1		dut1
#define		dut_2		dut2
#define		dut_3		dut3
/*
 * GPIO define
 */

//GPIO_0(for system control) channel 1 Bit mapping define
#define		FT2_EOT_OFFSET		1
#define		FT2_FAIL_OFFSET		2
#define		FT2_PASS_OFFSET		3
#define		FT2_PASS2_OFFSET	4

#define		LED_D2_OFFSET		8
#define		LED_D3_OFFSET		9
#define		LED_D4_OFFSET		10
#define		LED_D5_OFFSET		11
#define		LED_D6_OFFSET		12
#define		LED_D7_OFFSET		13


#define		ADC_DRDY_OFFSET		16
#define		DAC_LDAC_OFFSET		17
#define		ADC_CH0_OFFSET		18
#define		ADC_CH1_OFFSET		19
#define		ADC_CH2_OFFSET		20
#define		AD7994_INT_OFFSET	21

//#define		FT2_PWR_CTRL_OFFSET		24
#define 	FT2_MODE_0_SEL_OFFSET	26
#define		FT2_PWR_DSCHG_OFFSET 	25
#define 	FT2_MODE_1_SEL_OFFSET	27
#define 	FT2_MODE_2_SEL_OFFSET	28
#define 	FT2_MODE_3_SEL_OFFSET	29




//GPIO_0(for system control) channel 2 Bit mapping define
#define		FT2_START_OFFSET			0
#define 	MCM_FLASH_DBG_SEL_OFFSET	8

#define 	usb1dev_rst					16
#define 	usb1dev_ls_mode	 			17
#define	    usb1dev_fs_mode				18


//GPIO_2(for dut0,1,2,3 control) bit mapping define
#define 	dut0_FT2_PWR_CTRL_OFFSET 	0
#define 	dut1_FT2_PWR_CTRL_OFFSET 	dut0_FT2_PWR_CTRL_OFFSET+8
#define 	dut2_FT2_PWR_CTRL_OFFSET 	dut0_FT2_PWR_CTRL_OFFSET+16
#define 	dut3_FT2_PWR_CTRL_OFFSET 	dut0_FT2_PWR_CTRL_OFFSET+24

//FT2 interface signal polarity define
#define		FT2_EOT_VALID_POL 		0
#define		FT2_RSLT_VALID_POL 		0


void XGpio_WriteBit(u32 XGPIO_BASEADDR,u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState);
void XGpio_0_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState);
void XGpio_1_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState);
void XGpio_2_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState);
void XGpio_3_WriteBit(u8 XGPIO_CH,u8 XGPIO_BitOffset, u8 OutState);

u32 XGpio_0_ReadBit(u8 XGPIO_CH,u8 XGPIO_BitOffset);

void XGpio_dut0_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[]);
void XGpio_dut1_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[]);
void XGpio_dut2_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[]);
void XGpio_dut3_Relay_WriteByte(u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[]);
void XGpio_dutx_Relay_WriteByte(u8 dut_x,u32 XPAR_AXI_GPIO_DUT_x_BASEADDR,u8 XGPIO_Data[]);



void GpioIniti();

#endif /* GPIO_DRV_H_ */
