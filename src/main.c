#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define _DEFAULT_SOURCE

void *my_malloc(int size); // ??
void my_free(void *ptr);   // ??


int main()
{
    printf("Starting...");
    int *a = my_alloc(sizeof(int));
    *a = 10;
    printf("(malloc) a = %d, memory adress= %p\n", *a, a);

    int *b = my_alloc(sizeof(int));
    *b = 20;
    printf("(malloc) b = %d,  memory adress= %p\n", *b, b);

    my_free(a);

    int *c = my_alloc(sizeof(int));
    *c = 90;
    printf("(malloc) c = %d,  memory adress= %p\n", *c, c);

    my_free(b);
    my_free(c);

    return 0;
}

