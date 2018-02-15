#include "src/BufferQueue.h"
#include <string.h>
#include <stdlib.h>

int main()
{
    BufferQueue q(0);

    puts("checking initial data");
    if (8192 != q.getSize()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    if (0 != q.getCursor()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }

    puts("enqueue");
    q.enqueue("Hello, World!", 14);
    if (8192 != q.getSize()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    if (14 != q.getCursor()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }

    puts("dequeue");
    {
        char* buffer;
        size_t size;
        q.dequeue((void**)&buffer, &size);
        if (14 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (strcmp(buffer, "Hello, World!")) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (8192 != q.getSize()) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != q.getCursor()) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
    }

    puts("enqueue (append)");
    q.enqueue("ABC", 3);
    q.enqueue("DEF", 3);
    q.enqueue("GHI", 3);
    q.enqueue("", 1);
    if (8192 != q.getSize()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    if (10 != q.getCursor()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }

    puts("dequeue (concat)");
    {
        char* buffer;
        size_t size;
        q.dequeue((void**)&buffer, &size);
        if (10 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (strcmp(buffer, "ABCDEFGHI")) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (8192 != q.getSize()) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != q.getCursor()) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
    }

    puts("enqueue (expand)");
    for (int i = 0; i < 8192; i++) {
        q.enqueue("Test", 5);
    }
    if (8192 * 5 != q.getSize()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    if (8192 * 5 != q.getCursor()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    q.enqueue("1", 1);
    if (8192 * 6 != q.getSize()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }
    if (8192 * 5 + 1 != q.getCursor()) {
        fprintf(stderr, "%d: test failed\n", __LINE__);
        return -1;
    }

    puts("dequeue (limit)");
    {
        char* buffer;
        size_t size;
        q.clear();
        q.enqueue("1234567890", 10);

        q.dequeue((void**)&buffer, &size, 3);
        if (3 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != memcmp(buffer, "123", 3)) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }

        q.dequeue((void**)&buffer, &size, 3);
        if (3 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != memcmp(buffer, "456", 3)) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }

        q.dequeue((void**)&buffer, &size, 3);
        if (3 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != memcmp(buffer, "789", 3)) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }

        q.dequeue((void**)&buffer, &size, 3);
        if (1 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
        if (0 != memcmp(buffer, "0", 1)) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }

        q.dequeue((void**)&buffer, &size, 3);
        if (0 != size) {
            fprintf(stderr, "%d: test failed\n", __LINE__);
            return -1;
        }
    }

    puts("succeed.");
    return 0;
}