#include "platform.h"

u8 _by_Pattern_U2_MUX_dut2()
{
	u8 i;

	switch(dut2.g_pattern_step)
	{
	case 0x0000:
	{
		XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x55);
		XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0xff);	//向usb host索要测试结果
		msdelay(5);
		dut2.g_pattern_step++;
	}

	case 0x0001:
	{
		dut2.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		dut2.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		dut2.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		xil_printf("dut2.g_uartRecBuf[0] = %x\r\n", dut2.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
		xil_printf("dut2.g_uartRecBuf[1] = %x\r\n", dut2.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut2/dut1)
		xil_printf("dut2.g_uartRecBuf[2] = %x\r\n", dut2.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)

		if(dut2.g_uartRecBuf[0] == 0xff)
		{
			dut2.g_pattern_step++;
		}
		else
		{
			if(dut2.g_result_polling_tmrcount > 0)
			{
				dut2.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut2.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut2.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				xil_printf("dut2.g_uartRecBuf[0] = %x\r\n", dut2.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
				xil_printf("dut2.g_uartRecBuf[1] = %x\r\n", dut2.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut2/dut1)
				xil_printf("dut2.g_uartRecBuf[2] = %x\r\n", dut2.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)
				dut2.g_result_polling_tmrcount--;
				xil_printf("dut2.g_result_polling_tmrcount = %d\r\n", dut2.g_result_polling_tmrcount);
				msdelay(50);
			}
			else
			{
				XGpio_WriteBit(XPAR_AXI_GPIO_1_BASEADDR,0,1, 0);	//reset usb host
				msdelay(10);
				xil_printf("reset usb host!\r\n");
				dut2.g_result_fail=0x01;
				dut2.g_result_fail_tmrcount = 0xffff;
			}
		}
		break;
	}

	case 0x0002:
	{
		if((dut2.g_uartRecBuf[2] & 0x0f) == 0x0f)
		{
			for(i=1; i<31; i++)
			{
				dut2.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut2.g_result_polling_tmrcount = 5;
			dut2.g_pattern_timer = 0xfff;
			dut2.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut2.g_pattern_step = 0x00;
			dut2.g_dut_pattern_status_buf[2]++;
			dut2.g_uartPatternEnable = 0x00;
			result_output_for_v50(XPAR_AXI_GPIO_dut2_1_BASEADDR,dut2.g_uartPatternNum);
			dut2.g_uartPatternNum = 0x16;
			xil_printf("dut2.pattern_U2_MUX_and_AUX_postive_test_pass!\r\n\r\n");
		}
		else
		{
			if(dut2.g_result_polling_tmrcount > 0)
			{
				XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x55);
				XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0xff);	//向usb host索要测试结果
				msdelay(5);

				dut2.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut2.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut2.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				xil_printf("dut2.g_uartRecBuf[0] = %x\r\n", dut2.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
				xil_printf("dut2.g_uartRecBuf[1] = %x\r\n", dut2.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut2/dut1)
				xil_printf("dut2.g_uartRecBuf[2] = %x\r\n", dut2.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)
				dut2.g_result_polling_tmrcount--;
				xil_printf("dut2.g_result_polling_tmrcount = %d\r\n", dut2.g_result_polling_tmrcount);
				msdelay(500);	//每500ms polling一次结果
			}
			else
			{
				dut2.g_result_fail = 0x01;
				dut2.g_result_fail_tmrcount = 0xffff;
			}
		}
		break;
	}
	}

	if(dut2.g_result_fail == 0x01)
	{
		xil_printf("dut2.pattern_U2_MUX_and_AUX_postive_test_fail! fail_step = %x\r\n",dut2.g_pattern_step);
		pattern_safe_state_dut2();
	}

	return 0;
}
