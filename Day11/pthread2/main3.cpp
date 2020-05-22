#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
二.条件变量

条件变量的限时等待
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void* threadFunc(void* arg)
{
    cout << "child thread "  << (long)arg << " is running and try to get the mutex " << endl;
    pthread_mutex_lock(&mutex);
    cout << "child thread " << (long)arg << " release the mutex and joined the waited_queue to wait for pthread_cond_signal" << endl;
    struct timespec tv;
    tv.tv_sec = time(NULL) + 5; //必须加上 time(NULL)
    tv.tv_nsec = 0;
    pthread_cond_timedwait(&cond, &mutex, &tv); 
    int ret = pthread_mutex_unlock(&mutex);    
    cout << ret << endl;
    cout << "timeout and leave" << endl;

    pthread_exit(NULL);
}

const long N = 3;
int main()
{
    pthread_t pids[N];
    for (long i = 0; i < N; i++)
        pthread_create(&pids[i], NULL, threadFunc, (void*)i);
    sleep(1);

    for (long i = 0; i < N; i ++)
        pthread_join(pids[i], NULL);
    return 0;
}