#include "blockStorage.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


enum Errors { InvalidFree, NoEnoughMemory, NoPersistMemory, TooBigBlock };
class Ptr {
public:
    BlockStorage::Node* blocks;
public:
    void* get() {
        return (void*)blocks->data;
    }

    Ptr(BlockStorage::Node* block) {
        block->links++;
        blocks = block;
    }

    ~Ptr() {
        
    }
};

class Allocator {
    BlockStorage l;
public:
    Allocator(size_t size) {

        mem = (void*)malloc(size);
        l.head = (BlockStorage::Node*)((char*)mem + size - sizeof(BlockStorage::Node));
        l.tail = l.head;
        l.head = l.newNode(l.head, size, mem, nullptr, nullptr, true, 1);
    }

    ~Allocator()
    {
        free(this->mem);
    }
public:
    void* mem;
    size_t maxblocksize;
    void show_busy_blocks();
    void show_free_blocks();
    void show_hang_blocks();
    Ptr* mem_alloc(size_t size);
    void mem_free(BlockStorage::Node* blk); 
    void mem_realloc(size_t size, size_t new_size); 
    void a_defrag();    void free_hang_blocks(); 
    Ptr* find(size_t size);

};