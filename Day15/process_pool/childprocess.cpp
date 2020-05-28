#include "function.h"

void makeProcess(Process_data *pArr)
{
    int fds[2];
    int ret;
    for (int i = 0; i < PROCESSNUM; i++)
    {
        socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
        pid_t pid = fork();
        if (pid == 0)
        {
            close(fds[0]);
            doingTask(fds[1]);
        }
        else
        {
            close(fds[1]);
            Process_data child;
            child.pid = pid;
            child.fd = fds[0];
            child.busy = false;
            pArr[i] = child;
        }
    }
}

void doingTask(int fd)
{
    while (1)
    {
        int newfd;
        cout << "child process waiting for task..." << endl;
        recvFd(fd, &newfd);
        cout << "new child process is servering the client:" << newfd << endl;
        bool busy = false;
        send(fd, &busy, 1, 0);//发送一个标识消息，告诉主进程，自己不忙了
    }
}