#include "function.h"
#include "factory.h"

/*
线程池服务器创建流程：
1.创建任务队列，队列中放置锁，用于对任务队列进行加锁，对多个线程进行互斥；
2.创建一个工厂，存放任务队列，线程池，条件变量，启动工厂其实也就是启动线程池，子线程在没有任务时进行条件等待；
3.main函数创建TCP连接，监听socketFd，如果有客户端连上，那么将任务插入任务队列，并唤醒子线程。

*/


int main()
{
    Factory f;
    f.startFactory();
    int sockfd;
    tcpInit(&sockfd);//创建TCP连接
    while (1)
    {
        struct sockaddr_in client;
        bzero(&client, sizeof(client));
        socklen_t len = sizeof(client);
        int newTask = accept(sockfd, (sockaddr*)&client, &len);
        ERROR_CHECK(newTask, -1, "accept");
        cout << inet_ntoa(client.sin_addr) << ":" <<  ntohs(client.sin_port) << " has connected! fd = " << newTask << endl;

        pthread_mutex_lock(&f.que.mutex);
        f.que.insertTask(newTask);
        pthread_mutex_unlock(&f.que.mutex);
        pthread_cond_signal(&f.cond);
    }
    return 0;
}

