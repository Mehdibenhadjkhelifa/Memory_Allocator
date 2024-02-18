#ifndef _MEMORY_H
#define _MEMORY_H
void* malloc(size_t size);
void* realloc(void* ptr,size_t size);
void* calloc(size_t nelem,size_t elsize);
void free(void* ptr);
#endif

