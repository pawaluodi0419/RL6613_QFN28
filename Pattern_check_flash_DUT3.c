#include "platform.h"

u8 _by_Pattern_check_flash_dut3()
{
	u8 i;
	u8 Buff_dut3_XGPIO_0[8];
	u8 read_flashdata[40];
	u8 Loop_run_enable = 0;
	static u16 PASS_COUNT = 0;

	switch(dut3.g_pattern_step)
	{
	case 0x0000:
	{
		if(dut3.g_dut_pattern_status_buf[7] == 0x00)
		{
			Buff_dut3_XGPIO_0[0] = 0x01;                            //REG0005 ouput value[7:0]
			Buff_dut3_XGPIO_0[1] = 0xC2;							//REG0006
			Buff_dut3_XGPIO_0[2] = 0x60;							//REG0007 output value[15:8]
			Buff_dut3_XGPIO_0[3] = 0x9F;							//REG0008
			Buff_dut3_XGPIO_0[4] = 0x00|(dut3.g_uartPatternNum); 	//REG0009 output value[23:16]
			Buff_dut3_XGPIO_0[5] = 0xE0;							//REG000a
			Buff_dut3_XGPIO_0[6] = 0x01;							//REG000b output value[31:24]
			Buff_dut3_XGPIO_0[7] = 0xF4;							//REG000c

			XGpio_dut3_Relay_WriteByte(XPAR_AXI_GPIO_dut3_1_BASEADDR,Buff_dut3_XGPIO_0);
			dut3.g_dut_pattern_status_buf[7] = 0x01;
			//xil_printf("PatternNum = %x\r\n",dut3.g_uartPatternNum);
			//xil_printf("dut3.pattern_check_flash_gpio_control_completed!\r\n\r\n");
			msdelay(10);
		}
		else if(dut3.g_dut_pattern_status_buf[7] == 0x01)
		{
			if(dut3.g_relay_control_timer == 0 )
			{
				dut3.g_dut_pattern_status_buf[7] = 0x00;
				dut3.g_pattern_step++;
			}
		}
		//output fail result
		else
		{
			dut3.g_result_fail = 0x01;
			dut3.g_result_fail_tmrcount = 0xffff;
		}
		break;
	}

	//reset to rom
	case 0x0001:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_reset_to_rom;
		dut3.g_pattern_smbus_control_buf[2] = 0xda;
		dut3.g_pattern_smbus_control_buf[3] = 0x0b;
		dut3.g_pattern_smbus_control_buf[4] = 0x00;

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

	//check if in rom code
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

			if(dut3.g_pattern_smbus_control_buf[10] == 0x00)
			{
				xil_printf("dut3 check in rom code pass!\r\n\r\n");
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

	//select mcm flash
	case 0x0003:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writemem;
		dut3.g_pattern_smbus_control_buf[2] = 0x01;
		dut3.g_pattern_smbus_control_buf[3] = 0xd0;
		dut3.g_pattern_smbus_control_buf[4] = 0x01;
		dut3.g_pattern_smbus_control_buf[5] = 0x01;

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

	//write flash 32byte
	case 0x0004:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writeflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x00;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x08;

		dut3.g_pattern_smbus_control_buf[5] = 0x55;
		dut3.g_pattern_smbus_control_buf[6] = 0xaa;
		dut3.g_pattern_smbus_control_buf[7] = 0xaa;
		dut3.g_pattern_smbus_control_buf[8] = 0x55;
		dut3.g_pattern_smbus_control_buf[9] = 0x00;
		dut3.g_pattern_smbus_control_buf[10] = 0xff;
		dut3.g_pattern_smbus_control_buf[11] = 0xff;
		dut3.g_pattern_smbus_control_buf[12] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	case 0x0005:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writeflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x08;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x08;

		dut3.g_pattern_smbus_control_buf[5] = 0x55;
		dut3.g_pattern_smbus_control_buf[6] = 0xaa;
		dut3.g_pattern_smbus_control_buf[7] = 0xaa;
		dut3.g_pattern_smbus_control_buf[8] = 0x55;
		dut3.g_pattern_smbus_control_buf[9] = 0x00;
		dut3.g_pattern_smbus_control_buf[10] = 0xff;
		dut3.g_pattern_smbus_control_buf[11] = 0xff;
		dut3.g_pattern_smbus_control_buf[12] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	case 0x0006:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writeflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x10;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x08;

		dut3.g_pattern_smbus_control_buf[5] = 0x55;
		dut3.g_pattern_smbus_control_buf[6] = 0xaa;
		dut3.g_pattern_smbus_control_buf[7] = 0xaa;
		dut3.g_pattern_smbus_control_buf[8] = 0x55;
		dut3.g_pattern_smbus_control_buf[9] = 0x00;
		dut3.g_pattern_smbus_control_buf[10] = 0xff;
		dut3.g_pattern_smbus_control_buf[11] = 0xff;
		dut3.g_pattern_smbus_control_buf[12] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	case 0x0007:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_writeflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x18;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x08;

		dut3.g_pattern_smbus_control_buf[5] = 0x55;
		dut3.g_pattern_smbus_control_buf[6] = 0xaa;
		dut3.g_pattern_smbus_control_buf[7] = 0xaa;
		dut3.g_pattern_smbus_control_buf[8] = 0x55;
		dut3.g_pattern_smbus_control_buf[9] = 0x00;
		dut3.g_pattern_smbus_control_buf[10] = 0xff;
		dut3.g_pattern_smbus_control_buf[11] = 0xff;
		dut3.g_pattern_smbus_control_buf[12] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 flash data write pass!\r\n\r\n");
			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	//read back and compare, report fail if not match
	case 0x0008:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x00;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x20;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=0;i<32;i++)
			{
				read_flashdata[i] = dut3.g_pattern_smbus_control_buf[i+10];
			}
			for(i=0;i<32;i++)
			{
				//xil_printf("dut3.read_flashdata[%02d]= %02x\r\n", i, read_flashdata[i]);
			}

			if((read_flashdata[0] == 0x55) && (read_flashdata[1] == 0xaa) && (read_flashdata[2] == 0xaa) && (read_flashdata[3] == 0x55)
			&& (read_flashdata[4] == 0x00) && (read_flashdata[5] == 0xff) && (read_flashdata[6] == 0xff) && (read_flashdata[7] == 0x00)
			&& (read_flashdata[8] == 0x55) && (read_flashdata[9] == 0xaa) && (read_flashdata[10] == 0xaa) && (read_flashdata[11] == 0x55)
			&& (read_flashdata[12] == 0x00) && (read_flashdata[13] == 0xff) && (read_flashdata[14] == 0xff) && (read_flashdata[15] == 0x00)
			&& (read_flashdata[16] == 0x55) && (read_flashdata[17] == 0xaa) && (read_flashdata[18] == 0xaa) && (read_flashdata[19] == 0x55)
			&& (read_flashdata[20] == 0x00) && (read_flashdata[21] == 0xff) && (read_flashdata[22] == 0xff) && (read_flashdata[23] == 0x00)
			&& (read_flashdata[24] == 0x55) && (read_flashdata[25] == 0xaa) && (read_flashdata[26] == 0xaa) && (read_flashdata[27] == 0x55)
			&& (read_flashdata[28] == 0x00) && (read_flashdata[29] == 0xff) && (read_flashdata[30] == 0xff) && (read_flashdata[31] == 0x00))
			{
				xil_printf("dut3 compare flash data pass!\r\n\r\n");
				dut3.g_pattern_step++;
			}
			else
			{
				dut3.g_result_fail = 0x01;
				dut3.g_result_fail_tmrcount = 0xffff;
			}

			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}
			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
		}
		break;
	}

	//chip erase
	case 0x0009:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_eraseflash;
		dut3.g_pattern_smbus_control_buf[2] = 0xda;
		dut3.g_pattern_smbus_control_buf[3] = 0x0b;
		dut3.g_pattern_smbus_control_buf[4] = 0x00;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			xil_printf("dut3 erase flash data pass!\r\n\r\n");
			for(i=1; i<60; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step++;
		}
		break;
	}

	//read again, should be all FF
	case 0x000a:
	{
		dut3.g_pattern_smbus_control_buf[1] = smbus_cmd_type_readflash;
		dut3.g_pattern_smbus_control_buf[2] = 0x00;
		dut3.g_pattern_smbus_control_buf[3] = 0x01;
		dut3.g_pattern_smbus_control_buf[4] = 0x20;

		smbus3_irq_handle(dut3.g_pattern_smbus_control_buf);
		if(dut3.g_pattern_smbus_control_buf[0] != smbus_road_done_pass)
		{
			break;
		}
		else
		{
			for(i=0;i<41;i++)
			{
				read_flashdata[i] = 0;
			}
			for(i=0;i<32;i++)
			{
				read_flashdata[i] = dut3.g_pattern_smbus_control_buf[i+10];
			}
			for(i=0;i<32;i++)
			{
				//xil_printf("dut3.read_flashdata[%02d]= %02x\r\n", i, read_flashdata[i]);
			}

			if((read_flashdata[0] == 0xff) && (read_flashdata[1] == 0xff) && (read_flashdata[2] == 0xff) && (read_flashdata[3] == 0xff)
			&& (read_flashdata[4] == 0xff) && (read_flashdata[5] == 0xff) && (read_flashdata[6] == 0xff) && (read_flashdata[7] == 0xff)
			&& (read_flashdata[8] == 0xff) && (read_flashdata[9] == 0xff) && (read_flashdata[10] == 0xff) && (read_flashdata[11] == 0xff)
			&& (read_flashdata[12] == 0xff) && (read_flashdata[13] == 0xff) && (read_flashdata[14] == 0xff) && (read_flashdata[15] == 0xff)
			&& (read_flashdata[16] == 0xff) && (read_flashdata[17] == 0xff) && (read_flashdata[18] == 0xff) && (read_flashdata[19] == 0xff)
			&& (read_flashdata[20] == 0xff) && (read_flashdata[21] == 0xff) && (read_flashdata[22] == 0xff) && (read_flashdata[23] == 0xff)
			&& (read_flashdata[24] == 0xff) && (read_flashdata[25] == 0xff) && (read_flashdata[26] == 0xff) && (read_flashdata[27] == 0xff)
			&& (read_flashdata[28] == 0xff) && (read_flashdata[29] == 0xff) && (read_flashdata[30] == 0xff) && (read_flashdata[31] == 0xff))
			{
				xil_printf("dut3 check flash data all 0xff pass!\r\n");
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

	case 0x000b:
	{
		dut3.g_dut_start_ready = 0;

		if(Loop_run_enable == 1)
		{
			dut3.g_dut_start_ready = 0x11;
			dut3.g_uartPatternNum = 0x00;
			dut3.g_test_count++;
			xil_printf("dut3.g_test_count =%x\r\n", dut3.g_test_count);
		}
		else
		{
			dut3.g_uartPatternNum = 0x17;
		}
		result_output_for_v50(XPAR_AXI_GPIO_dut3_1_BASEADDR,dut3.g_uartPatternNum);
		xil_printf("dut3.FT2_pass!\r\n\r\n");
		PASS_COUNT++;
		xil_printf(">>>>>>>>>>>>>>>>>>>> DUT3 PASS_COUNT = %d\r\n\r\n", PASS_COUNT);
		//xil_printf("dut3.g_ft2_test_done = %x\r\n",dut3.g_ft2_test_done);
		//xil_printf("dut3.g_dut_start_ready = %x\r\n\r\n",dut3.g_dut_start_ready);
		//xil_printf("dut3.g_result_fail = %x\r\n\r\n",dut3.g_result_fail);
		//xil_printf("dut3.g_dut_pattern_status_buf[2] = %x\r\n\r\n",dut3.g_dut_pattern_status_buf[2]);
		//xil_printf("dut3.g_pattern_step = %x\r\n\r\n",dut3.g_pattern_step);

		pattern_safe_state_dut3();

		break;
	}
	}

	if(dut3.g_result_fail == 0x01)
	{
		xil_printf("dut3.pattern_check_flash_fail! fail_step = %x\r\n\r\n",dut3.g_pattern_step);
		pattern_safe_state_dut3();
	}

	return 0;
}
