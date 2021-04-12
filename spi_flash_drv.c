/*
 * spi_drv.c
 *
 *  Created on: 2014-3-9
 *      Author: Administrator
 */

#include "platform.h"


void sFLASH_WriteEnable(u32 SPI_BASEADDR)  //写使能
{

  sFLASH_CS_LOW(SPI_BASEADDR);  //拉低CS

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_WREN); //发送写使能命令 0x06

  sFLASH_CS_HIGH(SPI_BASEADDR);  //拉高CS
}


void sFLASH_WaitForWriteEnd(u32 SPI_BASEADDR)  //等待写结束
{
  u8 flashstatus = 0;

  sFLASH_CS_LOW(SPI_BASEADDR);  //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_RDSR);  //读状态寄存器

  XSpi_ReadReg(SPI_BASEADDR,XSP_DRR_OFFSET);  // clear SPI receive buffer
  do
  {

	Spi_SendByte(SPI_BASEADDR,0,sFLASH_DUMMY_BYTE);
    flashstatus = Spi_GetReceByte(SPI_BASEADDR); //独到状态寄存器信息

  }
  while (flashstatus & sFLASH_WIP_FLAG); //判断是否正在写入


  sFLASH_CS_HIGH(SPI_BASEADDR); //拉高CS
}


void sFLASH_EraseSector(u32 SPI_BASEADDR,u32 SectorAddr) //擦扇区  stm25p128 的 扇区擦除命令码 = w25x16的块擦除命令码
{
  sFLASH_WriteEnable(SPI_BASEADDR); //写使能

  sFLASH_CS_LOW(SPI_BASEADDR);  //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_SE); //擦扇区命令

  Spi_SendByte(SPI_BASEADDR,0,(u8)((SectorAddr & 0xFF0000) >> 16)); //发送地址
  Spi_SendByte(SPI_BASEADDR,0,(u8)((SectorAddr & 0xFF00) >> 8));
  Spi_SendByte(SPI_BASEADDR,0,(u8)(SectorAddr & 0xFF));

  sFLASH_CS_HIGH(SPI_BASEADDR);  //拉高CS


  sFLASH_WaitForWriteEnd(SPI_BASEADDR);  //等待写结束
}


void sFLASH_EraseBulk(u32 SPI_BASEADDR) //擦块   stm25p128 的 块擦除相命令码 = w25x16的芯片擦除命令码
{
  sFLASH_WriteEnable(SPI_BASEADDR);//写使能

  sFLASH_CS_LOW(SPI_BASEADDR);//拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_BE);//擦块命令

  sFLASH_CS_HIGH(SPI_BASEADDR);//拉高CS

  sFLASH_WaitForWriteEnd(SPI_BASEADDR);  //等待写结束
}



void sFLASH_EraseChip(u32 SPI_BASEADDR) //chip erase
{
  sFLASH_WriteEnable(SPI_BASEADDR);//写使能

  sFLASH_CS_LOW(SPI_BASEADDR);//拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_CE);//擦块命令

  sFLASH_CS_HIGH(SPI_BASEADDR);//拉高CS

  sFLASH_WaitForWriteEnd(SPI_BASEADDR);  //等待写结束
}



void sFLASH_WritePage(u32 SPI_BASEADDR,u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)  //写页
{

  sFLASH_WriteEnable(SPI_BASEADDR);  //写使能

  sFLASH_CS_LOW(SPI_BASEADDR);   //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_WRITE);  //写命令

  Spi_SendByte(SPI_BASEADDR,0,(u8)((WriteAddr & 0xFF0000) >> 16)); //地址
  Spi_SendByte(SPI_BASEADDR,0,(u8)((WriteAddr & 0xFF00) >> 8));
  Spi_SendByte(SPI_BASEADDR,0,(u8)(WriteAddr & 0xFF));

  while (NumByteToWrite--)   //写NumByteToWrite个数据 要小于256个
  {

	  Spi_SendByte(SPI_BASEADDR,0,*pBuffer);

    pBuffer++;
  }

  sFLASH_CS_HIGH(SPI_BASEADDR);  //拉高cs

  sFLASH_WaitForWriteEnd(SPI_BASEADDR);  //等写结束
}


