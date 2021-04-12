/*
 * smbus_drv.h
 *
 *  Created on: 2018-3-6
 *      Author: Ashley_su
 */

#ifndef SMBUS_DRV_H_
#define SMBUS_DRV_H_

#include "platform.h"


#define smbus_dut_slaveaddr	        0x62
#define smbus_memwrite_cmdcode	    0x18
#define smbus_efusewrite_cmdcode	0x19
#define smbus_phywrite_cmdcode	    0x1B
#define smbus_memread_cmdcode	    0x38

#define smbus_second_readcmd        0x80
#define smbus_first_readcmd_count   0x05





#define TPC_DIC_Register_CMD    0x18
#define SMBUS_DataNum	        0x04
#define SMBUS_DEV_SLAVE_ADDR	0x62
#define SMBUS_DataCnt	        0x04
#define SMBUS_Data	            0x46


#define TPC_Register_ADDR_L	0xA2
#define TPC_Register_ADDR_H	0xC1


#define SMBUS_DEV0_ADDR XPAR_AXI_IIC_DUT0_1_BASEADDR
#define SMBUS_DEV1_ADDR XPAR_AXI_IIC_DUT1_1_BASEADDR
#define SMBUS_DEV2_ADDR XPAR_AXI_IIC_DUT2_1_BASEADDR
#define SMBUS_DEV3_ADDR XPAR_AXI_IIC_DUT3_1_BASEADDR



u8 smbus_master_write_blockwrite(u32 smbus_fpga_baseaddr, u8 smbus_writecmd_buf[], u8 smbus_writecmd_count);
u8 smbus_master_get_pinstate(u8 dut_num, u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result);

u8 smbus_master_read_blockwrite(u32 smbus_fpga_baseaddr, u16 smbus_memAddr, u8 smbus_read_cmdcode, u8 smbus_readdata_buf[], u8 smbus_readdata_count);
u8 smbus_master_read_blockread(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count);
u8 smbus_master_alert_ack(u8 dut_num, u8 smbus_ping_status, u8 smbus_datatransfer_result);

u8 smbus_master_get_pinstate_dut0(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result);
u8 smbus_master_get_pinstate_dut1(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result);
u8 smbus_master_get_pinstate_dut2(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result);
u8 smbus_master_get_pinstate_dut3(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result);


u8 smbus_master_read_blockread_dut0(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count);
u8 smbus_master_read_blockread_dut1(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count);
u8 smbus_master_read_blockread_dut2(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count);
u8 smbus_master_read_blockread_dut3(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count);


u8 smbus_master_alert_ack_dut0(u8 smbus_ping_status, u8 smbus_datatransfer_result);
u8 smbus_master_alert_ack_dut1(u8 smbus_ping_status, u8 smbus_datatransfer_result);
u8 smbus_master_alert_ack_dut2(u8 smbus_ping_status, u8 smbus_datatransfer_result);
u8 smbus_master_alert_ack_dut3(u8 smbus_ping_status, u8 smbus_datatransfer_result);

#endif /* SMBUS_DRV_H_*/



