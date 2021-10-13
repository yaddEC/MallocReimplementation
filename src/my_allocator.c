#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "metadata.h"

static Data *base = NULL;

Data *metaInit(int size)
{
    Data *init = NULL;
    init = sbrk(sizeof(Data));
    init->occupy = true;
    init->size = size + sizeof(Data);
    init->next = NULL;
    init->memoryAdress = sbrk(size); //adresse de la memoire allouer
    init->next = sbrk(0);            // initialisation de la prochaine struct data dans la struct actuelle
    init->next->size = 0;            // initialisation de la condition pour la boucle  (la condition NULL n'est pas possible)
    return init;
}

void debugInfo()
{
    Data *cur = base;

    while (cur->size != 0)
    {
        printf("data adress = %p|| memory adress = %p || allocated size = %d || total size = %d|| next data = %p ||occupy =%s \n", cur, cur->memoryAdress, cur->size - 24, cur->size, cur->next, cur->occupy ? "true" : "false");
        cur = cur->next;
    }
    printf("\n");
}

void split(Data *cur, int size)
{
    char *curData = cur;
    Data *newMetadata = curData + sizeof(Data) + size;
    newMetadata->occupy = false;
    newMetadata->size = cur->size - sizeof(Data) - size;
    newMetadata->next = cur->next;
    cur->next = newMetadata;
    cur->size = cur->size - newMetadata->size;
    newMetadata->memoryAdress = newMetadata + sizeof(Data);
}

Data *findData(Data *meta, int size)
{
    Data *cur = base;
    while (cur->size != 0)
    {
        if (cur->size == size + 24 && cur->occupy == false) // si la memoire n'est pas occupe ET si la taille est  suffisante
        {
            cur->size = size + sizeof(Data);
            cur->occupy = true;
            meta = cur;
            return meta;
        }
        else if (cur->size > size + 24 && cur->occupy == false) // si la memoire n'est pas occupe ET si la taille est superieur
        {
            split(cur, size);
            cur->occupy = true;
            return cur;
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

void *my_calloc(int number, int size)
{
    char *callmeta = my_alloc(number * size);
    for (int i = 0; i < number * size; i++)
    {
        callmeta[i] = 0;
    }
    return callmeta;
}

void *my_realloc(void *ptr, int size)
{
    Data *cur = base;
    while (cur->size != 0)
    {
        if (cur->next->memoryAdress == ptr && cur->size + cur->next->size >= size && cur->occupy == false) // si la memoire precedente a celle qu'on recherche est libre   ET   que leurs tailles combine est sup ou egal a celle du param
        {
            char *memcache=NULL;
            int oldsize = cur->next->size;
            for (int i = 0; i < oldsize; i++)
            {
                memcache[i] = cur->next->memoryAdress+i;
            }


            if (cur->size + oldsize > size)
            {
                split(cur, size);
            }
            my_free(cur->next);
           
                cur->memoryAdress= memcache;

            cur->occupy = true;
        }
    }
}
 