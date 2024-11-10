#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg)
{
    int reader_id = *((int *)arg);

    pthread_mutex_lock(&read_count_mutex);
    read_count++;
    if (read_count == 1)
    {
        pthread_mutex_lock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_count_mutex);
    printf("Leitor %d leu o valor: %d\n", reader_id, shared_data);
    sleep(1);

    pthread_mutex_lock(&read_count_mutex);
    read_count--;
    if (read_count == 0)
    {
        pthread_mutex_unlock(&resource_mutex);
    }
    pthread_mutex_unlock(&read_count_mutex);

    return NULL;
}

void *writer(void *arg)
{
    int writer_id = *((int *)arg);

    pthread_mutex_lock(&resource_mutex);

    shared_data += 10;
    printf("Escritor %d modificou o valor para: %d\n", writer_id, shared_data);
    sleep(1);
    pthread_mutex_unlock(&resource_mutex);

    return NULL;
}

int main()
{
    pthread_t readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
