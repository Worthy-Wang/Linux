#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
应用层协议设计：分包协议 与 TCP粘包
基于TCP传输的协议

为什么需要设计应用层的协议？
因为TCP传输协议会出现粘包的现象，总的来说就是将字节像流水一样传输给对方，在等长数据结构的情况下是没有问题的；
但如果是变长体的数据结构，接收方就无法进行划分，会造成数据混乱

先来看这两个函数

* send/write 向文件中写数据

非阻塞向文件中写入数据。

* read/recv 在没有数据可读的时候会阻塞；如果有数据的话，分为三种情况：

1. buf_len < data_len
那么读取buf_len的数据并返回buf_len, 此时还剩余(data_len - buf_len)的数据没有读取

2. buf_len > data_len
读取data_len的数据并返回data_len, 此时已经没有剩余数据

3. buf_len == data_len
正好读完
*/
#define IP "172.21.0.7"
#define PORT 2000
#define FILENAME "file"

struct Packet
{
    int dataLen;    // 包头，用来记录存数据的大小
    char buf[1000]; // 包数据，用来存放数据
};

int tranFile(int client_fd, int file_fd)
{
    int ret;
    Packet packet;

    //发送文件名称
    packet.dataLen = strlen(FILENAME);
    strcpy(packet.buf, FILENAME);
    ret = send(client_fd, &packet, 4 + packet.dataLen, 0);
    ERROR_CHECK(ret, -1, "send");
    //发送文件内容
    int sum = 0;
    while (packet.dataLen = read(file_fd, packet.buf, sizeof(packet.buf)))
    {
        ret = send(client_fd, &packet, 4 + packet.dataLen, 0);
        cout << ret << endl;
        sum += ret;
        ERROR_CHECK(ret, -1, "send");
    }
    //发送结束标志
    ret = send(client_fd, &packet, 4, 0);
    ERROR_CHECK(ret, -1, "send");
    cout << "sum = " << sum << endl;
    return 0;
}

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
    sockinfo.sin_addr.s_addr = inet_addr(IP);
    sockinfo.sin_port = htons(PORT);
    sockinfo.sin_family = AF_INET;
    ret = bind(sockfd, (sockaddr *)&sockinfo, sizeof(sockinfo));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    struct sockaddr_in client;
    bzero(&client, sizeof(client));
    socklen_t len = sizeof(client);
    int client_fd = accept(sockfd, (sockaddr *)&client, &len);
    ERROR_CHECK(client_fd, -1, "accept");
    cout << "client " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << " has connected" << endl;
    int file_fd = open(FILENAME, O_RDWR);
    ERROR_CHECK(file_fd, -1, "open");
    tranFile(client_fd, file_fd);

    close(sockfd);
    close(client_fd);
    close(file_fd);
    return 0;
}