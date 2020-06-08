#include "function.h"

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
    char *pmap = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, file_fd, 0);
    ERROR_CHECK(pmap, (char *)-1, "mmap");
    off_t offset = 0;
    while (1)
    {
        if (statbuf.st_size > offset + (off_t)sizeof(packet.buf))
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
