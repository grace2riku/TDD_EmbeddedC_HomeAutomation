#ifndef D_IO_H
#define D_IO_H
#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint16_t ioData;

ioData IO_Read(ioAddress offset);
void IO_Write(ioAddress offset, ioData data);

#endif