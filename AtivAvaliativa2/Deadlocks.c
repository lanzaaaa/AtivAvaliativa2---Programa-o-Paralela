#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_task(void *arg)
{
    pthread_mutex_lock(&mutex1);
    printf("Thread 1 bloqueou o mutex1.\n");
    sleep(1);

    printf("Thread 1 tentando bloquear o mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1 bloqueou o mutex2.\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void *thread2_task(void *arg)
{
    pthread_mutex_lock(&mutex2);
    printf("Thread 2 bloqueou o mutex2.\n");
    sleep(1);

    printf("Thread 2 tentando bloquear o mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2 bloqueou o mutex1.\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_task, NULL);
    pthread_create(&t2, NULL, thread2_task, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
