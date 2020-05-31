#include <Unixfunc.h>
#include <iostream>
using namespace std;

#define IP "172.21.0.7"
#define PORT 2000

int recvCycle(int fd, void *p, size_t len)
{
    char *pStart = (char *)p;
    size_t size = 0;
    while (size < len)
    {
        int ret = recv(fd, pStart + size, len - size, 0);
        ERROR_CHECK(ret, -1, "recv");
        size += ret;
    }
    return 0;
}

int recvFile(int sockfd)
{
    int ret;
    int dataLen;
    char buf[1000] = {0};

    //接收文件名称
    ret = recvCycle(sockfd, &dataLen, sizeof(int));
    ERROR_CHECK(ret, -1, "recvCycle");
    ret = recvCycle(sockfd, buf, dataLen);
    ERROR_CHECK(ret, -1, "recvCycle");
    int file_fd = open(buf, O_RDWR | O_CREAT, 0666);
    ERROR_CHECK(file_fd, -1, "open");

    //接收文件大小
    ret = recvCycle(sockfd, &dataLen, sizeof(int));
    ERROR_CHECK(ret, -1, "recvCycle");
    ret = recvCycle(sockfd, buf, dataLen);
    ERROR_CHECK(ret, -1, "recvCycle");
    off_t filesize;
    memcpy(&filesize, buf, dataLen);

    //接收文件内容
    while (1)
    {
        ret = recvCycle(sockfd, &dataLen, sizeof(int));
        ERROR_CHECK(ret, -1, "recvCycle");
        if (0 == dataLen)//收到的是结束标志，结束接收
            break;
        else
        {
            ret = recvCycle(sockfd, buf, dataLen);
            ERROR_CHECK(ret, -1, "recvCycle");
            ret = write(file_fd, buf, dataLen);
            ERROR_CHECK(ret, -1, "write");
        }
    }

    close(file_fd);
    return 0;
}

int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in sockinfo;
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr(IP);
    sockinfo.sin_port = htons(PORT);
    sockinfo.sin_family = AF_INET;
    ret = connect(sockfd, (sockaddr *)&sockinfo, sizeof(sockinfo));
    ERROR_CHECK(ret, -1, "connect");

    recvFile(sockfd);

    close(sockfd);
    return 0;
}