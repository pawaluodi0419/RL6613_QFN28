/*
 * DAC_5825_4822_DRV.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef DAC_5825_4822_DRV_H_
#define DAC_5825_4822_DRV_H_



/*
 * MAX5825 define
 */
#define 	DAC_MAX5825_DEV0_ADDR			0x00
#define 	DAC_MAX5825_DEV1_ADDR			0x20

void i2c_max5825_output(u32 i2c_fpga_baseaddr,u8 slave_addr,u8 byChannel,u32 Vol_Value);

/*
 * MCP4822 define
 */
#define 	DAC_CHSEL_OFFSET			15
#define 	DAC_GAIN_OFFSET				13
#define		DAC_SHDN_OFFSET				12

#define 	DAC_SEL_CHA_VALID			0
#define 	DAC_SEL_CHB_VALID			1
#define 	DAC_GAIN_1_VALID			1
#define 	DAC_GAIN_2_VALID			0
#define 	DAC_SHDN_VALID				0
#define 	DAC_ACTIVE_VALID		 	1
#define 	DAC_REF_EXT		 	        0
#define 	DAC_REF_INTEr2V5		 	1
#define 	DAC_REF_INTEr2V0		 	2
#define 	DAC_REF_INTEr4V1		 	3

#define 	DAC_DEV0_ADDR		XPAR_AXI_SPI_1_BASEADDR
#define 	DAC_DEV1_ADDR		XPAR_AXI_SPI_DUT1_1_BASEADDR
#define 	DAC_DEV2_ADDR		XPAR_AXI_SPI_DUT2_1_BASEADDR
#define 	DAC_DEV3_ADDR		XPAR_AXI_SPI_DUT3_1_BASEADDR

void DAC_WriteWords(u32 dacDevAddr, u8 ChSel,u8 GainSel,u8 OpaMode,u16 Date);

void _by_dac_output_control_dut2(u8 dac_data_control_buf[]);



#endif /* DAC_5825_4822_DRV.h */