void sFLASH_WriteBuffer(u32 SPI_BASEADDR,u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)  //写缓存数据  适用于各种情况
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = (u8)(WriteAddr % sFLASH_SPI_PAGESIZE);     //得到除256余下的地址码
  count = (u8)(sFLASH_SPI_PAGESIZE - Addr);         //余下地址码还差多少到256
  NumOfPage = (u8)(NumByteToWrite / sFLASH_SPI_PAGESIZE);  //有几个整页
  NumOfSingle = (u8)(NumByteToWrite % sFLASH_SPI_PAGESIZE); //有多少个零头

  if (Addr == 0) //当地址整除256
  {
    if (NumOfPage == 0) //要写入的数据小于256
    {
      sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, NumByteToWrite);
    }
    else //要写入的数据大于256
    {
      while (NumOfPage--)
      {
        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else //地址不是256整倍数
  {
    if (NumOfPage == 0) //要写入的小于256
    {
      if (NumOfSingle > count) //零头大于到256整数倍地址还差的个数,也就是 地址+零头 超过256倍数,需要拆分
      {
        temp = (u8)(NumOfSingle - count);

        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, temp);
      }
      else
      {
        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else //要写的个数的大于256
    {
      NumByteToWrite -= count;
      NumOfPage =  (u8)(NumByteToWrite / sFLASH_SPI_PAGESIZE);
      NumOfSingle = (u8)(NumByteToWrite % sFLASH_SPI_PAGESIZE);

      sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      if (NumOfSingle != 0)
      {
        sFLASH_WritePage(SPI_BASEADDR,pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}


void sFLASH_ReadBuffer(u32 SPI_BASEADDR,u8* pBuffer, u32 ReadAddr, u16 NumByteToRead) //读取数据
{
  sFLASH_CS_LOW(SPI_BASEADDR);  //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_READ); //读命令

  Spi_SendByte(SPI_BASEADDR,0,(u8)((ReadAddr & 0xFF0000) >> 16));  //地址
  Spi_SendByte(SPI_BASEADDR,0,(u8)((ReadAddr& 0xFF00) >> 8));
  Spi_SendByte(SPI_BASEADDR,0,(u8)(ReadAddr & 0xFF));


  XSpi_ReadReg(SPI_BASEADDR,XSP_DRR_OFFSET);  // clear SPI receive buffer
  while (NumByteToRead--) //while到读取结束
  {

	Spi_SendByte(SPI_BASEADDR,0,sFLASH_DUMMY_BYTE);
	*pBuffer  = Spi_GetReceByte(SPI_BASEADDR); //独到状态寄存器信息

    pBuffer++;
  }

  sFLASH_CS_HIGH(SPI_BASEADDR);
}


u32 sFLASH_ReadID(u32 SPI_BASEADDR)  //读ID
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  sFLASH_CS_LOW(SPI_BASEADDR);  //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,0x9F); //READ ID命令 9F

  XSpi_ReadReg(SPI_BASEADDR,XSP_DRR_OFFSET);  // clear SPI receive buffer

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_DUMMY_BYTE);
  Temp0 =  Spi_GetReceByte(SPI_BASEADDR);  //读出ID

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_DUMMY_BYTE);
  Temp1 =  Spi_GetReceByte(SPI_BASEADDR);  //读出ID

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_DUMMY_BYTE);
  Temp2 =  Spi_GetReceByte(SPI_BASEADDR);  //读出ID

  sFLASH_CS_HIGH(SPI_BASEADDR);  //拉高CS

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;  //合并数据

  return Temp;
}


void sFLASH_StartReadSequence(u32 SPI_BASEADDR,u32 ReadAddr)  //读数据起始序列
{
  sFLASH_CS_LOW(SPI_BASEADDR); //拉低cs

  Spi_SendByte(SPI_BASEADDR,0,sFLASH_CMD_READ); //读命令

  Spi_SendByte(SPI_BASEADDR,0,(u8)((ReadAddr & 0xFF0000) >> 16));  //地址

  Spi_SendByte(SPI_BASEADDR,0,(u8)((ReadAddr& 0xFF00) >> 8));

  Spi_SendByte(SPI_BASEADDR,0,(u8)(ReadAddr & 0xFF));

  //need CS pull high？

}


u8 proMcmFlash(u32 srcFlashDevAddr, u32 mcmFlashDevAddr,u8 proSize ,u8 accCheckEn, u8 eraseMcmBeforeProEn, u8 readCompEn)
{
	u8 i,j,k;
    u8 FLASH_RXBuff[256];
    u8 FLASH_RdCompBuff[256];
    u8 proResult=1;  // set the read compare result as pass.
    u32 temp;
    u32 rdAccValue;

//	XGpio_0_WriteBit(0,LED_D7_OFFSET,1);

	rdAccValue=0; //clear the read acc value.


	temp=sFLASH_ReadID(srcFlashDevAddr);
	temp=sFLASH_ReadID(mcmFlashDevAddr);
	if(eraseMcmBeforeProEn){                //erase MCM Flash
		sFLASH_EraseChip(mcmFlashDevAddr);
	}

	for(j=0;j<=proSize;j++){    //64K program loop

		if(!proResult){  //jump out the 64K program loop if read compare fail
			break;
		}

		for(i=0;i<=255;i++){     //page program loop

			if(!proResult){  //jump out the page program loop if read compare fail
				break;
			}

			sFLASH_ReadBuffer(srcFlashDevAddr,FLASH_RXBuff, i*256+j*65536, 256); //read page from source flash
			sFLASH_WritePage(mcmFlashDevAddr,FLASH_RXBuff, i*256+j*65536, 256); //write page to MCM flash

			if(readCompEn){  //read compare
				sFLASH_ReadBuffer(mcmFlashDevAddr,FLASH_RdCompBuff, i*256+j*65536, 256); //read page from MCM flash
				for(k=0;k<=255;k++){
					if(FLASH_RXBuff[k]!=FLASH_RdCompBuff[k]){
						proResult=0;
						break;
					}

					if(accCheckEn){
						rdAccValue=FLASH_RdCompBuff[k]+rdAccValue;
					}
				}
			}
		}

	}


//	XGpio_0_WriteBit(0,LED_D7_OFFSET,0); // program ended indicator

	return proResult;


}
