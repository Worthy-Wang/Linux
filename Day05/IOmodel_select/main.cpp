#include <Unixfunc.h>
#include <iostream>
using namespace std;
#define STR_LEN 10 //定义随机输出的字符串长度。

/*
前言：为什么要使用IO多路转接模型?
试想一下，如果A想接收B的消息，那么A就需要创建一个进程(或线程)，用while(1)循环一直监视B是否给A发来消息，同时B也一直需要监视A，这会让系统的开销变得很大。
IO多路转接模型的函数select, 可以帮助我们同时监视多个文件句柄, 这样极大地降低了 内存 与 CPU 的开销。

IO多路转接模型 
* int select(int maxFd, fdset* rdset, fdset* wrset, fdset* exceptionset, struct timeval*)
select函数的本质：将加入的文件句柄进行监视, 如果读集合有可读的情况 或者 写集合有可写的情况，那么将向下执行
出错时返回 -1
超时返回 0
正常情况下返回一个 大于0 的数

参数说明：
maxfd: 文件句柄的最大值+1，如0， 1， 2分别代表输入，输出，错误输出，那么maxfd应该是现有的fd的最大值+1, select的本质是循环
rdset: 读文件句柄的集合，当检测的文件句柄中有可读的情况时，开始往下执行
wrset: 写文件句柄的集合，当检测的文件句柄中有可写的情况时，开始往下执行，一般来说文件句柄均为可写的情况
exceptionset: 异常文件句柄的集合
struct timeval:等待时间 NULL表示select函数阻塞并无限等待，0表示select函数非阻塞不等待，传入timeval则表示阻塞等待的时间



文件句柄的函数:
* FD_ZERO(fd_set* sets)
清空sets集合中原来的文件句柄
* FD_SET(int fd, fd_set* sets)
添加文件句柄到集合中
* FD_ISSET(int fd, fd_set* sets)
判断文件句柄在sets集合中是否有设定
* FD_CLR(int fd, fd_set* sets)

*/

/*
实例 ：两个文件句柄，同时对pipe文件进行读取和写入
*/
char *GenerateStr(char *str, int strlen)
{
    int i, flag;

    srand(time(NULL)); //通过时间函数设置随机数种子，使得每次运行结果随机。
    for (i = 0; i < strlen; i++)
    {
        flag = rand() % 3;
        switch (flag)
        {
        case 0:
            str[i] = rand() % 26 + 'a';
            break;
        case 1:
            str[i] = rand() % 26 + 'A';
            break;
        case 2:
            str[i] = rand() % 10 + '0';
            break;
        }
    }
    str[strlen] = 0;
    return str;
}

int test1()
{
    int fdr = open("pipe", O_RDWR);
    ERROR_CHECK(fdr, -1, "pipe");
    int fdw = open("pipe", O_RDWR);
    ERROR_CHECK(fdw, -1, "pipe");
    fd_set rdset, wrset;
    struct timeval timeout;
    while (1)
    {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fdr, &rdset);
        FD_SET(fdw, &wrset); //为了防止文件句柄与初始状态相比发生变化，所以每一次都要重新清空再设置
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        int ret = select(5, &rdset, &wrset, NULL, &timeout);
        if (ret > 0)
        {
            if (FD_ISSET(fdw, &wrset))
            {
                cout << "fdw write:" << endl;
                char buf[20] = {0};
                GenerateStr(buf, 10);
                write(fdw, buf, strlen(buf));
                cout << endl;
            }
            if (FD_ISSET(fdr, &rdset))
            {
                cout << "fd1 read:" << endl;
                char buf[20] = {0};
                read(fdr, buf, sizeof(buf));
                sleep(1);
                cout << buf << endl;
            }
        }
        else
            cout << "timeout" << endl;//因为设置了写集合，所以实际上不会出现超时的情况，因为文件句柄随时都是可写的状态
    }
    close(fdw);
    close(fdr);
    return 0;
}

/*
*/

int main()
{
    test1();
    return 0;
}