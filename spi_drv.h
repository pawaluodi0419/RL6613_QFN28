/*
 * spi_drv.h
 *
 *  Created on: 2017-6-15
 *      Author: kay_yin
 */

#ifndef SPI_DRV_H_
#define SPI_DRV_H_

void Spi_SendByte(u32 BaseAddr,u8 SlvNum,u16 TransData);

u16 Spi_GetReceByte(u32 BaseAddr);

void SpiInitiToMaster();

#endif /* SPI_DRV_H_ */


