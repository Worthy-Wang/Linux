#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
二.线程等待与退出 pthread_join pthread_exit

* int pthread_join(pthread_t __th, void **__thread_return)

* void pthread_exit(void *__retval)



1.传出long/int型
*/
void *threadFunc1(void *arg)
{
    long val = 4;
    pthread_exit((void *)val); //此处不能使用 (void*)&val ,因为这样传出的是地址，而不是值
}

void test1()
{
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc1, NULL);
    long val;
    pthread_join(pid, (void **)&val);
    cout << "val = " << val << endl;
}

/*
2. 传出char*型
*/
void *threadFunc2(void *arg)
{
    char *s = "HelloWorld";
    pthread_exit(s);
}

void test2()
{
    pthread_t pid;
    pthread_create(&pid, NULL, threadFunc2, NULL);
    void *buf;
    pthread_join(pid, &buf);
    cout << (char *)buf << endl;
}



int main()
{

    return 0;
}