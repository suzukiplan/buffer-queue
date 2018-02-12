#include "BufferQueue.h"
#include <string.h>
#include <stdlib.h>

BufferQueue::BufferQueue(size_t iSize) {
    size = ((iSize / BUFFER_BLOCK_SIZE) + 1) * BUFFER_BLOCK_SIZE;
    cursor = 0;
    buffer = malloc(size);
    if (!buffer) size = 0;
}

BufferQueue::~BufferQueue() {
    if (buffer) free(buffer);
}

bool BufferQueue::enqueue(const void *aBuffer, const size_t aSize) {
    if (size - cursor < aSize) {
        size_t newSize = ((size + aSize) / BUFFER_BLOCK_SIZE + 1) * BUFFER_BLOCK_SIZE;
        void *newBuffer = malloc(newSize);
        if (!newBuffer) return false;
        memcpy(newBuffer, buffer, cursor);
        free(buffer);
        buffer = newBuffer;
        size = newSize;
    }
    memcpy(((char *) this->buffer) + cursor, aBuffer, aSize);
    cursor += aSize;
    return true;
}

void BufferQueue::dequeue(void **oBuffer, size_t *oSize) {
    if (cursor) {
        *oBuffer = buffer;
        *oSize = cursor;
        cursor = 0;
    } else {
        *oBuffer = NULL;
        *oSize = 0;
    }
}
