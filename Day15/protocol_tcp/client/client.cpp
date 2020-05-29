#include <Unixfunc.h>
#include <iostream>
using namespace std;

#define IP "172.21.0.7"
#define PORT 2000

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

int recvFile(int sockfd)
{
    int dataLen;
    //接收文件名称
    char buf[1000] = {0};
    recvCycle(sockfd, &dataLen, 4);
    recvCycle(sockfd, buf, dataLen);
    cout << buf << endl;
    //接收文件内容
    int fd = open(buf, O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    int sum = 0;
    while (1)
    {
        recvCycle(sockfd, &dataLen, 4);
        cout << dataLen << endl;
        sum += dataLen;
        if (dataLen > 0)
        {
            recvCycle(sockfd, buf, dataLen);
            write(fd, buf, dataLen);
        }
        else
            break;
    }
    cout << "sum = " << sum << endl;
    close(fd);
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