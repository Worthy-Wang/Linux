#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
命名管道案例
实现聊天室的雏形功能，每人互发一句消息的方式进行聊天
利用两个命名管道，chat1 首先发消息

可能有人会有疑问：为什么不直接用一个命名管道，进行读写操作？
因为命名管道的本质也是半双工管道，必须固定读端与写端，所以要有两根管道
*/

int main(int argc, char* argv[])
{
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDWR);
    int fdw = open(argv[2], O_RDWR);
    ERROR_CHECK(fdr, -1, "open1");
    ERROR_CHECK(fdw, -1, "open2");
    char buf[100] = {0};
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        read(0, buf, sizeof(buf));
        write(fdw, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
        read(fdr, buf, sizeof(buf));
        cout << buf;
    }
    return 0;
}