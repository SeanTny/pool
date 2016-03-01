#include <stdio.h>
#include <boost/pool/pool.hpp>
#include <time.h>

#include "mpool.h"
#include "m_vector.h"


#include "lib/pthread.h"

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

//void test_list()
//{
//    char    *c1 = (char*)malloc(16),*c2 = (char*)malloc(16),*c3;
//    YC_List *list =List_Create(sizeof(char*));

//    List_Push_Back(char*,list,c1);
//    List_Push_Back(char*,list,c2);

//    c3 = List_Read_Front(char*,list);
//    sprintf(c1,"Hello");
//    sprintf(c2,"World");
//    printf("%s\n",List_Read_Front(char*,list));

//    List_Free(list);

//}

void * f1(void *arg)
{
    Sleep(1000);
    printf("==================Func 1\n");
    return NULL;
}
void * f2(void* arg)
{
    printf("==================Func 2\n");
    return NULL;
}

void test_boost()
{
    boost::pool<>   bpool(bsz);
    clock_t start, end;
    int i , j;

    start = clock();
    for( j = 0 ;j < runtimes; ++j)
    for ( i = 0 ; i < times; ++i)
    {
       void *f = bpool.malloc();
        bpool.free(f,bsz);
    }
    end = clock();
    fprintf(stdout,"Boost Pool Time Ellapsed:%dms\n",end-start);

}

void test_block()
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
    fprintf(stdout,"Block Pool Time Ellapsed:%dms\n",end-start);
    pool_release(block);
}

void test_threadpool()
{
    thPool  *pool = thpool_create(3);
    Task    t1 = {f1,NULL}, t2 = {f2,NULL};

    add_Task(pool,&t2);
    add_Task(pool,&t2);
    add_Task(pool,&t1);
    add_Task(pool,&t1);
    add_Task(pool,&t1);
    add_Task(pool,&t2);
    Sleep(3000);
    thpool_release(pool);
}

int main(void)
{
    test_boost();
    test_block();
    test_threadpool();

    return 0;
}

