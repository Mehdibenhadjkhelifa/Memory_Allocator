#include <stdio.h>

#include "memory.h"
#include "core.h"

void* global_base = NULL;


int main(void){
    printf("size of meta block is %lu\n",META_SIZE);
    printf("size of size_t : %zu\n size of void* : %lu\n size of int : %lu\n",sizeof(size_t),sizeof(void*),sizeof(int));
}
