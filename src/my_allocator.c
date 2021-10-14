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
    char *curData = (char*)cur;
    Data *newMetadata = (Data*)curData + sizeof(Data) + size;
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
    while(size%8!=0){
        size++;
    }

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
    if (((cur->next->memoryAdress == ptr && cur->occupy == false) || (cur->memoryAdress == ptr && cur->next->occupy == false))&&cur->next->size!=0) // si la memoire que l'on free est a cote d'une memoire libre
    {
        cur->size += cur->next->size;
        cur->occupy = false;
        cur->next = cur->next->next;
        return true;
    }
    return false;
}
void isLast(Data *cur)
{
    if(cur->next->size==0){
        brk(sbrk(0)-(cur->size-24));
        cur->size=0;     
    }
}

void my_free(void *ptr)
{

    Data *cur = base;
    while (cur->size != 0)
    {
        if (mergeOrNot(cur, ptr) == true)
        {
           isLast(cur);
            break;
        }
        else if (cur->memoryAdress == ptr)
        {
            cur->occupy = false;
            isLast(cur);
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
    Data *meta = NULL;
    char *curData = NULL;
    while (cur->size != 0)
    {
        if (cur->memoryAdress == ptr && cur->next->size >= size && cur->next->occupy == false) // si la memoire suivante a celle qu'on recherche est libre   ET   que leurs tailles combine est sup ou egal a celle du param
        {
            meta = cur->next;
            curData = meta->memoryAdress;
            if (meta->size > size)
            {
                split(meta, size);
            }
            int oldsize = cur->size;
            char *ptrData = cur->memoryAdress;
            for (int i = 0; i < oldsize; i++)
            {
                curData[i] = ptrData[i];
            }
            meta->occupy = true;
            my_free(cur->memoryAdress);

            return meta;
        }
        else if (cur->memoryAdress == ptr)
        {
            curData = my_alloc(size);
            int oldsize = cur->size;
            char *ptrData = cur->memoryAdress;
            for (int i = 0; i < oldsize; i++)
            {
                curData[i] = ptrData[i];
            }
            my_free(cur->memoryAdress);
            return curData;
        }
        cur = cur->next;
    }
    return NULL;
}
