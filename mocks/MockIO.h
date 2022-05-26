#ifndef D_MockIO_H
#define D_MockIO_H
#include "IO.h"
void MockIO_Create(int maxExpectations);
void MockIO_Destroy(void);
void MockIO_Expect_Write(ioAddress offset, ioData data);
void MockIO_Expect_ReadThenReturn(ioAddress offset, ioData returnData);
void MockIO_Verify_Complete(void);

void MockIO_IO_Write(ioAddress addr, ioData value);
ioData MockIO_IO_Read(ioAddress addr);

#endif