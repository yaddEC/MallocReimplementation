#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "metadata.h"
#define _DEFAULT_SOURCE

static Adress *base = NULL;

Data *metaInit(int size)
{
    Data *init = NULL;
    init = sbrk(1);
    init->occupy = true;
    init->size = size;
    sbrk(4);
    init->next = NULL;
    sbrk(sizeof(8));

    init->next = sbrk(0);
    return init;
}

Adress *adressInit(size)
{
    Adress *memory = NULL;
    memory->head = metaInit(size);
    memory->memoryAdress=sbrk(0);
    sbrk(size);
    return memory;



}

void *my_alloc(int size)
{
    bool verifyer = false;
    Adress *meta = NULL;

    if (base == NULL)
    {
        base = adressInit(size);
        return base->memoryAdress;
    }
    else
    {
        Adress *cur = base;

        while (cur->head != NULL)
        {
            if (cur->head->size >= (sizeof(Data) + size + 1) && cur->head->occupy == false)
            {
                verifyer = true;

                meta = cur;
                cur->head->occupy = true;
            }

            cur = cur->next;
        }
    }
    if (verifyer == false)
    {
        meta = metaInit(size);
    }

    return &meta->next;
}
void my_free(void *ptr); // ??

int main()
{
    printf("Starting...");

    int *a = my_alloc(sizeof(int));
    *a = 10;
    printf("(malloc) a = %d\n", *a);

    int *b = my_alloc(sizeof(int));
    *b = 20;
    printf("(malloc) b = %d\n", *b);
    return 0;
}
