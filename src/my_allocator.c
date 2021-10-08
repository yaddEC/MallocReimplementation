#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "metadata.h"
#define _DEFAULT_SOURCE

static Data *base = NULL;

void *memoryInit(int size) // definition de la memoire a allouer
{
    void *pointer = sbrk(0);
    sbrk(size);
    return pointer;
}

Data *metaInit(int size)
{
    Data *init = NULL;
    init = sbrk(sizeof(Data));
    init->occupy = true;
    init->size = size;
    init->next = NULL;
    init->memoryAdress = memoryInit(size); //adresse de la memoire allouer
    init->next = sbrk(0);                  // initialisation de la prochaine struct data dans la struct actuelle
    init->next->size = 0;                  // initialisation pour la boucle (ne fonctionne pas )

    return init;
}

Data* findData(Data* meta, int size )
{
    Data *cur = base;
    while (cur->size != 0)
    {
        if (cur->size >= size  && cur->occupy == false) // si la memoire est n'est pas occupe ET si la taille est suffisante 
        {
            cur->size = size;
            cur->occupy = true;
            meta = cur;
            return meta;
        }
        cur = cur->next;
    }
    return meta;
}

void *my_alloc(int size)
{
    Data *meta = NULL;
    if (base == NULL) // verification si le head existe
    {
        base = metaInit(size);
        return base->memoryAdress;
        }
    else
    {
    meta = findData(meta, size);
    }
    if (meta == NULL)
    {
        meta = metaInit(size);
    }
    return meta->memoryAdress;
}


void my_free(void *ptr)
{

    Data *cur = base;
    while (cur->size != 0)
    {
        if (cur->memoryAdress == ptr)
        {
            cur->occupy = false;
            break;
        }

        cur = cur->next;
    }
}

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

    return 0;
}
