#ifndef INCLUDE_BUFFER_QUEUE_H
#define INCLUDE_BUFFER_QUEUE_H
#include <stdio.h>

#define BUFFER_BLOCK_SIZE 8192

class BufferQueue {
private:
    void *buffer;
    size_t size;
    size_t cursor;

public:
    BufferQueue(size_t iSize);
    ~BufferQueue();
    bool enqueue(const void *aBuffer, const size_t aSize);
    void dequeue(void **oBuffer, size_t *oSize);
    size_t getSize() {
        return size;
    }
    size_t getCursor() {
        return cursor;
    }
};

#endif
