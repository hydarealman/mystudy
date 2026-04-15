#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void) {
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID) {
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MYSPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MYSPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= MYSPI_SwapByte(W25Q64_DUMMY_BYTE);
	MySPI_Stop();
}

void W25Q64_WriteEnable(void) {
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void) {
	uint32_t Timeout;
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	Timeout = 100000;
	while((MYSPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		Timeout--;
		if (Timeout == 0) {
			break;
		}
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count) {
	uint16_t i;
	W25Q64_WriteEnable();
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MYSPI_SwapByte(Address >> 16);
	MYSPI_SwapByte(Address >> 8);
	MYSPI_SwapByte(Address);
	for (i = 0; i < Count; i++) {
		MYSPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
}

void W25Q64_SectorErase(uint32_t Address) {
	W25Q64_WriteEnable();
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MYSPI_SwapByte(Address >> 16);
	MYSPI_SwapByte(Address >> 8);
	MYSPI_SwapByte(Address);
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count) {
	uint16_t i;
	MySPI_Start();
	MYSPI_SwapByte(W25Q64_READ_DATA);
	MYSPI_SwapByte(Address >> 16);
	MYSPI_SwapByte(Address >> 8);
	MYSPI_SwapByte(Address);
	for (i = 0; i < Count; i++) {
		DataArray[i] = MYSPI_SwapByte(W25Q64_DUMMY_BYTE); // 发送FF置换回有用的数据
	}
	MySPI_Stop();
}




