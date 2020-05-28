#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
Udp通信：
udp是不可靠的连接方法，所以客户端的流程与服务端的流程都比较简单

服务端：socket -> bind -> recvfrom/sendto

客户端：socket -> recvfrom/sendto

1. recvfrom(..., sockaddr *__restrict__ __addr, socklen_t *__restrict__ __addr_len)

前面参数与recv 相同，addr结构体用于存放发送方的IP地址与端口号。

2. sendto(..., const sockaddr *__addr, socklen_t __addr_len)

前面的参数与send相同，addr结构体用于存放目标地址IP与端口号

案例：客户端与服务端通过udp连接通信
*/

int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in sockinfo;
    socklen_t len = sizeof(sockinfo);
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr("172.21.0.7");
    sockinfo.sin_port = htons(2012);
    sockinfo.sin_family = AF_INET;
    ret = bind(sockfd, (sockaddr *)&sockinfo, len);
    ERROR_CHECK(ret, -1, "bind");

    char buf[100] = {0};
    struct sockaddr_in client;
    recvfrom(sockfd, buf, sizeof(buf), 0, (sockaddr*)&client, &len);
    cout << " client " << inet_ntoa(client.sin_addr) << " :" << ntohs(client.sin_port) << endl;
    cout << "receiving :" << buf << endl;
    sendto(sockfd, "world", 5, 0, (sockaddr*)&sockinfo, len);

    close(sockfd);
    return 0;
}