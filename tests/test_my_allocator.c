#include <stdlib.h>
#include <stdio.h>
#include <my_allocator.h>
 
//#define USE_MY_ALLOCATOR
 
#ifdef USE_MY_ALLOCATOR
#define ALLOC my_alloc
#define REALLOC my_realloc
#define CALLOC my_calloc
#define FREE my_free
#else
#define ALLOC malloc
#define REALLOC realloc
#define CALLOC calloc
#define FREE free
#endif
 
void test1()
{
   
   
   // MALLOC
   int* a = ALLOC(sizeof(int));
   *a = 10;
   printf("(malloc) a = %d\n", *a);
 
   // REALLOC
   a = REALLOC(a, 2 * sizeof(int));
   a[1] = 20;
   printf("(realloc) a[1] = %d\n", a[1]);
   FREE(a); // FREE
 
   // CALLOC
   a = CALLOC(1, sizeof(int));
   printf("(calloc) a = %d\n", *a);
   FREE(a);
}
 
int main()
{
   test1();
 
   return 0;
}
