#include "src/BufferQueue.h"
#include <string.h>

int main()
{
    BufferQueue q(0);

    puts("checking initial data");
    if (8192 != q.getSize()) {
        fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
        return -1;
    }
    if (0 != q.getCursor()) {
        fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
        return -1;
    }

    puts("enqueue");
    q.enqueue("Hello, World!", 14);
    if (8192 != q.getSize()) {
        fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
        return -1;
    }
    if (14 != q.getCursor()) {
        fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
        return -1;
    }

    puts("dequeue");
    {
        char* buffer;
        size_t size;
        q.dequeue((void**)&buffer, &size);
        if (14 != size) {
            fprintf(stderr, "Invalid size: %ld\n", size);
            return -1;
        }
        if (strcmp(buffer, "Hello, World!")) {
            fprintf(stderr, "Invalid buffer: %s", buffer);
            return -1;
        }
        if (8192 != q.getSize()) {
            fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
            return -1;
        }
        if (0 != q.getCursor()) {
            fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
            return -1;
        }
    }

    puts("enqueue (append)");
    q.enqueue("ABC", 3);
    q.enqueue("DEF", 3);
    q.enqueue("GHI", 3);
    q.enqueue("", 1);
    if (8192 != q.getSize()) {
        fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
        return -1;
    }
    if (10 != q.getCursor()) {
        fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
        return -1;
    }

    puts("dequeue (concat)");
    {
        char* buffer;
        size_t size;
        q.dequeue((void**)&buffer, &size);
        if (10 != size) {
            fprintf(stderr, "Invalid size: %ld\n", size);
            return -1;
        }
        if (strcmp(buffer, "ABCDEFGHI")) {
            fprintf(stderr, "Invalid buffer: %s", buffer);
            return -1;
        }
        if (8192 != q.getSize()) {
            fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
            return -1;
        }
        if (0 != q.getCursor()) {
            fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
            return -1;
        }
    }

    puts("enqueue (expand)");
    for (int i = 0; i < 8192; i++) {
        q.enqueue("Test", 5);
    }
    if (8192 * 5 != q.getSize()) {
        fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
        return -1;
    }
    if (8192 * 5 != q.getCursor()) {
        fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
        return -1;
    }
    q.enqueue("1", 1);
    if (8192 * 6 != q.getSize()) {
        fprintf(stderr, "Invalid buffer size: %ld\n", q.getSize());
        return -1;
    }
    if (8192 * 5 + 1 != q.getCursor()) {
        fprintf(stderr, "Invalid cursor: %ld\n", q.getCursor());
        return -1;
    }

    puts("succeed.");
    return 0;
}