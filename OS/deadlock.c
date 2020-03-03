#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

pthread_mutex_t resource1,resource2;
int test=0;
void *proc1(void *arg)
{
    printf("\nThis is proc1 using rs1");

    pthread_mutex_lock(&resource1);
    sleep(2);
    printf("\np1 trying to get rs2...");
    pthread_mutex_lock(&resource2);
    test++;
    printf("\nproc1 got rs2!!");

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);
    return 0;
}

void *proc2(void *arg)
{
    printf("\nThis is proc2 using rs2");


    pthread_mutex_lock(&resource2);
    sleep(2);
    printf("\np2 trying to get rs1...");
    pthread_mutex_lock(&resource1);

    test--;
    printf("\nproc2 got rs1!!");

    pthread_mutex_unlock(&resource1);
    pthread_mutex_unlock(&resource2);
    return 0;
}

int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&resource1, NULL);
    pthread_mutex_init(&resource2, NULL);

    pthread_create(&t1,NULL, proc1 , NULL);
    pthread_create(&t2,NULL, proc2 , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    /* will never arrive here */
    pthread_mutex_destroy(&resource1);
    pthread_mutex_destroy(&resource2);
    return 0;
}
