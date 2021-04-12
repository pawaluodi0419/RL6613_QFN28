#include "platform.h"

u8 _by_Pattern0_Setup_dut3()
{
	u8 i;
	u8 read_icstatus_data[20];
	u8 Buff_dut3_XGPIO_0[8];
	static u16 TEST_COUNT = 0;

	switch(dut3.g_pattern_step)
	{
	//FT Mode_relay_Control
	//VMON满偏(XGPIO13 -> H), GPIO8为low(XGPIO5 -> L)
	//Billboard test relay control：XGPIO25设定输出high
	//DP反插test relay control：XGPIO27设定输出high
	case 0x0000:
	{
		dut3.g_uartPatternNum = 0;
		Buff_dut3_XGPIO_0[0] = 0x00;                            //REG0005 ouput value[7:0]
		Buff_dut3_XGPIO_0[1] = 0xDF;							//REG0006
		Buff_dut3_XGPIO_0[2] = 0x20;							//REG0007 output value[15:8]
		Buff_dut3_XGPIO_0[3] = 0xDF;							//REG0008
		Buff_dut3_XGPIO_0[4] = 0x00|(dut3.g_uartPatternNum); 	//REG0009 output value[23:16]
		Buff_dut3_XGPIO_0[5] = 0xE0;							//REG000a
		Buff_dut3_XGPIO_0[6] = 0x0A;							//REG000b output value[31:24]
		Buff_dut3_XGPIO_0[7] = 0xF5;							//REG000c

		XGpio_dut3_Relay_WriteByte(XPAR_AXI_GPIO_dut3_1_BASEADDR,Buff_dut3_XGPIO_0);
		//xil_printf("PatternNum = %x\r\n",dut3.g_uartPatternNum);
		xil_printf("dut3.pattern0_gpio_control_completed!\r\n");
		msdelay(10);

		XGpio_2_WriteBit(0,dut3_FT2_PWR_CTRL_OFFSET,0x00);	//S0_PWR_EN# output low, power on DUT
		xil_printf("dut3 power on!\r\n\r\n");
		msdelay(1200);

		dut3.g_pattern_step++;
		TEST_COUNT++;
		xil_printf(">>>>>>>>>>>>>>>>>>>> DUT3 TEST_COUNT = %d\r\n\r\n", TEST_COUNT);

		break;
	}

	//check FT mode
	case 0x0001:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readmem;
		dut3.g_pattern_smbus_control_buf[2] = 0x07;
		dut3.g_pattern_smbus_control_buf[3] = 0xdf;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 read 0xdf07 =%x\r\n", dut3.g_pattern_smbus_control_buf[10]);

			if(dut3.g_pattern_smbus_control_buf[10] == 0x20)
			{
				xil_printf("dut3 check FT mode pass!\r\n\r\n");
				dut3.g_pattern_step = 0x0003;
			}
			else
			{
				XGpio_2_WriteBit(0,dut3_FT2_PWR_CTRL_OFFSET,0x01);
				msdelay(50);
				XGpio_2_WriteBit(0,dut3_FT2_PWR_CTRL_OFFSET,0x00);
				msdelay(1200);
				xil_printf("dut3 check FT mode again!\r\n\r\n");
				dut3.g_pattern_step = 0x0002;
			}

			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}
			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
		}
		break;
	}

	//check FT mode retry
	case 0x0002:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readmem;
		dut3.g_pattern_smbus_control_buf[2] = 0x07;
		dut3.g_pattern_smbus_control_buf[3] = 0xdf;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 read 0xdf07 =%x\r\n", dut3.g_pattern_smbus_control_buf[10]);

			if(dut3.g_pattern_smbus_control_buf[10] == 0x20)
			{
				xil_printf("dut3 check FT mode pass!\r\n\r\n");
				dut3.g_pattern_step++;
			}
			else
			{
				dut3.g_result_fail = 0x01;
				dut3.g_result_fail_tmrcount = 0xffff;
			}

			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}
			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
		}
		break;
	}

	//设定U2_MUX为Billboard
	case 0x0003:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writephy;
		dut3.g_pattern_smbus_control_buf[2] = 0x3b;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;
		dut3.g_pattern_smbus_control_buf[5] = 0x00;
		dut3.g_pattern_smbus_control_buf[6] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	//设定U2_MUX为Billboard
	case 0x0004:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writephy;
		dut3.g_pattern_smbus_control_buf[2] = 0x0b;
		dut3.g_pattern_smbus_control_buf[3] = 0x00;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;
		dut3.g_pattern_smbus_control_buf[5] = 0x08;
		dut3.g_pattern_smbus_control_buf[6] = 0x03;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	//DP反插
	case 0x0005:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writephy;
		dut3.g_pattern_smbus_control_buf[2] = 0x70;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;
		dut3.g_pattern_smbus_control_buf[5] = 0x00;
		dut3.g_pattern_smbus_control_buf[6] = 0x0c;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;

			dut3.g_start_test_flag1 = 0x01;
			dut3.g_pattern_step++;
		}
		break;
	}

	//check IC information
	case 0x0006:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_geticstatus;
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
			for(i=0;i<21;i++)
			{
				read_icstatus_data[i] = dut3.g_pattern_smbus_control_buf[i+10];
			}
			xil_printf("dut3.read_icstatus_data[11] =0x%x\r\n", read_icstatus_data[11]);
			xil_printf("dut3.read_icstatus_data[12] =0x%x\r\n", read_icstatus_data[12]);

			if((read_icstatus_data[11] == 0x53) && (read_icstatus_data[12] == 0x54))
			{
			    xil_printf("dut3 check IC information pass!\r\n\r\n");

				for(i=1; i<31; i++)
				{
					dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
				}

				dut3.g_pattern_timer = 0xfff;
				dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
				dut3.g_pattern_step = 0x00;
				dut3.g_dut_pattern_status_buf[2]++;
				dut3.g_uartPatternEnable = 0x00;
				dut3.g_uartPatternNum = (dut3.g_uartPatternNum++ & 0xff);
				//dut3.g_uartPatternNum = (dut3.g_uartPatternNum++ & 0xff);
				result_output_for_v50(XPAR_AXI_GPIO_dut3_1_BASEADDR,dut3.g_uartPatternNum);
				xil_printf("dut3_pattern0_setup_pass!\r\n\r\n");
			}
			else
			{
				dut3.g_result_fail = 0x01;
				dut3.g_result_fail_tmrcount = 0xffff;
			}
		}
		break;
	}
	}

	if(dut3.g_result_fail == 0x01)
	{
		xil_printf("dut3_pattern0_setup_fail! fail_step = %x\r\n",dut3.g_pattern_step);
		pattern_safe_state_dut3();
	}

	return 0;
}


