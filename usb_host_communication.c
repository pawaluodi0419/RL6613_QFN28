#include "platform.h"

void start_test(u32 i2c_fpga_baseaddr, u8 slave_addr)
{
	u8 i2c_usb_host_slaveaddr;
	u8 write_databuf[1];

	i2c_usb_host_slaveaddr = slave_addr;
	write_databuf[0] = 0x00;
	write_databuf[1] = 0x80;

	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);
	XIic_Send(i2c_fpga_baseaddr, i2c_usb_host_slaveaddr, write_databuf, 2, XIIC_STOP);
	usdelay(10);

	//xil_printf("inform usb host to start test!\r\n\r\n");
}

u8 i2c_master_get_status1(u32 i2c_fpga_baseaddr, u8 slave_addr, u8 i2c_get_status_result)
{
	u8 i2c_usb_host_slaveaddr;
	u8 get_status_databuf[1] = {0x00};

	i2c_usb_host_slaveaddr = slave_addr;

	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);
	XIic_Recv(i2c_fpga_baseaddr, i2c_usb_host_slaveaddr, get_status_databuf, 2, XIIC_STOP);

	return get_status_databuf[0];
}

u8 i2c_master_get_status2(u32 i2c_fpga_baseaddr, u8 slave_addr, u8 i2c_get_status_result)
{
	u8 i2c_usb_host_slaveaddr;
	u8 get_status_databuf[1] = {0x00};

	i2c_usb_host_slaveaddr = slave_addr;

	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);
	XIic_Recv(i2c_fpga_baseaddr, i2c_usb_host_slaveaddr, get_status_databuf, 2, XIIC_STOP);

	return get_status_databuf[1];
}


