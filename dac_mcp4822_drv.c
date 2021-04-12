#include "platform.h"
#include "ccdet_calibration_dut.h"

void _by_mcp4822_output_control_dut0(u8 dac_data_control_buf[])
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
}

void _by_mcp4822_output_control_dut1(u8 dac_data_control_buf[])
{


	dut1.g_dacChSel=(dac_data_control_buf[0]>>1)&0x1; //select DAC channel
	dut1.g_dacGainSel=!(dac_data_control_buf[0]&0x4); //select DAC Gain
	switch(dut1.g_ccdet_retest_signbit)
	{
	case 0x00:
	{
		dut1.g_dacTransDataL=dac_data_control_buf[1];
		dut1.g_dacTransDataH=dac_data_control_buf[2]&0xf;
		break;
	}
	case lower_voltage_retest:
	{
		dut1.g_dacTransDataL=dac_data_control_buf[3];
		dut1.g_dacTransDataH=dac_data_control_buf[4]&0xf;
		break;
	}
	case higer_voltage_retest:
	{
		dut1.g_dacTransDataL=dac_data_control_buf[5];
		dut1.g_dacTransDataH=dac_data_control_buf[6]&0xf;
		break;
	}
	}
	DAC_WriteWords(DAC_DEV1_ADDR,dut1.g_dacChSel,dut1.g_dacGainSel,DAC_ACTIVE_VALID,(dut1.g_dacTransDataH<<8)|dut1.g_dacTransDataL);

}

void _by_mcp4822_output_control_dut2(u8 dac_data_control_buf[])
{
	dut2.g_dacChSel=(dac_data_control_buf[0]>>1)&0x1; //select DAC channel
	dut2.g_dacGainSel=!(dac_data_control_buf[0]&0x4); //select DAC Gain
	switch(dut2.g_ccdet_retest_signbit)
	{
	case 0x00:
	{
		dut2.g_dacTransDataL=dac_data_control_buf[1];
		dut2.g_dacTransDataH=dac_data_control_buf[2]&0xf;
		break;
	}
	case lower_voltage_retest:
	{
		dut2.g_dacTransDataL=dac_data_control_buf[3];
		dut2.g_dacTransDataH=dac_data_control_buf[4]&0xf;
		break;
	}
	case higer_voltage_retest:
	{
		dut2.g_dacTransDataL=dac_data_control_buf[5];
		dut2.g_dacTransDataH=dac_data_control_buf[6]&0xf;
		break;
	}
	}

	DAC_WriteWords(DAC_DEV2_ADDR,dut2.g_dacChSel,dut2.g_dacGainSel,DAC_ACTIVE_VALID,(dut2.g_dacTransDataH<<8)|dut2.g_dacTransDataL);

}

void _by_mcp4822_output_control_dut3(u8 dac_data_control_buf[])
{
	dut3.g_dacChSel=(dac_data_control_buf[0]>>1)&0x1; //select DAC channel
	dut3.g_dacGainSel=!(dac_data_control_buf[0]&0x4); //select DAC Gain
	switch(dut3.g_ccdet_retest_signbit)
	{
	case 0x00:
	{
		dut3.g_dacTransDataL=dac_data_control_buf[1];
		dut3.g_dacTransDataH=dac_data_control_buf[2]&0xf;
		break;
	}
	case lower_voltage_retest:
	{
		dut3.g_dacTransDataL=dac_data_control_buf[3];
		dut3.g_dacTransDataH=dac_data_control_buf[4]&0xf;
		break;
	}
	case higer_voltage_retest:
	{
		dut3.g_dacTransDataL=dac_data_control_buf[5];
		dut3.g_dacTransDataH=dac_data_control_buf[6]&0xf;
		break;
	}
	}

	DAC_WriteWords(DAC_DEV3_ADDR,dut3.g_dacChSel,dut3.g_dacGainSel,DAC_ACTIVE_VALID,(dut3.g_dacTransDataH<<8)|dut3.g_dacTransDataL);

}

/******************************************************************************
*
* Config the MCP4822
*
* @param
*
* @return
*
* @note
*
*******************************************************************************/

void DAC_WriteWords(u32 dacDevAddr, u8 ChSel,u8 GainSel,u8 OpaMode,u16 Date){
	u16 TransData;
	TransData=(ChSel<<DAC_CHSEL_OFFSET)|(GainSel<<DAC_GAIN_OFFSET)|(OpaMode<<DAC_SHDN_OFFSET)|(Date&0xfff);

    XSpi_WriteReg(dacDevAddr, XSP_SSR_OFFSET, ~0x1);
    usdelay(1);
    Spi_SendByte(dacDevAddr,0,(u8)(TransData>>8));
    Spi_SendByte(dacDevAddr,0,(u8)(TransData));
    usdelay(1);
    XSpi_WriteReg(dacDevAddr, XSP_SSR_OFFSET, ~0);

}
