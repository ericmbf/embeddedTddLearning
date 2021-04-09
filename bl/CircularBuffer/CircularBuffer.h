#include <stdint.h>
#include <stdbool.h>

typedef struct CircularBufferStruct * CircularBuffer;

CircularBuffer CircularBuffer_Create(uint8_t uc_size);
void CircularBuffer_Destroy(CircularBuffer self);
int CircularBuffer_Put(CircularBuffer self, int value);
int CircularBuffer_Get(CircularBuffer);
int CircularBuffer_Capacity(CircularBuffer);
bool CircularBuffer_remove(int32_t *pl_value);
int CircularBuffer_IsEmpty(CircularBuffer self);
int CircularBuffer_IsFull(CircularBuffer self);