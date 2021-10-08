#pragma once
#include <stdbool.h>


typedef struct Data
{
    
    Value adress;
    bool occupy;
    int size;
    struct Data* next;
    


}Data;

typedef struct Adress
{
    Data* head;
    void* memoryAdress;

    
}Adress;
