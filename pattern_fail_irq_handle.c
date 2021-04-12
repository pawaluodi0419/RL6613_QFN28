/*
 * gpio_irq_handle.c
 *
 *  Created on: 2017-6-19
 *      Author: kay_yin
 */

#include "platform.h"


void pattern_fail_intrq_dut0()
{
	u8 i;
	for(i=0;i<30;i++)
	{
		dut0.g_pattern_smbus_control_buf[i] = 0x00;
	}
	dut0.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
	dut0.g_smbus_status_buf[0] = 0x00;
	dut0.g_smbus_status_buf[1] = 0xff;
	dut0.g_smbus_style = 0x00;
	dut0.g_smbus_timer = 0xff;
	dut0.g_relay_control_timer = 0xff;
	dut0.g_smbus_getstatus_timer = 0x02;
	/////////smbus initial////////

	/////////cc_det initial////////
	for(i=0;i<12;i++)
	{
		dut0.g_ccdet_calibration_data_buf[i] = 0x88;
	}

	dut0.g_retest = 0;
	dut0.g_ccdet_step = 0;
	dut0.g_ccdet_retest_signbit = 0;
	/////////cc_det initial////////

	/////////pattern initial////////
	for(i=0;i<12;i++)
	{
		dut0.g_dut_pattern_status_buf[i] = 0x00;
	}
	dut0.g_result_fail = 0x00;
	dut0.g_uartPatternEnable = 0x01;
	dut0.g_uartPatternNum = 0x0f;
	dut0.g_result_output_ch = 0;
	dut0.g_pattern_step = 0x00;
	dut0.g_pattern_timer = 0xfff;
	//XGpio_0_WriteBit(0,FT2_PWR_DSCHG_OFFSET,!(0x00));
	XGpio_2_WriteBit(0,dut0_FT2_PWR_CTRL_OFFSET,0x01);
	/////////pattern initial////////

	usdelay(100);
	dut0.g_dut_start_ready = 1;
}


