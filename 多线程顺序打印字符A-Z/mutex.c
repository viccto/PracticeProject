#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 3

pthread_mutex_t lock;

char c = 'a';

void* thread_fun(void *arg)
{
    int i = (int)arg;
    while(1)
    {
        if(c > 'z')
        {
            printf("%d OK\n", i);
            break;
        }
        if((c - 'a') % NUM_THREAD == i)
        {
            pthread_mutex_lock(&lock);
            if(c > 'z')
            {
                printf("%d OK\n", i);
                break;
            }
            printf("%d %c\n", i, c);
            c = c + 1;
            pthread_mutex_unlock(&lock);
        }
    }
}

int main()
{
    printf("hello world\n");
    pthread_t tid[NUM_THREAD];

    // init mutex_lock
    pthread_mutex_init(&lock, NULL);

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
    return 0;
}