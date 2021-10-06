#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define _DEFAULT_SOURCE

void *my_malloc(int size); // ??
void my_free(void *ptr);   // ??

int main()
{
    void *brkAddress = sbrk(0);
    printf("break is currently at %p\n", brkAddress);
    brkAddress = sbrk(0);
    printf("break is currently at %p\n", brkAddress);
    int *value;
    value = calloc(10,10*sizeof(int));
    printf("value = %d\n", *value);
    brkAddress = sbrk(0);

    printf("break is currently at %p\n", brkAddress);

    return 0;
}
