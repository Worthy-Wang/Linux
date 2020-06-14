#include "function.h"

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
    ftruncate(file_fd, filesize);

    //接收文件内容
    char *pmap = (char *)mmap(NULL, filesize, PROT_WRITE, MAP_SHARED, file_fd, 0);
    ERROR_CHECK(pmap, (char *)-1, "mmap");
    off_t download = 0, lastsize = 0;
    off_t slice = filesize / 100;
    while (1)
    {
        recvCycle(sockfd, &dataLen, sizeof(int));
        if (0 == dataLen)
        {
            printf("\r100.00%%\n");
            break;
        }
        else
        {
            ret = recvCycle(sockfd, pmap + download, dataLen);
            if (ret == 0)
                break; //服务器已经断开
            download += dataLen;
            if (download - lastsize > slice)
            {
                printf("\r%5.2f%%", (float)download / filesize * 100);
                fflush(stdout);
                lastsize = download;
            }
        }
    }
    ret = munmap(pmap, filesize);
    ERROR_CHECK(ret, -1, "munmap");

    close(file_fd);
    return 0;
}

int sendFile(int client_fd)
{
    int ret;
    Packet packet;
    int file_fd = open(FILENAME, O_RDWR);
    ERROR_CHECK(file_fd, -1, "open");

    //传送文件名称
    packet.dataLen = strlen(FILENAME);
    strcpy(packet.buf, FILENAME);
    sendCycle(client_fd, &packet, sizeof(int) + packet.dataLen);

    //传送文件大小
    struct stat statbuf;
    ret = stat(FILENAME, &statbuf);
    ERROR_CHECK(ret, -1, "stat");
    packet.dataLen = sizeof(off_t);
    memcpy(packet.buf, &statbuf.st_size, packet.dataLen);
    sendCycle(client_fd, &packet, sizeof(int) + packet.dataLen);

    //传送文件内容
    char *pmap = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, file_fd, 0);
    ERROR_CHECK(pmap, (char *)-1, "mmap");
    off_t offset = 0;
    while (1)
    {
        if (statbuf.st_size > offset + (off_t)sizeof(packet.buf))
        {
            packet.dataLen = sizeof(packet.buf);
            memcpy(packet.buf, pmap + offset, packet.dataLen);
            sendCycle(client_fd, &packet, sizeof(int) + packet.dataLen);
            offset += packet.dataLen;
        }
        else
        {
            packet.dataLen = statbuf.st_size - offset;
            memcpy(packet.buf, pmap + offset, packet.dataLen);
            sendCycle(client_fd, &packet, sizeof(int)+ packet.dataLen);
            break;
        }

    }

    ret = munmap(pmap, statbuf.st_size);
    ERROR_CHECK(ret, -1, "munmap");
    //发送传送结束标志
    packet.dataLen = 0;
    sendCycle(client_fd, &packet, sizeof(int));

    close(file_fd);
    return 0;
}
