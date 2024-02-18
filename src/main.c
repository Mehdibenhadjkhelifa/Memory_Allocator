#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

void* global_base = NULL;
#define META_SIZE sizeof(block_meta)
typedef struct block_meta{
    size_t size;
    struct block_meta* next;
    int free;
    int magic;
}block_meta;

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

int main(void){
    printf("size of meta block is %lu\n",META_SIZE);
    printf("size of size_t : %zu\n size of void* : %lu\n size of int : %lu\n",sizeof(size_t),sizeof(void*),sizeof(int));
}
