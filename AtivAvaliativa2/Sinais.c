#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
int shared_data = 0;

void *wait_for_signal(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("Thread esperando pelo sinal...\n");

    pthread_cond_wait(&condition_var, &mutex);
    printf("Sinal recebido! Thread executando tarefa com shared_data: %d\n", shared_data);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *send_signal(void *arg)
{
    sleep(2);
    pthread_mutex_lock(&mutex);

    shared_data = 42;
    printf("Thread enviando sinal com shared_data atualizado: %d\n", shared_data);
    pthread_cond_signal(&condition_var);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, wait_for_signal, NULL);
    pthread_create(&t2, NULL, send_signal, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition_var);

    return 0;
}
