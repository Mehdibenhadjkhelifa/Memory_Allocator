#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
void* heap_alloc(size_t size){
    void* p = sbrk(0);
    void* request = sbrk((ssize_t)size);
    if(request == (void*) -1){
        fprintf(stderr,"Sbrk failed to allocate %zu bytes\n",size);
       return NULL;
    }
    else{
        assert(p == request);//not thread safe 
        fprintf(stdout,"successfully increased space by %zu bytes\n",size);
        return p;                     
    } 
}
int main(void){
    size_t arr_size = 5;
    int* test = (int*)heap_alloc( arr_size * sizeof(int));
    for(size_t i = 0;i<arr_size; i++){
        test[i] = (int)i;
    }
    for(size_t i = 0;i< arr_size; i++){
        printf("test of %zu is : %d\n",i,test[i]);
    }
}
