#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
Posix多线程pthread详解(二) 锁与条件变量

一.互斥锁
互斥锁的使用形式如下：
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_locK(&mutex);
    //doing ...
    pthread_mutex_unlock(&mutex);

案例：主线程与子线程各加一千万
在没有使用互斥锁的情况下，主线程与子线程相加一千万是小于两千万的，使用互斥锁，那么结果便等于两千万
另外，与两个进程相加一千万对比，多线程很明显更加迅速。
*/
int N = 10000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *threadFunc(void *arg)
{
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_lock(&mutex);
        *(int *)arg += 1;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    int sum = 0;
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc, &sum);
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(pid, NULL);
    cout << "final sum = " << sum << endl;
    return 0;
}