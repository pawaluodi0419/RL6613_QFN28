/*
 * smbus_drv.c
 *
 *  Created on: 2018-3-6
 *      Author: Ashley_su
 */

#include "platform.h"
#include "smbus_drv.h"

/******************************************************************************/
/**
*
* Config the smbus
*
* @param    devAddr :
*
* @param    chNum :
*
* @param    avgPoints :
*
* @return	adc conversion data
*
* @note		None
*
*******************************************************************************/


u8 smbus_master_write_blockwrite(u32 smbus_fpga_baseaddr, u8 smbus_writecmd_buf[], u8 smbus_writecmd_count)
{
	u8 i;
	u8 smbus_writedata_count;
	u8 smbus_write_cmdcode;
	u8 smbus_memAddr;
	u8 smbus_writedata_buf[20];

	//xil_printf("smbus_master_write_blockwrite_step00\r\n");
	XIic_DynInit(smbus_fpga_baseaddr);
	//XIic_WriteReg(smbus_fpga_baseaddr,  XIIC_CR_REG_OFFSET,XIIC_CR_TX_FIFO_RESET_MASK | XIIC_CR_MSMS_MASK);
	//XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_writecmd_buf, smbus_writecmd_count, XIIC_STOP);
	//xil_printf("smbus_master_write_blockwrite_step01\r\n");
	XIic_DynSend(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_writecmd_buf, smbus_writecmd_count, XIIC_STOP);
	usdelay(5);
	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Stop(smbus_fpga_baseaddr);

	//xil_printf("smbus_master_write_blockwrite_done\r\n");
	return 0;
}


u8 smbus_master_read_blockwrite(u32 smbus_fpga_baseaddr, u16 smbus_memAddr, u8 smbus_read_cmdcode, u8 smbus_readdata_buf[], u8 smbus_readdata_count)
{

	u8 smbus_readcmd01_buf[5];
	u8 smbus_readcmd_count;

	smbus_readcmd_count = (smbus_readcmd_count&0x00);
	smbus_readcmd01_buf[0] = smbus_read_cmdcode;
	smbus_readcmd01_buf[1] = 0x03;
	smbus_readcmd01_buf[2] = (smbus_memAddr&(0xFF));
	smbus_readcmd01_buf[3] = ((smbus_memAddr&(~(0xFF)))>>8);
	smbus_readcmd01_buf[4] = smbus_readdata_count;

	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_readcmd01_buf, smbus_first_readcmd_count, XIIC_STOP);   //the first writen

	return 0;

}




u8 smbus_master_get_pinstate_dut0(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result)
{

	u8 i;
	u8 smbus_master_pinstatus_buf[1] = {0x00};
	u8 *smus_master_pinstatus;
	u8 smbus_get_pinstatus_ack = 0x00;

	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_pinstatus_buf, 1, XIIC_STOP);
	//usdelay(20);

	////////xil_printf("smbus_master_pinstatus = %x\r\n", smbus_master_pinstatus_buf[0]);
	//smbus_get_pinstatus_ack = smbus_master_alert_ack_dut0(smbus_master_pinstatus_buf[0], smbus_get_pinstatus_result);
	//////xil_printf("smbus_get_pinstatus_ack = %d\r\n", smbus_get_pinstatus_ack);

	return smbus_master_pinstatus_buf[0];
}


u8 smbus_master_get_pinstate_dut1(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result)
{

	u8 i;
	u8 smbus_master_pinstatus_buf[1] = {0x00};
	u8 *smus_master_pinstatus;
	u8 smbus_get_pinstatus_ack = 0x00;

	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_pinstatus_buf, 1, XIIC_STOP);
	//usdelay(20);
	////xil_printf("smbus_master_pinstatus = %x\r\n", smbus_master_pinstatus_buf[0]);
	//smbus_get_pinstatus_ack = smbus_master_alert_ack_dut1(smbus_master_pinstatus_buf[0], smbus_get_pinstatus_result);
	////xil_printf("smbus_get_pinstatus_ack = %d\r\n", smbus_get_pinstatus_ack);

	return smbus_master_pinstatus_buf[0];

}




