#include "CircularBuffer.h"

static int32_t *gpl_buffer = 0;
static int8_t gc_head = -1;
static int8_t gc_tail = -1;
static uint8_t guc_size = 0;
static uint8_t guc_cnt = 0;

void CircularBuffer_init(uint8_t *puc_buffer, uint8_t uc_size)
{
    gpl_buffer = (int32_t*) puc_buffer;
    guc_size = uc_size;
    guc_cnt = 0;
    gc_head = -1;
    gc_tail = -1;
}

bool CircularBuffer_insert(int32_t ul_value)
{
    bool b_ret = false;

    if(guc_cnt < guc_size)
    {
        gpl_buffer[++gc_head] = ul_value;

        if(gc_head == (guc_size - 1))
        {
            gc_head = -1;
        }

        guc_cnt++;
        b_ret = true;
    }

    return b_ret;
}

bool CircularBuffer_remove(int32_t *pl_value)
{
    bool b_ret = false;

    if(guc_cnt)
    {
        *pl_value = gpl_buffer[++gc_tail];

        if (gc_tail == (guc_size - 1))
        {
            gc_tail = -1;
        }

        guc_cnt--;
    }

    return b_ret;
}

bool CircularBuffer_isFull()
{
    return false;
}