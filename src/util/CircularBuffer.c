#include "CircularBuffer.h"
#include "Utils.h"
#include "stdlib.h"

typedef struct CircularBufferStruct
{
    int count;
    int index;
    int outdex;
    int capacity;
    int* values;
} CircularBufferStruct;

enum {BUFFER_GUARD = -999};

CircularBuffer CircularBuffer_Create(int capacity)
{
    CircularBuffer self = calloc(capacity, sizeof(CircularBufferStruct));
    self->capacity = capacity;
    self->values = calloc(capacity + 1, sizeof(int));
    self->values[capacity] = BUFFER_GUARD;
    
    return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
    free(self->values);
    free(self);
}

int CircularBuffer_Put(CircularBuffer self, int value)
{

    return 1;
}

void CircularBuffer_Print(CircularBuffer self)
{
    int i;
    int currentValue;

    currentValue = self->outdex;

    FormatOutput("Circular buffer content:\n<");

    FormatOutput(">\n");           
}