u8 smbus_master_get_pinstate_dut2(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result)
{

	u8 i;
	u8 smbus_master_pinstatus_buf[1] = {0x00};
	u8 *smus_master_pinstatus;
	u8 smbus_get_pinstatus_ack = 0x00;

	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_pinstatus_buf, 1, XIIC_STOP);
	//usdelay(20);
	//xil_printf("smbus_master_pinstatus = %x\r\n", smbus_master_pinstatus_buf[0]);
	//smbus_get_pinstatus_ack = smbus_master_alert_ack_dut2(smbus_master_pinstatus_buf[0], smbus_get_pinstatus_result);
	//xil_printf("smbus_get_pinstatus_ack = %d\r\n", smbus_get_pinstatus_ack);

	return smbus_master_pinstatus_buf[0];

}



u8 smbus_master_get_pinstate_dut3(u32 smbus_fpga_baseaddr, u8 smbus_get_pinstatus_result)
{

	u8 i;
	u8 smbus_master_pinstatus_buf[1] = {0x00};
	u8 *smus_master_pinstatus;
	u8 smbus_get_pinstatus_ack = 0x00;

	XIic_DynInit(smbus_fpga_baseaddr);
	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_pinstatus_buf, 1, XIIC_STOP);
	//usdelay(20);
	////////xil_printf("smbus_master_pinstatus = %x\r\n", smbus_master_pinstatus_buf[0]);
	//smbus_get_pinstatus_ack = smbus_master_alert_ack_dut3(smbus_master_pinstatus_buf[0], smbus_get_pinstatus_result);
	//////xil_printf("smbus_get_pinstatus_ack = %d\r\n", smbus_get_pinstatus_ack);

	return smbus_master_pinstatus_buf[0];

}


u8 smbus_master_read_blockread_dut0(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count)
{

	u8 i;
	u8 smbus_master_block_read_result;
	u8 smbus_readcmd_count;
	u8 smbus_master_block_read_cmd_buf[30] = {0};

	u8 smbus_second_readcmd_buf[1];

	smbus_second_readcmd_buf[0] = smbus_second_readcmd;

	XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_second_readcmd_buf, 1, XIIC_REPEATED_START);
	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);

	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);

	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1, XIIC_STOP);
	//XIic_DynRecv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1);

	if(smbus_master_block_read_cmd_buf[0] == smbus_readdata_count)
	{
		smbus_master_block_read_result = 0x00;

	}
	else
	{
		smbus_master_block_read_result = 0x01;
	}


	for(i=0;i<smbus_readdata_count+1;i++)
	{

	dut0.g_pattern_smbus_control_buf[i+10] = smbus_master_block_read_cmd_buf[i+1];
	}

    return 0;
}






u8 smbus_master_read_blockread_dut1(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count)
{

	u8 i;
	u8 smbus_master_block_read_result;
	u8 smbus_readcmd_count;
	u8 smbus_master_block_read_cmd_buf[30] = {0};

	u8 smbus_second_readcmd_buf[1];

	smbus_second_readcmd_buf[0] = smbus_second_readcmd;

	XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_second_readcmd_buf, 1, XIIC_REPEATED_START);
	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);

	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);

	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1, XIIC_STOP);
	//XIic_DynRecv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1);

	if(smbus_master_block_read_cmd_buf[0] == smbus_readdata_count)
	{
		smbus_master_block_read_result = 0x00;

	}
	else
	{
		smbus_master_block_read_result = 0x01;
	}


	for(i=0;i<smbus_readdata_count+1;i++)
	{

	dut1.g_pattern_smbus_control_buf[i+10] = smbus_master_block_read_cmd_buf[i+1];
	}

    return 0;
}









