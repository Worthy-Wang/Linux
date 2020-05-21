#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
Linux 信号处理机制

一.signal
* typedef void (*sighandler_t)(int);

函数指针 sighandler_t

* sighandler_t signal(int signum, sighandler_t handler);

捕捉signum的信号



案例一：捕捉终端ctrl + c 产生的 SIGINT 中断信号
*/
void sighandler(int signum)
{
    cout << "recving signal number:" << signum << endl;
    // exit(0);//如果没有退出的话仍将会一直运行程序
}

void test1()
{
    signal(SIGINT, sighandler);
    while (1)
        ;
    cout << "this is test0" << endl;
}


/*
二.sigaction


*/
void handler(int signum)
{
    cout << "capturing signal :" << signum << endl;
}

void test2()
{
}


int main()
{
    test2();
    return 0;
}
