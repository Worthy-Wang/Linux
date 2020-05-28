#include "function.h"


/*

进程池：
1.先创建好进程池，子进程建立主进程相连的管道（与主进程通信），主进程记录子进程的信息（id, 管道，是否忙碌）
2.建立TCP连接，epoll监听sockfd 以及 与进程池相连接的所有管道
3.epoll开始监听，如果sockfd就绪则连接好新的客户端，并将客户端转交子进程处理；如果管道就绪则将子进程调整为非忙碌状态。

*/

int main()
{
    Process_data pArr[PROCESSNUM];
    makeProcess(pArr);
    tcpInit();
    // int epfd = epoll_create(1);
    
    return 0;
}   