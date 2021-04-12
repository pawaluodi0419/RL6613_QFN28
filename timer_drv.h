/*
 * timer_drv.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef TIMER_DRV_H_
#define TIMER_DRV_H_

//
#define AXI_TIMER_0_CLOCK_PERD  (1000000.0/XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ);
#define AXI_TIMER_1_CLOCK_PERD  (1000000.0/XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ);
#define AXI_TIMER_2_CLOCK_PERD  (1000000.0/XPAR_AXI_TIMER_2_CLOCK_FREQ_HZ);

void Tmr_Counter_100us(u32 BaseAddress , u32 TmrCtrNumber , u16 TmrCount);

void TmrIntvlLoad(u32 BaseAddress,u8 TmrCtrNumber,u32 TmrIntvlValue);

void msdelay(u16 DlyTimeValue);

void usdelay(u16 DlyTimeValue);

#endif /* TIMER_DRV_H_ */
