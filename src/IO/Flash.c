#include "Flash.h"
#include "m28w160ect.h"

void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

int Flash_Write(ioAddress address, ioData data)
{
    ioData status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    IO_Read(address);

    return FLASH_SUCCESS;
}

