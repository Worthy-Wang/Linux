#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
二.命名管道
命名管道比起无名管道，即便不是亲属进程也能够进行进程间通信
需要使用 mkfifo 命令创建命名管道

命名管道：读写操作案例

在使用命名管道之前, 必须使用 mkfifo 创建 命名管道。
分别创建好 读端 与 写端 ， 并设置退出机制

如果没有设置退出机制，那么read端 将会默认一直在接收 0 个字符，读端将会一直打印空字符串
*/

//write.cpp
int main()
{
    int fdw = open("pipe", O_WRONLY);
    ERROR_CHECK(fdw, -1 ,"open w");
    char buf[100] = {0};
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        read(0, buf, sizeof(buf));
        write(fdw, buf, strlen(buf) - 1);
    }
    return 0;
}