#include "function.h"

int makeProcess(Process_data *pArr)
{
    int fds[2];
    for (int i = 0; i < PROCESSNUM; i++)
    {
        int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
        ERROR_CHECK(ret, -1, "socketpair");
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
    return 0;
}

void doingTask(int fd)
{
    while (1)
    {
        int newfd;
        cout << "child process waiting for task..." << endl;
        recvFd(fd, &newfd);
        cout << "child process is servering the client:" << newfd << endl;
        sleep(1);
        bool busy = false;
        send(fd, &busy, 1, 0);//发送一个标识消息，告诉主进程，自己不忙了
    }
}