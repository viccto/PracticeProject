#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 3

pthread_mutex_t lock;
pthread_cond_t cond;

char c = 'a';

void* thread_fun(void *arg)
{
    int i = (int)arg;
    while(1)
    {
        pthread_mutex_lock(&lock);
        while((c - 'a') % NUM_THREAD != i)  // 'while', not 'if'. Make sure condition after be notified. 
        {
            pthread_cond_wait(&cond, &lock);
            if(c > 'z')
            {
                printf("%d OK\n", i);
                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&lock);
                pthread_exit(0);
            }
        }
        printf("%d %c\n", i, c);
        c = c + 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    printf("hello world\n");
    pthread_t tid[NUM_THREAD];

    // init mutex_lock & condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    int i = 0;
    for(i = 0; i < NUM_THREAD; i++)
    {
        pthread_create(&tid[i], NULL, thread_fun, (void *)i);
    }
    
    for(i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(tid[i], NULL);
    }
    // pthread_mutex_destory(&lock);
    // pthread_cond_destory(&cond);
    return 0;
}