/*
 * VarInitial.c
 *
 *  Created on: 2017-6-20
 *      Author: kay_yin
 */

#include "platform.h"

void VarInitial()
{
	u8 i;

	//dut0
	dut0.g_uartRecBuf[4];
	dut0.g_uartRecBufNum=0;
	dut0.g_uartRecDataBuf;
	dut0.g_uartRecAddrBufL;
	dut0.g_uartRecAddrBufH;
	dut0.g_uartStartReadFlag=0;
	dut0.g_uartStartWriteFlag=0;
	dut0.g_uartRecAddrBufCnt;
	dut0.g_uartRecDataBufNum;
	dut0.g_uartWriteValidFlg;
	dut0.g_uartReadValidFlg;
	dut0.g_uartRecAddrBuf;
	dut0.g_uartLnkChk;
	dut0.g_uartTranDataBuf;

	dut0.g_uartPatternNum = 0x0f;
	dut0.g_result_output_ch = 0;

	//pattern state//
	dut0.g_dut_pattern_status_buf[0]= 0x00;
	dut0.g_dut_pattern_status_buf[1]= 0x00;
	dut0.g_dut_pattern_status_buf[2]= 0x00;
	dut0.g_dut_pattern_status_buf[3]= 0x00;
	dut0.g_dut_pattern_status_buf[4]= 0x00;
	dut0.g_dut_pattern_status_buf[5]= 0x00;
	dut0.g_dut_pattern_status_buf[6]= 0x00;


	dut0.g_axiTmr0Cnt=0;
	dut0.g_axiTmr1Cnt=0;
	dut0.g_axiTmr2Cnt=0;


	dut0.g_trigSendFT2ResultFlg=0;
	dut0.g_ft2Result=0;
	dut0.g_ft2ResultCnt=0;
	dut0.g_ft2StartFlg=0;
	dut0.g_ft2StartReLoadFlg=0;
	dut0.g_ft2StartReloadCnt=0;

	dut0.g_vmoncompare_process_bit=0;
	dut0.g_vmon_compare_step=0;
	dut0.g_start_smbus_timer = 0xffffffff;
	dut0.g_start_smbus_retry = 0x2;
	dut0.g_smbus_writeblock_status = 0;
	dut0.g_test_count=0;

	dut0.g_adcOpaFlg=0;
	dut0.g_adcChSel=0;
	dut0.g_adcData=0;

	dut0.g_dacOpaFlg=0;
	dut0.g_dacChSel=0;
	dut0.g_dacGainSel=0;
	dut0.g_dacTransDataL=0;
	dut0.g_dacTransDataH=0;

	dut0.g_flashDLStart=0;
	dut0.g_flashSize=0;
	dut0.g_flashMCMEraseEn=1;
	dut0.g_flashMCMRdAccChkEn=1;
	dut0.g_flashRdCompEn=1;
	dut0.g_flashRdCompResult=0;
	dut0.g_flashMCMRdAccValue=0;

	dut0.g_ad7994ConversionStart=0;
	dut0.g_ad7994ChSel=0;
	dut0.g_ad7994RrevCh=0x55; // initial the register with a value that different from g_ad7994ChSel
	dut0.g_ad7994DataLowByte=0;
	dut0.g_ad7994DataHighByte=0;
	dut0.g_ad7994AvgPionts=0;

	dut0.g_ccdet_retest_signbit = 0x00;
	dut0.g_efuse_status = 0;
	dut0.g_efuse_valid_ldo3v3 = 0;
	dut0.g_efuse_data_ldo3v3 = 0;
	for(i=0;i<10;i++)
	{
		dut0.g_ccdet_calibration_data_buf[i] = 0x88;
	}

	//smbus control state//

	for(i=0;i<31;i++)
	{
		dut0.g_pattern_smbus_control_buf[i] = 0x00;
	}
	dut0.g_smbus_getstatus_timer = 0x02;

	//dut1
	dut1.g_uartRecBuf[4];
	dut1.g_uartRecBufNum=0;
	dut1.g_uartRecDataBuf;
	dut1.g_uartRecAddrBufL;
	dut1.g_uartRecAddrBufH;
	dut1.g_uartStartReadFlag=0;
	dut1.g_uartStartWriteFlag=0;
	dut1.g_uartRecAddrBufCnt;
	dut1.g_uartRecDataBufNum;
	dut1.g_uartWriteValidFlg;
	dut1.g_uartReadValidFlg;
	dut1.g_uartRecAddrBuf;
	dut1.g_uartLnkChk;
	dut1.g_uartTranDataBuf;

	dut1.g_uartPatternNum = 0x0f;
	dut1.g_result_output_ch = 0;

	//pattern state//
	dut1.g_dut_pattern_status_buf[0]= 0x00;
	dut1.g_dut_pattern_status_buf[1]= 0x00;
	dut1.g_dut_pattern_status_buf[2]= 0x00;
	dut1.g_dut_pattern_status_buf[3]= 0x00;
	dut1.g_dut_pattern_status_buf[4]= 0x00;
	dut1.g_dut_pattern_status_buf[5]= 0x00;

	dut1.g_axiTmr0Cnt=0;
	dut1.g_axiTmr1Cnt=0;
	dut0.g_axiTmr2Cnt=0;


	dut1.g_trigSendFT2ResultFlg=0;
	dut1.g_ft2Result=0;
	dut1.g_ft2ResultCnt=0;
	dut1.g_ft2StartFlg=0;
	dut1.g_ft2StartReLoadFlg=0;
	dut1.g_ft2StartReloadCnt=0;

	dut1.g_vmoncompare_process_bit=0;
	dut1.g_vmon_compare_step=0;
	dut1.g_start_smbus_timer = 0xffffffff;
	dut1.g_start_smbus_retry = 0x2;
	dut1.g_smbus_writeblock_status = 0;
	dut1.g_test_count=0;

	dut1.g_adcOpaFlg=0;
	dut1.g_adcChSel=0;
	dut1.g_adcData=0;

	dut1.g_dacOpaFlg=0;
	dut1.g_dacChSel=0;
	dut1.g_dacGainSel=0;
	dut1.g_dacTransDataL=0;
	dut1.g_dacTransDataH=0;

	dut1.g_flashDLStart=0;
	dut1.g_flashSize=0;
	dut1.g_flashMCMEraseEn=1;
	dut1.g_flashMCMRdAccChkEn=1;
	dut1.g_flashRdCompEn=1;
	dut1.g_flashRdCompResult=0;
	dut1.g_flashMCMRdAccValue=0;

	dut1.g_ad7994ConversionStart=0;
	dut1.g_ad7994ChSel=0;
	dut1.g_ad7994RrevCh=0x55; // initial the register with a value that different from g_ad7994ChSel
	dut1.g_ad7994DataLowByte=0;
	dut1.g_ad7994DataHighByte=0;
	dut1.g_ad7994AvgPionts=0;

	dut1.g_ccdet_retest_signbit = 0x00;
	dut1.g_efuse_status = 0;
	dut1.g_efuse_valid_ldo3v3 = 0;
	dut1.g_efuse_data_ldo3v3 = 0;
	for(i=0;i<10;i++)
	{
		dut1.g_ccdet_calibration_data_buf[i] = 0x88;
	}

	for(i=0;i<31;i++)
	{
		dut1.g_pattern_smbus_control_buf[i] = 0x00;
	}
	dut1.g_smbus_getstatus_timer = 0x02;


	//dut2
	dut2.g_uartRecBuf[4];
	dut2.g_uartRecBufNum=0;
	dut2.g_uartRecDataBuf;
	dut2.g_uartRecAddrBufL;
	dut2.g_uartRecAddrBufH;
	dut2.g_uartStartReadFlag=0;
	dut2.g_uartStartWriteFlag=0;
	dut2.g_uartRecAddrBufCnt;
	dut2.g_uartRecDataBufNum;
	dut2.g_uartWriteValidFlg;
	dut2.g_uartReadValidFlg;
	dut2.g_uartRecAddrBuf;
	dut2.g_uartLnkChk;
	dut2.g_uartTranDataBuf;

	dut2.g_uartPatternNum = 0x0f;
	dut2.g_result_output_ch = 0;


	//pattern state//
	dut2.g_dut_pattern_status_buf[0]= 0x00;
	dut2.g_dut_pattern_status_buf[1]= 0x00;
	dut2.g_dut_pattern_status_buf[2]= 0x00;
	dut2.g_dut_pattern_status_buf[3]= 0x00;
	dut2.g_dut_pattern_status_buf[4]= 0x00;
	dut2.g_dut_pattern_status_buf[5]= 0x00;

	dut2.g_pattern_step = 0x00;

	//smbus state//
	dut2.g_smbus_status_buf[0] = 0x00;
	dut2.g_smbus_status_buf[1] = 0x0f;


	dut2.g_axiTmr0Cnt=0;
	dut2.g_axiTmr1Cnt=0;
	dut2.g_axiTmr2Cnt=0;


	dut2.g_trigSendFT2ResultFlg=0;
	dut2.g_ft2Result=0;
	dut2.g_ft2ResultCnt=0;
	dut2.g_ft2StartFlg=0;
	dut2.g_ft2StartReLoadFlg=0;
	dut2.g_ft2StartReloadCnt=0;

	dut2.g_vmoncompare_process_bit=0;
	dut2.g_vmon_compare_step=0;
	dut2.g_start_smbus_timer = 0xffffffff;
	dut2.g_start_smbus_retry = 0x2;
	dut2.g_smbus_writeblock_status = 0;
	dut2.g_test_count=0;

	dut2.g_adcOpaFlg=0;
	dut2.g_adcChSel=0;
	dut2.g_adcData=0;

	dut2.g_dacOpaFlg=0;
	dut2.g_dacChSel=0;
	dut2.g_dacGainSel=0;
	dut2.g_dacTransDataL=0;
	dut2.g_dacTransDataH=0;

	dut2.g_flashDLStart=0;
	dut2.g_flashSize=0;
	dut2.g_flashMCMEraseEn=1;
	dut2.g_flashMCMRdAccChkEn=1;
	dut2.g_flashRdCompEn=1;
	dut2.g_flashRdCompResult=0;
	dut2.g_flashMCMRdAccValue=0;

	dut2.g_ad7994ConversionStart=0;
	dut2.g_ad7994ChSel=0;
	dut2.g_ad7994RrevCh=0x55; // initial the register with a value that different from g_ad7994ChSel
	dut2.g_ad7994DataLowByte=0;
	dut2.g_ad7994DataHighByte=0;
	dut2.g_ad7994AvgPionts=0;

	dut2.g_ccdet_retest_signbit = 0x00;
	dut2.g_efuse_status = 0;
	dut2.g_efuse_valid_ldo3v3 = 0;
	dut2.g_efuse_data_ldo3v3 = 0;
	for(i=0;i<10;i++)
	{
		dut2.g_ccdet_calibration_data_buf[i] = 0x88;
	}

	//smbus control state//
	for(i=0;i<31;i++)
	{
		dut2.g_pattern_smbus_control_buf[i] = 0x00;
	}

	dut2.g_smbus_getstatus_timer = 0x02;



	//dut3
	dut3.g_uartRecBuf[4];
	dut3.g_uartRecBufNum=0;
	dut3.g_uartRecDataBuf;
	dut3.g_uartRecAddrBufL;
	dut3.g_uartRecAddrBufH;
	dut3.g_uartStartReadFlag=0;
	dut3.g_uartStartWriteFlag=0;
	dut3.g_uartRecAddrBufCnt;
	dut3.g_uartRecDataBufNum;
	dut3.g_uartWriteValidFlg;
	dut3.g_uartReadValidFlg;
	dut3.g_uartRecAddrBuf;
	dut3.g_uartLnkChk;
	dut3.g_uartTranDataBuf;

	dut3.g_uartPatternNum = 0x0f;
	dut3.g_result_output_ch = 0;

	//pattern state//
	dut3.g_dut_pattern_status_buf[0]= 0x00;
	dut3.g_dut_pattern_status_buf[1]= 0x00;
	dut3.g_dut_pattern_status_buf[2]= 0x00;
	dut3.g_dut_pattern_status_buf[3]= 0x00;
	dut3.g_dut_pattern_status_buf[4]= 0x00;
	dut3.g_dut_pattern_status_buf[5]= 0x00;

	dut3.g_axiTmr0Cnt=0;
	dut3.g_axiTmr1Cnt=0;
	dut3.g_axiTmr2Cnt=0;


	dut3.g_trigSendFT2ResultFlg=0;
	dut3.g_ft2Result=0;
	dut3.g_ft2ResultCnt=0;
	dut3.g_ft2StartFlg=0;
	dut3.g_ft2StartReLoadFlg=0;
	dut3.g_ft2StartReloadCnt=0;

	dut3.g_vmoncompare_process_bit=0;
	dut3.g_vmon_compare_step=0;
	dut3.g_start_smbus_timer = 0xffffffff;
	dut3.g_start_smbus_retry = 0x2;
	dut3.g_smbus_writeblock_status = 0;
	dut3.g_test_count=0;

	dut3.g_adcOpaFlg=0;
	dut3.g_adcChSel=0;
	dut3.g_adcData=0;

	dut3.g_dacOpaFlg=0;
	dut3.g_dacChSel=0;
	dut3.g_dacGainSel=0;
	dut3.g_dacTransDataL=0;
	dut3.g_dacTransDataH=0;

	dut3.g_flashDLStart=0;
	dut3.g_flashSize=0;
	dut3.g_flashMCMEraseEn=1;
	dut3.g_flashMCMRdAccChkEn=1;
	dut3.g_flashRdCompEn=1;
	dut3.g_flashRdCompResult=0;
	dut3.g_flashMCMRdAccValue=0;

	dut3.g_ad7994ConversionStart=0;
	dut3.g_ad7994ChSel=0;
	dut3.g_ad7994RrevCh=0x55; // initial the register with a value that different from g_ad7994ChSel
	dut3.g_ad7994DataLowByte=0;
	dut3.g_ad7994DataHighByte=0;
	dut3.g_ad7994AvgPionts=0;

	dut3.g_ccdet_retest_signbit = 0x00;
	dut3.g_efuse_status = 0;
	dut3.g_efuse_valid_ldo3v3 = 0;
	dut3.g_efuse_data_ldo3v3 = 0;
	for(i=0;i<10;i++)
	{
		dut3.g_ccdet_calibration_data_buf[i] = 0x88;
	}

	for(i=0;i<31;i++)
	{
		dut3.g_pattern_smbus_control_buf[i] = 0x00;
	}
	dut3.g_smbus_getstatus_timer = 0x02;

}
