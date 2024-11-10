#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_barrier_t barrier;

void *thread_task(void *arg)
{
    int thread_id = *((int *)arg);
    printf("Thread %d está realizando a primeira parte da tarefa.\n", thread_id);
    sleep(1);

    printf("Thread %d está aguardando na barreira.\n", thread_id);
    pthread_barrier_wait(&barrier);

    printf("Thread %d passou da barreira e está realizando a segunda parte.\n", thread_id);
    sleep(1);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_task, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}
