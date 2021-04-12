#include "platform.h"

u8 _by_PatternF_efuse_dut3()
{
	u8 i;
	u8 Buff_dut3_XGPIO_0[8];

	switch(dut3.g_pattern_step)
	{
	//write pattern index
	case 0x0000:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writemem;
		dut3.g_pattern_smbus_control_buf[2] = 0x33;
		dut3.g_pattern_smbus_control_buf[3] = 0xdf;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;
		dut3.g_pattern_smbus_control_buf[5] = 0x0f;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 write pattern index =%x\r\n", dut3.g_pattern_smbus_control_buf[5]);
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
			//msdelay(50);
		}
		break;
	}

	//polling ack bit
	case 0x0001:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readmem;
		dut3.g_pattern_smbus_control_buf[2] = 0x33;
		dut3.g_pattern_smbus_control_buf[3] = 0xdf;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 polling pattern ack bit =%x\r\n", dut3.g_pattern_smbus_control_buf[10]);
			if(dut3.g_pattern_smbus_control_buf[10] == 0x8F)
			{
				for(i=1; i<31; i++)
				{
					dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
				}

				dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
				dut3.g_pattern_step++;
			}
			else
			{
				dut3.g_result_fail = 0x01;
				dut3.g_result_fail_tmrcount = 0xffff;
			}
		}
		break;
	}

	//read efuse
	case 0x0002:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readefuse;
		dut3.g_pattern_smbus_control_buf[2] = 0x00;
		dut3.g_pattern_smbus_control_buf[3] = 0x00;
		dut3.g_pattern_smbus_control_buf[4] = 0x14;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=0;i<20;i++)
			{
				xil_printf("dut3.efuse_data[%02d]= %02x\r\n", i, dut3.g_pattern_smbus_control_buf[i+10]);
			}
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	//read efuse
	case 0x0003:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readefuse;
		dut3.g_pattern_smbus_control_buf[2] = 0x14;
		dut3.g_pattern_smbus_control_buf[3] = 0x00;
		dut3.g_pattern_smbus_control_buf[4] = 0x14;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=0;i<20;i++)
			{
				xil_printf("dut3.efuse_data[%02d]= %02x\r\n", i+20, dut3.g_pattern_smbus_control_buf[i+10]);
			}
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;

			dut3.g_pattern_timer = 0xfff;
			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step = 0x00;
			dut3.g_dut_pattern_status_buf[2]++;
			dut3.g_uartPatternEnable = 0x00;
			dut3.g_uartPatternNum = (dut3.g_uartPatternNum++ & 0xff);
			dut3.g_uartPatternNum = (dut3.g_uartPatternNum++ & 0xff);
			result_output_for_v50(XPAR_AXI_GPIO_dut3_1_BASEADDR,dut3.g_uartPatternNum);
			xil_printf("dut3.patternF_pass!\r\n\r\n");
		}
		break;
	}
/*
	case 0x0004:
	{
		//TEST_COUNT++;
		//xil_printf("TEST_COUNT = %x\r\n\r\n", TEST_COUNT);

		dut3.g_pattern_step = 0x00;
		//dut3.g_dut_start_ready = 0x11;
		////////initial dut////////
		for(i=1; i<30; i++)
		{
			dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
		}

		dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
		dut3.g_smbus_status_buf[0] = 0x00;
		dut3.g_smbus_status_buf[1] = 0xff;
		dut3.g_smbus_style = 0x00;
		dut3.g_smbus_timer = 0xff;
		dut3.g_relay_control_timer = 0xff;
		dut3.g_smbus_getstatus_timer = 0x02;

		for(i=0;i<12;i++)
		{
			dut3.g_ccdet_calibration_data_buf[i] = 0x88;
		}
		dut3.g_efuse_status = 0;
		dut3.g_retest = 0;
		dut3.g_ccdet_step = 0;
		dut3.g_ccdet_retest_signbit = 0;

		for(i=0;i<8;i++)
		{
			dut3.g_dut_pattern_status_buf[i] = 0;
		}

		dut3.g_dut_start_ready = 0;
		XGpio_2_WriteBit(0,dut3_FT2_PWR_CTRL_OFFSET,0x01);

		usdelay(100);
	   	dut3.g_pattern_timer = 0xfff;
		dut3.g_uartPatternEnable = 0x00;

		if(Loop_run_enable ==1)
		{
			dut3.g_dut_start_ready = 0x11;
			dut3.g_uartPatternNum = 0x0;
			dut3.g_test_count++;
			xil_printf("dut3.g_test_count =%x\r\n", dut3.g_test_count);
		}
		else
		{
			dut3.g_uartPatternNum = 0x0f;
		}
		result_output_for_v50(XPAR_AXI_GPIO_dut3_1_BASEADDR,dut3.g_uartPatternNum);

		//xil_printf("dut3.g_dut_start_ready = %x\r\n\r\n",dut3.g_dut_start_ready);
		//xil_printf("dut3.g_result_fail = %x\r\n\r\n",dut3.g_result_fail);
		//xil_printf("dut3.g_dut_pattern_status_buf[2] = %x\r\n\r\n",dut3.g_dut_pattern_status_buf[2]);
		//xil_printf("dut3.g_pattern_step = %x\r\n\r\n",dut3.g_pattern_step);
		break;
	}
*/
	}

	if(dut3.g_result_fail == 0x01)
	{
		xil_printf("dut3.patternF_fail! fail_step = %x\r\n",dut3.g_pattern_step);
		pattern_safe_state_dut3();
	}

	return 0;
}
