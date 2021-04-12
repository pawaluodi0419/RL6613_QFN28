/*
 * uart_drv.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef UART_DRV_H_
#define UART_DRV_H_

/****************************************************************************/
/**
*
* Check to see if the receiver has data.
*
* @param	BaseAddress is the  base address of the device
*
* @return	TRUE if the receiver is Full, FALSE if it isn't full.
*
* @note		C-style Signature:
*		int XUartLite_IsReceiveEmpty(u32 BaseAddress);
*
*****************************************************************************/
#define XUartLite_IsReceiveFull(BaseAddress) \
  ((XUartLite_GetStatusReg((BaseAddress)) & XUL_SR_RX_FIFO_FULL) == \
	XUL_SR_RX_FIFO_FULL)



#endif /* UART_DRV_H_ */
