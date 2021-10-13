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

   printf("Starting MALLOC\n");
   int *a = my_alloc(sizeof(int));
   *a = 10;
   printf("(malloc) a = %d\n", *a);

   int *b = my_alloc(sizeof(int));
   *b = 20;
   printf("(malloc) b = %d\n", *b);

   debugInfo();

   // FREE
   printf("Starting MALLOC\n");
   my_free(a);

   debugInfo();
   //  ALLOUEMENT DYNAMIQUE

   printf("Starting ALLOUEMENT DYNAMIQUE\n");
   int *c = my_alloc(sizeof(int));
   *c = 90;
   printf("(malloc) c = %d\n", *c);
   debugInfo();

   //  MERGE

   printf("Starting MERGE\n");
   int *d = my_alloc(50 * sizeof(int));
   *d = 50;
   int *f = my_alloc(sizeof(int));
   *f = 90;
   printf("avant MERGE\n");
   debugInfo();
   printf("apres MERGE\n");
   my_free(d);
   my_free(f);
   debugInfo();

   //  SPLIT
   printf("Starting SPLIT\n");
      int *g = my_alloc(sizeof(int));
      *g = 50;

   debugInfo();

 // CALLOC
  printf("Starting SPLIT\n");
    int *h;
   h = my_calloc(2, sizeof(int));
    printf("(calloc) h = %d\n", *h);
    debugInfo();

    FREE(h);
}

   // REALLOC
   // b = REALLOC(b, 10 * sizeof(int));
   // b[1] = 20;
   // debugInfo();
   // FREE(b); // FREE

  

int main()
{
   test1();

   return 0;
}
