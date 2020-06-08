#include "function.h"

/*

进程池：
1.先创建好进程池，子进程建立主进程相连的管道（与主进程通信），主进程记录子进程的信息（id, 管道，是否忙碌）
2.建立TCP连接，epoll监听sockfd 以及 与进程池相连接的所有管道
3.epoll开始监听，如果sockfd就绪则连接好新的客户端，并将客户端转交子进程处理；如果管道就绪则将子进程调整为非忙碌状态。

技术亮点：
1.安全退出机制：服务器（客户端）突然断开，另一方均可安全退出。

*/

int main()
{
    //1.
    Process_data pArr[PROCESSNUM];
    makeProcess(pArr);
    cout << "Now there are " << PROCESSNUM << " child process waiting for task" << endl;
    //2.
    int sockfd;
    tcpInit(&sockfd);
    cout << "Server is running..." << endl;
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event ev, evs[PROCESSNUM + 1];
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    for (int i = 0; i < PROCESSNUM; i++)
    {
        ev.data.fd = pArr[i].fd;
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pArr[i].fd, &ev);
        ERROR_CHECK(ret, -1, "epoll_ctl");
    }
    //3.
    while (1)
    {
        int nfds = epoll_wait(epfd, evs, PROCESSNUM + 1, 10000);
        ERROR_CHECK(nfds, -1, "epoll_wait");
        if (nfds > 0)
        {
            for (int i = 0; i < nfds; i++)
            {
                if (evs[i].data.fd == sockfd)
                {
                    struct sockaddr_in client;
                    bzero(&client, sizeof(client));
                    socklen_t len = sizeof(client);
                    int newfd = accept(sockfd, (sockaddr *)&client, &len);
                    ERROR_CHECK(newfd, -1, "accept");
                    cout << "client " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << " has connected" << endl;
                    //找到非忙碌的子进程，给它安排任务
                    bool flag = false;
                    for (int j = 0; j < PROCESSNUM; j++)
                    {
                        if (!pArr[j].busy)
                        {
                            cout << "child process " << pArr[j].pid << " has taken the task" << endl;
                            sendFd(pArr[j].fd, newfd);
                            pArr[j].busy = true;
                            cout << "child proces " << pArr[j].pid << " is busy now" << endl;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                        cout << "no child process is free now!" << endl;
                }

                for (int j = 0; j < PROCESSNUM; j++)
                {
                    if (evs[i].data.fd == pArr[j].fd)
                    {
                        bool temp;
                        read(pArr[j].fd, &temp, 1);
                        pArr[j].busy = false;
                        cout << "child proces " << pArr[j].pid << " is not busy now" << endl;
                    }
                }
            }
        }
        else
            cout << "timeout" << endl;
    }

    return 0;
}