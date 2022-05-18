#include "CircularBuffer.h"

typedef struct CircularBufferStruct
{
    int count;
    int index;
    int outdex;
    int capacity;
    int* values;
} CircularBufferStruct;

void CircularBuffer_Print(CircularBuffer self)
{
    
}
