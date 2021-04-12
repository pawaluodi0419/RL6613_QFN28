#ifndef USB_HOST_COMMUNICATION_H_
#define USB_HOST_COMMUNICATION_H_

#define 	USB_HOST_ADDR		0x30

//#define 	START_TEST						1
//#define 	BILLBOARD_TEST_DUT0_PASS		2
//#define 	BILLBOARD_TEST_DUT0_FAIL		3
//#define 	AUX_MUX_POS_TEST_DUT0_PASS		4
//#define 	AUX_MUX_POS_TEST_DUT0_FAIL		5
//#define 	AUX_MUX_NEG_TEST_DUT0_PASS		6
//#define 	AUX_MUX_NEG_TEST_DUT0_FAIL		7
//#define 	U2_MUX_TEST_DUT0_PASS			8
//#define 	U2_MUX_TEST_DUT0_FAIL			9

void start_test(u32 i2c_fpga_baseaddr, u8 slave_addr);
u8 i2c_master_get_status1(u32 i2c_fpga_baseaddr, u8 slave_addr, u8 i2c_get_status_result);
u8 i2c_master_get_status2(u32 i2c_fpga_baseaddr, u8 slave_addr, u8 i2c_get_status_result);

#endif
