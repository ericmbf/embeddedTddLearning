#include "CircularBuffer.h"

#include <stdlib.h>
#include <string.h>

typedef struct CircularBufferStruct
{
    int count;
    int index;
    int outdex;
    int capacity;
    int *values;

} CircularBufferStruct;

enum {BUFFER_GUARD = -999};

CircularBuffer CircularBuffer_Create(uint8_t capacity)
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

int CircularBuffer_IsEmpty(CircularBuffer self)
{
    return self->count == 0;
}

int CircularBuffer_IsFull(CircularBuffer self)
{
    return self->count == self->capacity;
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

int CircularBuffer_Capacity(CircularBuffer self)
{
    return self->capacity;
}

bool CircularBuffer_remove(int32_t *pl_value)
{
    bool b_ret = false;

    return b_ret;
}

bool CircularBuffer_isFull()
{
    return false;
}