u8 smbus_master_read_blockread_dut2(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count)
{

	u8 i;
	u8 smbus_master_block_read_result;
	u8 smbus_readcmd_count;
	u8 smbus_master_block_read_cmd_buf[30] = {0};

	u8 smbus_second_readcmd_buf[1];

	smbus_second_readcmd_buf[0] = smbus_second_readcmd;

	XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_second_readcmd_buf, 1, XIIC_REPEATED_START);
	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);


	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1, XIIC_STOP);

	if(smbus_master_block_read_cmd_buf[0] == smbus_readdata_count)
	{
		smbus_master_block_read_result = 0x00;
	}
	else
	{
		smbus_master_block_read_result = 0x01;
	}


	for(i=0;i<smbus_readdata_count+1;i++)
	{

	dut2.g_pattern_smbus_control_buf[i+10] = smbus_master_block_read_cmd_buf[i+1];
	}

    return 0;
}




u8 smbus_master_read_blockread_dut3(u32 smbus_fpga_baseaddr, u8 smbus_readdata_count)
{

	u8 i;
	u8 smbus_master_block_read_result;
	u8 smbus_readcmd_count;
	u8 smbus_master_block_read_cmd_buf[30] = {0};

	u8 smbus_second_readcmd_buf[1];

	smbus_second_readcmd_buf[0] = smbus_second_readcmd;

	XIic_Send(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_second_readcmd_buf, 1, XIIC_REPEATED_START);
	usdelay(15);
    XIic_DynInit(smbus_fpga_baseaddr);


	XIic_Recv(smbus_fpga_baseaddr, smbus_dut_slaveaddr, smbus_master_block_read_cmd_buf, smbus_readdata_count+1, XIIC_STOP);

	if(smbus_master_block_read_cmd_buf[0] == smbus_readdata_count)
	{
		smbus_master_block_read_result = 0x00;
	}
	else
	{
		smbus_master_block_read_result = 0x01;
	}


	for(i=0;i<smbus_readdata_count+1;i++)
	{

	dut3.g_pattern_smbus_control_buf[i+10] = smbus_master_block_read_cmd_buf[i+1];
	}

    return 0;
}




u8 smbus_master_alert_ack_dut0(u8 smbus_ping_status, u8 smbus_datatransfer_result)
{
	u8 i = 0;
	u8 get_smbus_ping_status;
	get_smbus_ping_status = smbus_ping_status&(0x03);


	if((get_smbus_ping_status==0x00)|(get_smbus_ping_status==0x02))
	{

			usdelay(30);

			switch(get_smbus_ping_status)
			{
			case 0x00:
			{
				 //output smbus transfer data result fail
				dut0.g_result_fail=0x01;
				dut0.g_result_fail_tmrcount = 0xffff;
			}
			case 0x01:
			{
				 //output smbus transfer data result pass
				dut0.g_result_fail=0x00;
			}
			case 0x02:
			{
				 //output smbus transfer data result fail
				dut0.g_result_fail=0x01;
				dut0.g_result_fail_tmrcount = 0xffff;
			}
			case 0x03:
			{
				 //output smbus transfer data result fail
				dut0.g_result_fail=0x01;
				dut0.g_result_fail_tmrcount = 0xffff;
			}
			}


	}

	if(get_smbus_ping_status==0x01)
	{
		dut0.g_result_fail=0x00;      //output smbus transfer data result pass

	}

	else if(get_smbus_ping_status==0x03)
	{
		dut0.g_result_fail=0x01;      //output smbus transfer data result fail
		dut0.g_result_fail_tmrcount = 0xffff;

	}

	//dut0.g_smbus_status_buf[2] = 0x00;
	//dut0.g_smbus_status_buf[2] = dut0.g_result_fail;
	////////xil_printf("dut0_smbus_drv.c\r\n");
	//////xil_printf("dut0.g_smbus_status_buf[2] = %x\r\n", dut0.g_smbus_status_buf[2]);

	return dut0.g_result_fail;

}






