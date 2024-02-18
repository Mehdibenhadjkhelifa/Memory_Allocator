#ifndef _CORE_H
#define _CORE_H
#define META_SIZE sizeof(block_meta)
typedef struct block_meta{
    size_t size;
    struct block_meta* next;
    int free;
    int magic;
}block_meta;

block_meta* find_free_block(block_meta** last,size_t size);
block_meta* request_space(block_meta* last,size_t size);
block_meta* get_block_ptr(void* ptr);
#endif
