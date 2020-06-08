#include <Unixfunc.h>
#include <iostream>
using namespace std;

#define IP "172.21.0.7"
#define PORT 2000
#define FILENAME "file"

struct Packet
{
    int dataLen;    // 包头，用来记录存数据的大小
    char buf[1000]; // 包数据，用来存放数据
};

int tranFile(int client_fd)
{
    int ret;
    Packet packet;
    int file_fd = open(FILENAME, O_RDWR);
    ERROR_CHECK(file_fd, -1, "open");

    //传送文件名称
    packet.dataLen = strlen(FILENAME);
    strcpy(packet.buf, FILENAME);
    ret = send(client_fd, &packet, sizeof(int) + packet.dataLen, 0);
    ERROR_CHECK(ret, -1, "send");

    //传送文件大小
    struct stat statbuf;
    ret = stat(FILENAME, &statbuf);
    ERROR_CHECK(ret, -1, "stat");
    packet.dataLen = sizeof(off_t);
    memcpy(packet.buf, &statbuf.st_size, packet.dataLen);
    ret = send(client_fd, &packet, sizeof(int) + packet.dataLen, 0);
    ERROR_CHECK(ret, -1, "send");

    //传送文件内容
    int dataLen;
    char *pmap = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, file_fd, 0);
    ERROR_CHECK(pmap, (char *)-1, "mmap");
    off_t offset = 0;
    while (1)
    {
        if (statbuf.st_size > offset + sizeof(packet.buf))
        {
            packet.dataLen = sizeof(packet.buf);
            memcpy(packet.buf, pmap + offset, packet.dataLen);
            ret = send(client_fd, &packet, sizeof(int) + packet.dataLen, 0);
            ERROR_CHECK(ret, -1, "send");
            offset += packet.dataLen;
        }
        else
        {
            packet.dataLen = statbuf.st_size - offset;
            memcpy(packet.buf, pmap + offset, packet.dataLen);
            ret = send(client_fd, &packet, sizeof(int)+ packet.dataLen, 0);
            ERROR_CHECK(ret, -1, "send");
            break;
        }

    }

    ret = munmap(pmap, statbuf.st_size);
    ERROR_CHECK(ret, -1, "munmap");
    //发送传送结束标志
    packet.dataLen = 0;
    ret = send(client_fd, &packet, sizeof(int), 0);
    ERROR_CHECK(ret, -1, "send");

    close(file_fd);
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

    tranFile(client_fd);

    close(sockfd);
    close(client_fd);
    return 0;
}