#include "Flash.h"

void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

int Flash_Write(ioAddress address, ioData data)
{
    IO_Write(0x0, 0x40);
    IO_Write(address, data);
    IO_Read(0);
    IO_Read(address);
    return FLASH_SUCCESS;
}

