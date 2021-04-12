/*
 * spi_flash_drv.h
 *
 *  Created on: 2014-3-9
 *      Author: Administrator
 */
#include "xspi.h"


#define sFLASH_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /*!< Write enable instruction */
#define sFLASH_CMD_READ           0x03  /*!< Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /*!< Read identification */
#define sFLASH_CMD_SE             0x20  /*!< Sector Erase instruction */
#define sFLASH_CMD_BE             0xD8  /*!< Bulk Erase instruction */
#define sFLASH_CMD_CE             0x60  /*!< Chip Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */
#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100


/*
 * SPI Flash define
 */
#define SPI_SS_L                 0xFFFFFFFE
#define SPI_SS_H                 0xFFFFFFFF

#define sFLASH_CS_LOW(SPI_BASEADDR)           XSpi_WriteReg(SPI_BASEADDR, XSP_SSR_OFFSET, SPI_SS_L)
#define sFLASH_CS_HIGH(SPI_BASEADDR)          XSpi_WriteReg(SPI_BASEADDR, XSP_SSR_OFFSET, SPI_SS_H)


//
#define SRC_FLASH_DEV0_ADDR 	XPAR_AXI_SPI_2_BASEADDR
#define MCM_FLASH_DEV0_ADDR 	XPAR_AXI_SPI_3_BASEADDR


void sFLASH_WriteEnable(u32 SPI_BASEADDR);

void sFLASH_WaitForWriteEnd(u32 SPI_BASEADDR);

void sFLASH_EraseSector(u32 SPI_BASEADDR,u32 SectorAddr);

void sFLASH_EraseBulk(u32 SPI_BASEADDR); //this function has problem.

void sFLASH_EraseChip(u32 SPI_BASEADDR);

void sFLASH_WritePage(u32 SPI_BASEADDR,u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);

void sFLASH_WriteBuffer(u32 SPI_BASEADDR,u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);

void sFLASH_ReadBuffer(u32 SPI_BASEADDR,u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

u32 sFLASH_ReadID(u32 SPI_BASEADDR);

void sFLASH_StartReadSequence(u32 SPI_BASEADDR,u32 ReadAddr);

u8 proMcmFlash(u32 srcFlashDevAddr, u32 mcmFlashDevAddr,u8 proSize ,u8 accCheckEn, u8 eraseMcmBeforeProEn, u8 readCompEn);
