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
   int *a = ALLOC(sizeof(int));
   *a = 10;
   printf("(malloc) a = %d\n", *a);

   int *b = ALLOC(sizeof(int));
   *b = 20;
   printf("(malloc) b = %d\n", *b);

   debugInfo();

   // FREE
   printf("Starting MALLOC\n");
   FREE(a);

   debugInfo();
   //  ALLOUEMENT DYNAMIQUE

   printf("Starting ALLOUEMENT DYNAMIQUE\n");
   int *c = ALLOC(sizeof(int));
   *c = 90;
   printf("(malloc) c = %d\n", *c);
   debugInfo();

   //  MERGE

   printf("Starting MERGE\n");

     int *d = ALLOC(50 * sizeof(int));
   *d = 50;
    int *j = ALLOC(sizeof(int));
   *j = 90;

    
   int *f = ALLOC(sizeof(int));
   *f = 90;
   printf("avant MERGE\n");
   debugInfo();

   printf("apres MERGE\n");
   FREE(d);
    FREE(j);
   debugInfo();


   //  SPLIT
   printf("Starting SPLIT\n");
   int *g = ALLOC(sizeof(int));
   *g = 50;

   debugInfo();

   // CALLOC
   printf("Starting SPLIT+CALLOC\n");
   int *h;
   h = CALLOC(2, sizeof(int));
   printf("(calloc) h = %d\n", *h);
   debugInfo();

   FREE(h);

   // REALLOC
   printf("Starting REALLOC\n");
   b = REALLOC(b, 10 * sizeof(int));

   b[1] = 200;
   printf("(realloc) b[0] = %d, b[1] = %d,&b[0]=%p,&b[1]=%p\n", b[0], b[1], &b[0], &b[1]);
   debugInfo();
   FREE(b); // FREE
}

int main()
{
   test1();

   return 0;
}
