#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
应用层协议设计，通过上面的例子，我们得知，只读一次recv很可能无法将内核缓存中的数据读完，这样便不能解决TCP传输中粘包的问题
recv函数可能出现的问题:接收缓存区中的字节较少（不够len字节），recv有字节读取就返回，就无法一次性读取len的字节，所以需要循环读，保证字节读够
*/

//改进recv函数，可以完整的接收数据
int recvCycle(int fd, void* p, size_t len)
{
    char *pStart = (char*)p;
    size_t size = 0;
    while (size < len)
    {
        int ret = recv(fd, pStart + size, len - size, 0);
        ERROR_CHECK(ret, -1, "recv");
        size += ret;
    }
    return 0;
}


int main()
{

    return 0;
}