#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "metadata.h"


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
    init->next->size = 0;                  // initialisation de la condition pour la boucle  (la condition NULL n'est pas possible)

    return init;
}

void debugInfo()
{
    Data *cur = base;

    while (cur->size != 0)
    {

        printf("data adress = %p|| memory adress = %p || size = %d || next data = %p ||occupy =%s \n", cur, cur->memoryAdress, cur->size, cur->next, cur->occupy ? "true" : "false");
        cur = cur->next;
    }

    printf("\n");
}

Data *split(Data *cur, int size)
{

    void *cache = cur->next;
    sbrk(sizeof(Data));
    cur->occupy = true;

    cur->next = sbrk(0);
    cur->next->next = cache;
    cur->next->size = cur->size - size;
    cur->size = size;

    cur->next->memoryAdress = cur->memoryAdress + size;
    brk(cur->next);
    cur->next->occupy = false;
    return cur;
}

Data *findData(Data *meta, int size)
{
    Data *cur = base;
    while (cur->size != 0)
    {
        if (cur->size == size && cur->occupy == false) // si la memoire n'est pas occupe ET si la taille est  suffisante
        {
            cur->size = size;
            cur->occupy = true;
            meta = cur;
            return meta;
        }
        else if (cur->size > size && cur->occupy == false) // si la memoire n'est pas occupe ET si la taille est superieur
        {
            return split(cur, size);
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
        meta = findData(meta, size); //verification si de la memoire deja alloue est free
    }
    if (meta == NULL)
    {
        meta = metaInit(size);
    }
    return meta->memoryAdress;
}

bool mergeOrNot(Data *cur, void *ptr)
{
    if ((cur->next->memoryAdress == ptr && cur->occupy == false) || (cur->memoryAdress == ptr && cur->next->occupy == false)) // si la memoire que l'on free est a cote d'une memoire libre
    {
        cur->size += cur->next->size;
        cur->occupy = false;
        cur->next = cur->next->next;
        return true;
    }
    return false;
}

void my_free(void *ptr)
{

    Data *cur = base;
    while (cur->size != 0)
    {
        if (mergeOrNot(cur, ptr) == true)
            break;

        else if (cur->memoryAdress == ptr)
        {
            cur->occupy = false;
            break;
        }
        cur = cur->next;
    }
}
