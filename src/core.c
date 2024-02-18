#include <stddef.h>
#include <unistd.h>
#include <assert.h>

#include "core.h"

extern void* global_base;
block_meta* find_free_block(block_meta** last,size_t size){
    block_meta* current = global_base;
    while (current && !(current->free && current->size >= size)){
        *last = current;
        current = current->next;
    }
    return current;
}
block_meta* request_space(block_meta* last,size_t size){
    block_meta* block;
    block = sbrk(0);
    void* request = sbrk((intptr_t)(size + META_SIZE));
    assert((void*)block == request);
    if(request == (void*) -1){
        return NULL;
    }
    if(last)
        last->next = block;
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}
block_meta* get_block_ptr(void* ptr){
    return (block_meta*)ptr - 1;
}
