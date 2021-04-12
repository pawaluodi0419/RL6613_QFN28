/*
    * Copyright (c) 2008 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef _PatternF_Efuse_DUT_H_
#define _PatternF_Efuse_DUT_H_

#include <math.h>
#include <stdio.h>

//xilix system header file
#include "platform_config.h"
#include "xparameters.h"
#include "xspi.h"
#include "xuartlite_l.h"
#include "xtmrctr_l.h"
#include "xgpio_l.h"
#include "xintc_l.h"
#include "xiic_l.h"


#include "timer_drv.h"
#include "var_initial.h"
#include "smbus_drv.h"
#include "smbus_irq_handle.h"

//#define RCClock_Tolerance_Compare_Data         5
//#define VMON_Tolerance_Compare_Data            3
//#define RP12K_Tolerance_Compare_Data           3
//#define LDO3V3_Tolerance_Compare_Data          3
//#define CCDET_Tolerance_Compare_Data           3
//#define VBUS_3A_Tolerance_Compare_Data         3
//#define VBUS_1P5A_Tolerance_Compare_Data       3
//#define VBUS_0P5A_Tolerance_Compare_Data       3
//#define Loop_run_enable                        0



//extern global statement


u8 _by_PatternF_efuse_dut0();
u8 _by_PatternF_efuse_dut1();
u8 _by_PatternF_efuse_dut2();
u8 _by_PatternF_efuse_dut3();



#endif
