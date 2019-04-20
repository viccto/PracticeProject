#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREAD 3
sem_t sem[NUM_THREAD];

char c = 'a';

void* thread_fun(void *arg)
{
    int i = (int)arg;
    while(1)
    {
        sem_wait(&sem[i]);
        if(c > 'z')
        {
            printf("%d OK\n", i);
            sem_post(&sem[(i + 1) % NUM_THREAD]);
            break;
        }
        printf("%d %c\n", i, c);
        c = c + 1;
        sem_post(&sem[(i + 1) % NUM_THREAD]);
    }
}

int main()
{
    printf("hello world\n");
    pthread_t tid[NUM_THREAD];
    int i = 0;
    for(i = 0; i < NUM_THREAD; i++)
    {
        // init each semaphore as 0
        sem_init(&sem[i], 0, 0);
        pthread_create(&tid[i], NULL, thread_fun, (void *)i);
    }
    // start from the first thread
    sem_post(&sem[0]);

    for(i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(tid[i], NULL);
        // sem_destory(&sem[i]);     // error: undefine reference to 'sem_destory'
    }
    return 0;
}