/*
 * mcp4822_drv.c
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 *
 *
 *  Modified on:2018-06-14
 *  By:Ashley_su
 *
 *
 */
#include "platform.h"
#include "dac_5825_4822_drv.h"

/*void _by_max5825_output_control_dut0(u8 dac_data_control_buf[])
{


	dut0.g_dacChSel=(dac_data_control_buf[0]>>1)&0x1; //select DAC channel
	dut0.g_dacGainSel=!(dac_data_control_buf[0]&0x4); //select DAC Gain
	switch(dut0.g_ccdet_retest_signbit)
	{
	case 0x00:
	{
		dut0.g_dacTransDataL=dac_data_control_buf[1];
		dut0.g_dacTransDataH=dac_data_control_buf[2]&0xf;
		break;
	}
	case lower_voltage_retest:
	{
		dut0.g_dacTransDataL=dac_data_control_buf[3];
		dut0.g_dacTransDataH=dac_data_control_buf[4]&0xf;
		break;
	}
	case higer_voltage_retest:
	{
		dut0.g_dacTransDataL=dac_data_control_buf[5];
		dut0.g_dacTransDataH=dac_data_control_buf[6]&0xf;
		break;
	}
	}
	DAC_WriteWords(DAC_DEV0_ADDR,dut0.g_dacChSel,dut0.g_dacGainSel,DAC_ACTIVE_VALID,(dut0.g_dacTransDataH<<8)|dut0.g_dacTransDataL);
	//xil_printf("dut0.g_ccdet_retest_signbit = %x\r\n",dut0.g_ccdet_retest_signbit);
	//xil_printf("dut0_dac_writen =%x,%x,%x\,%x\r\n",dut0.g_dacChSel,dut0.g_dacGainSel,dut0.g_dacTransDataL,dut0.g_dacTransDataH);
}*/



void i2c_max5825_output(u32 i2c_fpga_baseaddr,u8 slave_addr,u8 byChannel,u32 Vol_Value) //mV
{
	u8 i2c_dacwrite_DataBuf[3];
	u32 Vol_ValueTemp;
	u8 i2c_dut_slaveaddr;
	u8 i2c_ref_databuf[3];
	u8 i2c_pow_databuf[3];
	u8 max5825_dacmode;

	i2c_dut_slaveaddr = (0x10|slave_addr);
	//i2c_dut_slaveaddr = DAC_MAX5825_DEV0_ADDR;

	//FT_MERGE_DBG_MSG("%x;%02bx;%02bx;%02bx\n",wValue,pDP130DataBuf[0],pDP130DataBuf[1],pDP130DataBuf[2]);

	/*max5825_ref configure as 2.5v
	 *ref mode
	 *00 = EXT
	 *01 = 2.5V
	 *10 = 2.0V
	 *11 = 4.1V
	 */
	i2c_ref_databuf[0]= (0x20 | DAC_REF_EXT);  //change to ref external 3v3
	Vol_ValueTemp=((Vol_Value*4095.00)/3300.00);  //change vref to 3.3V

	/*if((Vol_Value >0) && (Vol_Value<=2500))
	{
		i2c_ref_databuf[0]= (0x24 | DAC_REF_INTEr2V5);
		Vol_ValueTemp=((Vol_Value*4095.00)/2500.00);  //change vref to 2.5V
	}
	else if((Vol_Value > 2500) && (Vol_Value <= 3300))
	{
		i2c_ref_databuf[0]= (0x24 | DAC_REF_INTEr4V1);  //change vref to 4.096V
		Vol_ValueTemp=((Vol_Value*4095.00)/4096.00);
	}*/

	//xil_printf("Vol_ValueTemp =0x%x\r\n",Vol_ValueTemp);
	i2c_ref_databuf[1]=0;
	i2c_ref_databuf[2]=0;
	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);
	XIic_Send(i2c_fpga_baseaddr, i2c_dut_slaveaddr, i2c_ref_databuf,3, XIIC_STOP);
	usdelay(10);

	//xil_printf("i2c_ref_databuf =%x,%x,%x\r\n",i2c_ref_databuf[0],i2c_ref_databuf[1],i2c_ref_databuf[2]);


	/*open channel power
	 *ref mode
	 *00 = Normal
	 *01 = PD 1kW
	 *10 = PD 100kW
	 *11 = PD Hi-Z
	 */
	i2c_pow_databuf[0]=0x40;
	i2c_pow_databuf[1]=(u8)(1<<byChannel);
	i2c_pow_databuf[2]=00;	//power normal mode
	XIic_Send(i2c_fpga_baseaddr, i2c_dut_slaveaddr, i2c_pow_databuf,3, XIIC_STOP);
	usdelay(10);
	//xil_printf("i2c_pow_databuf =%x,%x,%x\r\n",i2c_pow_databuf[0],i2c_pow_databuf[1],i2c_pow_databuf[2]);

	/////////////CODEn_LOADn/////////////////////////////////////
	i2c_dacwrite_DataBuf[0] = (0xB0|byChannel); //CODEn_LOADn
	i2c_dacwrite_DataBuf[1] = (u8)(Vol_ValueTemp>>4);
	i2c_dacwrite_DataBuf[2] = (u8)((Vol_ValueTemp <<4) | (slave_addr&0x0f));
	//xil_printf("i2c_dacwrite_DataBuf =%x,%x,%x\r\n",i2c_dacwrite_DataBuf[0],i2c_dacwrite_DataBuf[1],i2c_dacwrite_DataBuf[2]);
	XIic_DynInit(i2c_fpga_baseaddr);
	usdelay(5);
	XIic_Send(i2c_fpga_baseaddr, i2c_dut_slaveaddr, i2c_dacwrite_DataBuf,3, XIIC_STOP);
	//xil_printf("i2c_max5825_output_voltage =%dmv\r\n",Vol_Value);
}













