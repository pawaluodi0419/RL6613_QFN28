#include "platform.h"

void i2c_mcp23008_output(u32 i2c_fpga_baseaddr,u8 slave_addr,u8 byChannel)
{
	u8 i2c_dut_slaveaddr;
	u8 io_direction_databuf[2];
	u8 io_value_databuf[2];

	i2c_dut_slaveaddr = slave_addr;

	io_direction_databuf[0]= 0x00;
	io_direction_databuf[1]= (u8)(0xff^(1<<byChannel));

	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);	
	XIic_Send(i2c_fpga_baseaddr, i2c_dut_slaveaddr, io_direction_databuf,2, XIIC_STOP);
	usdelay(10);
	xil_printf("io_direction_databuf =%x,%x\r\n",io_direction_databuf[0],io_direction_databuf[1]);

	io_value_databuf[0] = 0x09;
	io_value_databuf[1] = (u8)(0x00|(1<<byChannel));

	XIic_Send(i2c_fpga_baseaddr, i2c_dut_slaveaddr, io_value_databuf,2, XIIC_STOP);
	usdelay(10);
	xil_printf("io_value_databuf =%x,%x\r\n",io_value_databuf[0],io_value_databuf[1]);
}













