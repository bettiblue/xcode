#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* do_loop(void *data)
{
    int i;
    
    int me = *((int *)data);
    for (i = 0; i < 10; i++)
    {
        printf("%d - Got %d\n", me, i);
        sleep(1);
    }
    return 0;
}

int main()
{
    int       thr_id;
    pthread_t p_thread[3];
    int status;
    int a = 1;
    int b = 2;
    int c = 3;
    
    thr_id = pthread_create(&p_thread[0], NULL, do_loop, (void *)&a);
    thr_id = pthread_create(&p_thread[1], NULL, do_loop, (void *)&b);
    thr_id = pthread_create(&p_thread[2], NULL, do_loop, (void *)&c);
    
    pthread_join(p_thread[0], (void **) &status);
    pthread_join(p_thread[1], (void **) &status);
    pthread_join(p_thread[2], (void **) &status);
    
    printf("program is end..\n");
    return 0;
}