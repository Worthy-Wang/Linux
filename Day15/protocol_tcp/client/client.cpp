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
    return len;
}

int recvFile(int sockfd)
{
    int ret;
    int dataLen;
    char buf[1000] = {0};

    //接收文件名称
    recvCycle(sockfd, &dataLen, sizeof(int));
    recvCycle(sockfd, buf, dataLen);
    int file_fd = open(buf, O_RDWR | O_CREAT, 0666);
    ERROR_CHECK(file_fd, -1, "open");

    //接收文件大小
    recvCycle(sockfd, &dataLen, sizeof(int));
    recvCycle(sockfd, buf, dataLen);
    off_t filesize;
    memcpy(&filesize, buf, dataLen);

    //接收文件内容
    off_t beg = 0;
    off_t download = 0;
    off_t slice = filesize / 100; //完成百分之一时打印
    cout << "Starting receive file" << endl;
    while (1)
    {
        recvCycle(sockfd, &dataLen, sizeof(int));
        if (0 == dataLen) //收到的是结束标志，结束接收
        {
            printf("\r100.00%%\n");
            break;
        }
        else
        {
            download += dataLen;
            recvCycle(sockfd, buf, dataLen);
            ret = write(file_fd, buf, dataLen);
            ERROR_CHECK(ret, -1, "write");
            //计算完成进度
            if (download - beg > slice)
            {
                printf("\r%5.2f%%", (float)download/filesize * 100);
                fflush(stdout);
                beg = download;
            }
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