u8 smbus_master_alert_ack_dut1(u8 smbus_ping_status, u8 smbus_datatransfer_result)
{
	u8 i = 0;
	u8 get_smbus_ping_status;
	get_smbus_ping_status = smbus_ping_status&(0x03);


	if((get_smbus_ping_status==0x00)|(get_smbus_ping_status==0x02))
	{

			usdelay(30);

			switch(get_smbus_ping_status)
			{
			case 0x00:
			{
				 //output smbus transfer data result fail
				dut1.g_result_fail=0x01;
			}
			case 0x01:
			{
				 //output smbus transfer data result pass
				dut1.g_result_fail=0x00;
			}
			case 0x02:
			{
				 //output smbus transfer data result fail
				dut1.g_result_fail=0x01;
			}
			case 0x03:
			{
				 //output smbus transfer data result fail
				dut1.g_result_fail=0x01;
			}
			}


	}

	if(get_smbus_ping_status==0x01)
	{
		dut1.g_result_fail=0x00;      //output smbus transfer data result pass

	}

	else if(get_smbus_ping_status==0x03)
	{
		dut1.g_result_fail=0x01;      //output smbus transfer data result fail

	}

	//dut1.g_smbus_status_buf[2] = 0x00;
	//dut1.g_smbus_status_buf[2] = dut1.g_result_fail;
	////////xil_printf("dut1_smbus_drv.c\r\n");
	//////xil_printf("dut1.g_smbus_status_buf[2] = %x\r\n", dut1.g_smbus_status_buf[2]);

	return dut1.g_result_fail;

}








u8 smbus_master_alert_ack_dut2(u8 smbus_ping_status, u8 smbus_datatransfer_result)
{
	u8 i = 0;
	u8 get_smbus_ping_status;
	get_smbus_ping_status = smbus_ping_status&(0x03);


	if((get_smbus_ping_status==0x00)|(get_smbus_ping_status==0x02))
	{

			usdelay(30);

			switch(get_smbus_ping_status)
			{
			case 0x00:
			{
				 //output smbus transfer data result fail
				dut2.g_result_fail=0x00;
			}
			case 0x01:
			{
				 //output smbus transfer data result pass
				dut2.g_result_fail=0x01;
			}
			case 0x02:
			{
				 //output smbus transfer data result fail
				dut2.g_result_fail=0x00;
			}
			case 0x03:
			{
				 //output smbus transfer data result fail
				dut2.g_result_fail=0x00;
			}
			}


	}

	if(get_smbus_ping_status==0x01)
	{
		dut2.g_result_fail=0x01;      //output smbus transfer data result pass

	}

	else if(get_smbus_ping_status==0x03)
	{
		dut2.g_result_fail=0x00;      //output smbus transfer data result fail

	}

	dut2.g_smbus_status_buf[2] = 0x00;
	dut2.g_smbus_status_buf[2] = dut2.g_result_fail;
	////////xil_printf("dut2_smbus_drv.c\r\n");
	//////xil_printf("dut2.g_smbus_status_buf[2] = %x\r\n", dut2.g_smbus_status_buf[2]);

	return dut2.g_result_fail;

}



u8 smbus_master_alert_ack_dut3(u8 smbus_ping_status, u8 smbus_datatransfer_result)
{
	u8 i = 0;
	u8 get_smbus_ping_status;
	get_smbus_ping_status = smbus_ping_status&(0x03);


	if((get_smbus_ping_status==0x00)|(get_smbus_ping_status==0x02))
	{

			usdelay(30);

			switch(get_smbus_ping_status)
			{
			case 0x00:
			{
				 //output smbus transfer data result fail
				dut3.g_result_fail=0x00;
			}
			case 0x01:
			{
				 //output smbus transfer data result pass
				dut3.g_result_fail=0x01;
			}
			case 0x02:
			{
				 //output smbus transfer data result fail
				dut3.g_result_fail=0x00;
			}
			case 0x03:
			{
				 //output smbus transfer data result fail
				dut3.g_result_fail=0x00;
			}
			}


	}

	if(get_smbus_ping_status==0x01)
	{
		dut3.g_result_fail=0x01;      //output smbus transfer data result pass

	}

	else if(get_smbus_ping_status==0x03)
	{
		dut3.g_result_fail=0x00;      //output smbus transfer data result fail

	}

	dut3.g_smbus_status_buf[2] = 0x00;
	dut3.g_smbus_status_buf[2] = dut3.g_result_fail;
	////////xil_printf("dut3_smbus_drv.c\r\n");
	//////xil_printf("dut3.g_smbus_status_buf[2] = %x\r\n", dut3.g_smbus_status_buf[2]);

	return dut3.g_result_fail;

}
