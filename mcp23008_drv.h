#ifndef MCP23008_DRV_H_
#define MCP23008_DRV_H_

#define		MCP23008_ADDR	0x26

void i2c_mcp23008_output(u32 i2c_fpga_baseaddr,u8 slave_addr,u8 byChannel);


#endif
