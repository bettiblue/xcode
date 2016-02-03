
//스레드 생성 후 자동 종료되는 예제
//생성된 쓰레드가 정상적으로 동작하고 pthread_exit함수를 통해서 0값을 리턴하고 종료하였으므로 pthread_join함수에서 status값 0이 출력된다.

#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t threads[5];               // type of thread
int done[5];

void *thread_main(void *);

int main(void)
{
    int i;
    int rc;
    int status;
    
    printf("pid=%d\n", getpid());
    
    for (i = 0; i < 5; i++)             //create thread
    {
        done[i] = 0;
        pthread_create(&threads[i], NULL, &thread_main, (void *)i);
        printf("%d, %d\n", i, threads[i]);
    }
    
    for (i = 4; i >= 0; i--)
    {
        done[i] = 1;
        rc = pthread_join(threads[i], (void **)&status);
        if (rc == 0)
        {
            printf("Completed join with thread %d status= %d\n",i, status);
        }
        else
        {
            printf("ERROR; return code from pthread_join() is %d, thread %d\n", rc, i);
            return -1;
        }
    }
    
    return 0;
}

void *thread_main(void *arg)
{
    int i;
    double result=0.0;
    
    printf("therad: %d, %d\n", (int)arg, getpid());
    
    while (!done[(int)arg])
    {
        for (i=0; i < 1000000; i++)
        {
     	      result = result + (double)rand();
        }
        printf("thread: %d, result = %e\n", (int)arg, result);
    }
    
    pthread_exit((void *) 0);
}
