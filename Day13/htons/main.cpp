#include <iostream>
#include <Unixfunc.h>
#include <netdb.h>
using namespace std;

/*
网络字节序 与 主机字节序

首先需要理解 大端模式 与 小端模式这两个点：
这两种模式代表着数据在内存中是如何存放的，我们直到，一个字节能够存放8位，如果是超过8位的数据该怎样存放呢？
如需要存放数据 0x12345678
大端模式存放：0x12345678
小端模式存放: 0x78563412

不难看出，大端模式也就是高位优先存放，小端模式也就是低位优先存放。
大端模式是我们常用的存储方式，也就是网络字节序（IP地址在网络中的显示）；小端模式是主机存储IP地址的方式，称为主机字节序

下面学习两类函数：
1. htons , ntohs 
此类函数主要用于转换 整型

2.inet_aton, inet_addr, inet_ntoa
此类函数主要用于转换 字符串型 
*/

//主机字节序 ——> 网络字节序
void test0()
{
    int i = htons(0x1234);
    cout << i << endl;
    printf("%x\n", i);

    int j = ntohs(0x1234);
    printf("%x\n", j);

    int m = htons(111);
    cout << m << endl;

    int n = ntohs(m);
    cout << n << endl;
}


//主机字节序 ——> 网络字节序
int test1()
{
    char ip[] = "192.168.0.101"; //主机字节序, 小端模式
    printf("%x\n", inet_addr(ip)); //网络字节序，大端模式

    struct in_addr inaddr;
    inet_aton(ip, &inaddr);
    printf("%x\n", inaddr.s_addr); //网络字节序， 大端模式

    struct in_addr inaddr2;
    inet_pton(AF_INET, ip, &inaddr2);
    printf("%x\n", inaddr2.s_addr); //网络字节序， 大端模式

    return 0;
}

//网络字节序 ——> 主机字节序
int test2()
{
    struct in_addr inaddr;
    inaddr.s_addr = 0x6500a8c0;
    char ip[16];

    printf("%s\n", inet_ntoa(inaddr));

    inet_ntop(AF_INET, &inaddr, ip, 16);
    cout << ip << endl;

    return 0;
}


/*
域名转换IP地址

如百度转换为它的IP地址
*/
int test3()
{
    struct hostent *host = gethostbyname("www.baidu.com");
    cout << "网站的真正名字：" << endl;
    cout << host->h_name << endl;
    cout << "地址族 为IPV4:" << (host->h_addrtype==AF_INET ? "yes":"no") << endl;
    cout << "IP地址的字节数为:" << host->h_length << endl;
    cout << "网站的别名有:" << endl;
    for (int i = 0; host->h_aliases[i] != NULL; i++)
        cout << host->h_aliases[i] << endl;
    cout << "网站的IP地址列表：" << endl;
    for (int i = 0 ; host->h_addr_list[i] != NULL; i++)
    {
        char ip[16];
        inet_ntop(host->h_addrtype, host->h_addr_list[i], ip, 16);
        cout << ip << endl;
    }
    return 0;
}


int main()
{
    test0();
    return 0;
}