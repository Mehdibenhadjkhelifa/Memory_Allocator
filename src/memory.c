#include <stddef.h>
#include <assert.h>

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
