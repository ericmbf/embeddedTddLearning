#include <stdint.h>
#include <stdbool.h>

void CircularBuffer_init(uint8_t *puc_buffer, uint8_t uc_size);
bool CircularBuffer_insert(int32_t ul_value);
bool CircularBuffer_remove(int32_t *pl_value);
bool CircularBuffer_isFull();
