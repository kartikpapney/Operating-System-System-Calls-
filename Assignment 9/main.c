#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>


void* MyMalloc(size_t n) {
    if(n == 0) return NULL;
    void* program_break_location = (void*)sbrk(0);
    void* request = (void*)sbrk(n);
    if(request == (void*)(-1)) {
        return NULL;
    } else {
        return (program_break_location);
    }
}

void Myfree(void *ptr) {
    // void* end_of_data_segment = (void*)sbrk(sizeof(int));
    brk((void*)(sbrk(0) - sizeof(int)));
}

int main() {
    int i, n = 2;
    int *arr;
    int *brr;
    int *crr;
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    arr = (int*)MyMalloc(sizeof(int));
    arr[0] = 10;
    brr = (int*)MyMalloc(sizeof(int));
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    brr = (int*)MyMalloc(sizeof(int));
    brr[0] = 11;
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    printf("%d", arr[0]);
    printf("%d", brr[0]);
    printf("%d", crr[0]);
    Myfree(arr);
    crr = (int*)MyMalloc(sizeof(int));
    crr[0] = 12;
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    printf("%d", arr[0]);
    printf("%d", brr[0]);
    printf("%d", crr[0]);
}