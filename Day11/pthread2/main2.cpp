#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
二.条件变量

条件变量的使用方法为：
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    //doing something...
    pthread_mutex_unlock(&mutex);    
 
*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void* threadFunc(void* arg)
{
    cout << "child thread "  << (long)arg << " is running and try to get the mutex " << endl;
    pthread_mutex_lock(&mutex);
    cout << "child thread " << (long)arg << " release the mutex and joined the waited_queue to wait for pthread_cond_signal" << endl;
    pthread_cond_wait(&cond, &mutex);
    cout << "child thread " << (long)arg << " get the mutex , then doing things" << endl;
    pthread_mutex_unlock(&mutex);    

    pthread_exit(NULL);
}

const long N = 100;
int main()
{
    pthread_t pids[N];
    for (long i = 0; i < N; i++)
        pthread_create(&pids[i], NULL, threadFunc, (void*)i);
    sleep(1);

    for (long i = 0; i < N; i++)
    {
        pthread_cond_signal(&cond);
        // sleep(1);
    }

    for (long i = 0; i < N; i ++)
        pthread_join(pids[i], NULL);
    return 0;
}