#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

typedef struct CircularBufferStruct* CircularBuffer;

CircularBuffer CircularBuffer_Create(int capacity);
void CircularBuffer_Print(CircularBuffer);
void CircularBuffer_Destroy(CircularBuffer self);
int CircularBuffer_Put(CircularBuffer self, int value);
int CircularBuffer_Get(CircularBuffer self);

#endif /* D_CircularBuffer_H */