#include "platform.h"

u8 _by_Pattern_Billboard_dut3()
{
	u8 i;

	switch(dut3.g_pattern_step)
	{
	case 0x0000:
	{
		XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x55);
		XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x01);	//向usb host索要测试结果
		dut3.g_pattern_step++;
	}

	case 0x0001:
	{
		dut3.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		dut3.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		dut3.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
		xil_printf("dut3.g_uartRecBuf[0] = %x\r\n", dut3.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
		xil_printf("dut3.g_uartRecBuf[1] = %x\r\n", dut3.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut3/dut1)
		xil_printf("dut3.g_uartRecBuf[2] = %x\r\n", dut3.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)

		if(dut3.g_uartRecBuf[0] == 0x01)
		{
			dut3.g_pattern_step++;
		}
		else
		{
			if(dut3.g_result_polling_tmrcount > 0)
			{
				dut3.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut3.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut3.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				xil_printf("dut3.g_uartRecBuf[0] = %x\r\n", dut3.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
				xil_printf("dut3.g_uartRecBuf[1] = %x\r\n", dut3.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut3/dut1)
				xil_printf("dut3.g_uartRecBuf[2] = %x\r\n", dut3.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)
				dut3.g_result_polling_tmrcount--;
				xil_printf("dut3.g_result_polling_tmrcount = %d\r\n", dut3.g_result_polling_tmrcount);
				msdelay(50);	//每50ms polling一次结果，timeout时间1s
			}
			else
			{
				XGpio_WriteBit(XPAR_AXI_GPIO_1_BASEADDR,0,1, 0);	//reset usb host
				msdelay(10);
				xil_printf("reset usb host!\r\n");
				dut3.g_result_fail=0x01;
				dut3.g_result_fail_tmrcount = 0xffff;
			}
		}
		break;
	}

	case 0x0002:
	{
		if((dut3.g_uartRecBuf[1] & 0x03) == 0x03)
		{
			for(i=1; i<31; i++)
			{
				dut3.g_pattern_smbus_control_buf[i] = CLEAR_;
			}

			dut3.g_result_polling_tmrcount = 5;
			dut3.g_pattern_timer = 0xfff;
			dut3.g_pattern_smbus_control_buf[0] = smbus_road_waiting;
			dut3.g_pattern_step = 0x00;
			dut3.g_dut_pattern_status_buf[2]++;
			dut3.g_uartPatternEnable = 0x00;
			dut3.g_uartPatternNum = (dut3.g_uartPatternNum++ & 0xff);
			result_output_for_v50(XPAR_AXI_GPIO_dut3_1_BASEADDR,dut3.g_uartPatternNum);
			xil_printf("dut3.pattern_Billboard_and_AUX_negative_test_pass!\r\n\r\n");
		}
		else
		{
			if(dut3.g_result_polling_tmrcount > 0)
			{
				XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x55);
				XUartLite_SendByte(XPAR_UARTLITE_0_BASEADDR,0x01);	//向usb host索要测试结果

				dut3.g_uartRecBuf[0] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut3.g_uartRecBuf[1] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				dut3.g_uartRecBuf[2] = XUartLite_RecvByte(XPAR_UARTLITE_0_BASEADDR);
				xil_printf("dut3.g_uartRecBuf[0] = %x\r\n", dut3.g_uartRecBuf[0]);	//用于判断usb host是否需要reset
				xil_printf("dut3.g_uartRecBuf[1] = %x\r\n", dut3.g_uartRecBuf[1]);	//用于存放测试结果低8位(dut3/dut1)
				xil_printf("dut3.g_uartRecBuf[2] = %x\r\n", dut3.g_uartRecBuf[2]);	//用于存放测试结果高8位(dut2/dut3)
				dut3.g_result_polling_tmrcount--;
				xil_printf("dut3.g_result_polling_tmrcount = %d\r\n", dut3.g_result_polling_tmrcount);
				msdelay(50);	//每50ms polling一次结果，timeout时间1s
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
		xil_printf("dut3.pattern_Billboard_and_AUX_negative_test_fail! fail_step = %x\r\n",dut3.g_pattern_step);
		pattern_safe_state_dut3();
	}

	return 0;
}
