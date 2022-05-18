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
    if (self->count >= self->capacity)
        return 0;

    self->count++;
    self->values[self->index++] = value;

    if (self->index >= self->capacity)
        self->index = 0;

    return 1;
}

int CircularBuffer_Get(CircularBuffer self)
{
    int value;

    if (self->count <= 0)
        return 0;
    
    value = self->values[self->outdex++];
    self->count--;

    if (self->outdex >= self->capacity)
        self->outdex = 0;

    return value;
}

void CircularBuffer_Print(CircularBuffer self)
{
    int i;
    int currentValue;

    currentValue = self->outdex;

    FormatOutput("Circular buffer content:\n<");

    for (i = 0; i < self->count; i++) {
        if (i != 0)
            FormatOutput(", ");
        FormatOutput("%d", self->values[currentValue++]);

        if (currentValue >= self->capacity)
            currentValue = 0;
    }

    FormatOutput(">\n");           
}
