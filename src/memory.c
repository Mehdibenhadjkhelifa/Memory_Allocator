#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "core.h"
#include "memory.h"
extern void* global_base;

void* malloc(size_t size){
    block_meta* block;
    //TODO: Align size
    if(size <= 0)
       return NULL;
    if(!global_base){//First call
        block = request_space(NULL,size);
        if(block == NULL)
            return NULL;
        global_base = block;
    }else{
        block_meta* last = global_base;
        block = find_free_block(&last,size);
        if(block == NULL){//Failed to find free block
            block = request_space(last,size);
            if(!block)
                return NULL;//Requesting memory failed
        }else{
            //TODO: consider splitting block here
            block->free = 0;
            block->magic = 0x77777777;
        }
    }
    return (block+1);
}
void* realloc(void* ptr,size_t size){
    if(!ptr)
        return malloc(size);//NULL ptr. realloc should act like malloc
    block_meta* block_ptr = get_block_ptr(ptr);
    if(block_ptr->size >= size)
        return ptr; //We have enough space . Could free some once we implement split
    // Need to really realloc. Malloc new space and free old space.
    // Then copy old data to new space.
    void* new_ptr = malloc(size);
    if(!new_ptr)
        return NULL; // set errno on failure
    memcpy(new_ptr,ptr,block_ptr->size);
    free(ptr);
    return new_ptr;
}
void* calloc(size_t nelem,size_t elsize){
    size_t size = nelem * elsize; //TODO: check for overflow
    void* ptr = malloc(size);
    memset(ptr,0,size);
    return ptr;
}
void free(void* ptr){
    if(!ptr)
        return;
    //TODO : consider merging blocks once splitting blocks is implemented
    block_meta* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
    block_ptr->free = 1;
    block_ptr->magic =0x55555555;
}
