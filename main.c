#include <stdio.h>
#include <time.h>

#include "mpool.h"
#include "m_vector.h"

#include "thpool.h"


int bsz = 8;
int times = 100000;
int runtimes = 100;

void test_pool()
{
    MemPool *pool = pool_create(128,10);
    int     i = 0;
    for ( ; i < 15; ++i )
    {
        char *c = (char*)m_malloc(pool);

        sprintf(c,"%d\tThis Is My Pool\n",i+1);
        printf(c);
    }

    pool_release(pool);
}

void * f1(void *arg)
{
    printf("==================Func 1\n");
    return NULL;
}
void * f2(void* arg)
{
    printf("==================Func 2\n");
    return NULL;
}
void test_malloc()
{
    clock_t       start, end;
    int i , j ;


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
       void *f = malloc(bsz);
       free(f);
    }
    end = clock();
    fprintf(stdout,"malloc Time Ellapsed:%d\n",end-start);
}

//void test_boost()
//{
//    boost::pool<>   bpool(bsz);
//    clock_t start, end;
//    int i , j;

//    start = clock();
//    for( j = 0 ;j < runtimes; ++j)
//    for ( i = 0 ; i < times; ++i)
//    {
//       void *f = bpool.malloc();
//        bpool.free(f,bsz);
//    }
//    end = clock();
//    fprintf(stdout,"Boost Pool Time Ellapsed:%dms\n",end-start);

//}

void test_mempool()
{
    MemPool       *block = pool_create(bsz,1);
    clock_t       start, end;
    int i , j ;


    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
       void *f = m_malloc(block);
       m_free(block,f);
    }
    end = clock();
    fprintf(stdout,"Block Pool Time Ellapsed:%d\n",end-start);
    pool_release(block);
}

//void test_threadpool()
//{
//    thPool  *pool = thpool_create(3);
//    Task    t1 = {f1,NULL}, t2 = {f2,NULL};

//    add_Task(pool,&t2);
//    add_Task(pool,&t2);
//    add_Task(pool,&t1);
//    add_Task(pool,&t1);
//    add_Task(pool,&t1);
//    add_Task(pool,&t2);
//    Sleep(3000);
//    thpool_release(pool);
//}

int main(void)
{
//    test_boost();
    test_mempool();
    test_malloc();
//    test_threadpool();

    return 0;
}

