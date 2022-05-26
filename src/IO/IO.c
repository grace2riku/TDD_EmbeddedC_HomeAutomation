#include <IO.h>

static void IO_write_impl(ioAddress address, ioData data)
{
    ioData* p = 0;
    *(p + address) = data;
}

static ioData IO_read_impl(ioAddress address)
{
    ioData* p = 0;
    return *(p + address);
}

void (*IO_Write)(ioAddress address, ioData data) = IO_write_impl;
ioData (*IO_Read)(ioAddress address) = IO_read_impl;