#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
socket编程：
Linux网络编程实质上就是socket编程，IP地址可以确定一个主机，端口号可以确定主机中的一个进程，socket = IP + port（端口号）
这样便确定了主机中运行的进程，网络通信实质上就是进程通信。

我们知道连接分为两种，可靠的TCP连接与不可靠的UDP连接，下面分别通过这两种连接来熟悉socket编程

一.TCP通信
服务端：socket -> bind -> listen -> while(1){ accept -> doing ...} -> close
客户端：socket -> connect -> while (1) {doing ...} ->close

服务端详细流程：
1. int socket(int __domain, int __type, int __protocol)

* domain 使用的协议族：AF_INET(Ipv4), AF_INET6(Ipv6)
* type 代表连接的方式：SOCK_STREAM(TCP)， SOCK_DGRAM(UDP)
* protocol 协议，一般为0

服务端建立socket。

2. int bind(int __fd, const sockaddr *__addr, socklen_t __len)

* fd 之前创建的套接字
* addr 需要绑定的 地址族，IP地址， port号等， 一般使用struct sockaddr_in类型 进行绑定，然后再在bind函数进行类型强转 
* len addr的大小

将已经创建好的socket进行绑定好 IP地址，端口号等，如果想要进行网络通信，就需要通过这个socket。

3. int listen(int __fd, int __n)

* fd socket套接字
* n 同时连接的客户端的最大数量

在绑定好socket之后，开始进行监听，注意监听是非阻塞，只是说明服务端开始监听socket

4.int accept(int __fd, sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len)

* fd socket套接字
* addr 接收到的client信息结构体， 一般使用struct sockaddr_in 类型再强转
* addr_len client信息结构体的大小，注意是传入地址

accept函数一般是阻塞状态，用于接收连接的服务器，注意返回值是返回一个新的 newfd, 之后与服务器与客户端通信就是通过这个套接字进行通信
注意：此时sockfd只是用于接收客户端连接成功后的newfd套接字， 之后的通信都将在套接字newfd中进行， 也就是说，sockfd并不参与数据的交换。

5.close所有的newfd， sockfd


客户端详细流程：
1. int socket(int __domain, int __type, int __protocol)

* domain 使用的协议族：AF_INET(Ipv4), AF_INET6(Ipv6)
* type 代表连接的方式：SOCK_STREAM(TCP)， SOCK_DGRAM(UDP)
* protocol 协议，一般为0

2. int connect(int __fd, const sockaddr *__addr, socklen_t __len)

* fd 之前创建的socket套接字
* addr 需要绑定的 地址族，IP地址， port号等， 一般使用struct sockaddr_in类型 进行绑定，然后再在connect函数进行类型强转 
* len addr的大小

这个connect与服务端的bind函数相对应，连接上服务端已经绑定好的socket


注意，在bind之前可能会遇到：bind: Address already in use 这种情况
出现的原因是绑定的套接字在close之后还需要等待TIME_WAIT一段时间才能够进行重新绑定。
此时我们可以使用以下语句，让套接字可以立刻再次使用：
    int on = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");

案例：客户端连接上服务器并且互发消息
*/

int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    int on = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    ERROR_CHECK(ret, -1, "setsockopt");
    struct sockaddr_in sockinfo;
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr("172.21.0.7");
    sockinfo.sin_port = htons(2000);
    sockinfo.sin_family = AF_INET;
    ret = bind(sockfd, (sockaddr*)&sockinfo, sizeof(sockinfo));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    int newfd = accept(sockfd, NULL, NULL);
    ERROR_CHECK(ret, -1, "accept");
    
    char buf[100] = {0};
    recv(newfd, buf, sizeof(buf), 0);
    cout << "receiving from client:" << buf << endl;
    send(newfd, "world", 5, 0);
    
    close(sockfd);
    close(newfd);
    return 0;
}