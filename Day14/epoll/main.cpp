#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
IO多路复用（二） epoll

epoll相比于select有三个优点：
1.select在每一次循环的时候都需要重新设置需要监听的句柄，epoll则不必
2.select对每一个需要监听的句柄都要遍历询问，epoll则是直接将准备就绪的句柄加入就绪队列，并返回就绪句柄数量
3.epoll的最大连接数可以设置得非常的大，而select则只能设置很少

select相当于O(N)的时间复杂度，当有句柄准备就绪时，它并不知道是哪一个准备就绪，只能进行轮询；
epoll相当于O(1)的时间复杂度，它会精准的知道是哪些句柄准备就绪，并返回就绪句柄的数量。
在有大量的并发连接，且真正需要数据交换的有效连接较少的情况下，epoll的效率则比select大了许多。

* int epoll_create(int __size)

size目前这个参数已经不被需要，我们通常将它设置为1.
成功则返回一个epoll句柄，失败返回-1

* int epoll_ctl(int __epfd, int __op, int __fd, epoll_event * event)

epfd:epoll句柄
op: 需要进行的操作,有 EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL 
fd : 需要进行操作的句柄
event : 一个结构体, 用于与op结合进行操作

* int epoll_wait(int __epfd, epoll_event *__events, int __maxevents, int __timeout)

epfd: epoll句柄
events: 传入event数组，将准备就绪的句柄赋值到event数组中
maxevents: event数组的容量
timeout: 超时机制，-1则是永久等待，0则是不等待，正数则是等待毫秒
返回值：成功则返回的是准备就绪的句柄数量，也就是event数组被赋值的数量，失败返回-1， 超时返回0
epoll_wait在函数的形式上接近select



*/
void test0()
{

}


int main()
{
    test0();
    return 0;
}