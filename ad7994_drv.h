/*
 * ad7994_drv.h
 *
 *  Created on: 2017-6-19
 *      Author: kay_yin
 */

#ifndef AD7994_DRV_H_
#define AD7994_DRV_H_

#include "platform.h"

#define AD7994_ADC1_SLAVE_ADDR	0x21
#define AD7994_ADC2_SLAVE_ADDR	0x22


#define 	AD7994_EN_LOW      		XIic_WriteReg(XPAR_AXI_IIC_0_BASEADDR,XIIC_GPO_REG_OFFSET,0x0)
#define 	AD7994_EN_HIGH			XIic_WriteReg(XPAR_AXI_IIC_0_BASEADDR,XIIC_GPO_REG_OFFSET,0x1)

#define 	AD7994_CDR_ADDR			0x00
#define 	AD7994_CR_ADDR			0x02



#define AD7994_DEV0_ADDR XPAR_AXI_IIC_0_BASEADDR
#define AD7994_DEV1_ADDR XPAR_AXI_IIC_DUT1_0_BASEADDR
#define AD7994_DEV2_ADDR XPAR_AXI_IIC_DUT2_0_BASEADDR
#define AD7994_DEV3_ADDR XPAR_AXI_IIC_DUT3_0_BASEADDR


u16 AD7994ReadCvsData(u32 devAddr,u8 slaveAddr,u8 preChNum,u8 chNum, u8 avgPoints);

u16 _byAD7994ReadCvsData_dut0(u8 Device_addr,u8 CH_number, u8 avgPoints);
u16 _byAD7994ReadCvsData_dut1(u8 Device_addr,u8 CH_number, u8 avgPoints);
u16 _byAD7994ReadCvsData_dut2(u8 Device_addr,u8 CH_number, u8 avgPoints);
u16 _byAD7994ReadCvsData_dut3(u8 Device_addr,u8 CH_number, u8 avgPoints);



#endif /* AD7994_DRV_H_ */
