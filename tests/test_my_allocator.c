#include <stdlib.h>
#include <stdio.h>
#include <my_allocator.h>

#define USE_MY_ALLOCATOR

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

   printf("Starting...\n");
   int *a = my_alloc(sizeof(int));
   *a = 10;
   printf("(malloc) a = %d\n", *a);

   int *b = my_alloc(sizeof(int));
   *b = 20;
   printf("(malloc) b = %d\n", *b);

   debugInfo();

   my_free(a);

   debugInfo();

   int *c = my_alloc(sizeof(int));
   *c = 90;
   printf("(malloc) c = %d\n", *c);
   debugInfo();
   int *d = my_alloc(50 * sizeof(int));
   *d = 50;
   int *f = my_alloc(sizeof(int));
   *f = 90;
   printf("(malloc) d = %d\n", *d);
   printf("(malloc) f = %d\n", *f);
   debugInfo();
   my_free(d);
   debugInfo();
   int *e = my_alloc(20 * sizeof(int));
   *e = 50;
   printf("(malloc) e = %d\n", *e);
   debugInfo();

   
   debugInfo();
   my_free(e);
   debugInfo();

   // REALLOC
   //a = REALLOC(a, 2 * sizeof(int));
   //a[1] = 20;
   //printf("(realloc) a[1] = %d\n", a[1]);
   //FREE(a); // FREE

   // CALLOC
   //a = CALLOC(1, sizeof(int));
   //printf("(calloc) a = %d\n", *a);
   //FREE(a);
}

int main()
{
   test1();

   return 0;
}
