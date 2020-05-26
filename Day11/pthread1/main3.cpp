#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
三.线程的退出与清理函数 pthread_canel 与 pthread_cleanup_

* int pthread_cancel(pthread_t __th)

取消子线程函数，此时资源必须手动清理.

* void pthread_cleanup_push(void (*routine)(void *), void* arg)
* void pthread_cleanup_pop(int execute)
                                
以上为两个资源清理函数，必须成对出现。
execute值为0的情况下，只有调用pthread_exit() 或有其他线程使用pthread_cancel() 才能调用清理函数
*/

void cleanup(void *arg)
{
    free(arg);
    cout << "thread cleanup" << endl;
}

void *threadFunc(void *arg)
{
    cout << "child thread is running " << endl;
    int *a = (int *)malloc(8);
    pthread_cleanup_push(cleanup, a);
    sleep(10);
    cout << "after sleep()" << endl;
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
}

int main()
{
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc, NULL);
    sleep(1);
    pthread_cancel(pid);
    pthread_join(pid, NULL);
    return 0;
}