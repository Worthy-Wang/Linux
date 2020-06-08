#pragma once
#include "function.h"

class WorkQue
{
public:
    WorkQue()
    {
        mutex = PTHREAD_MUTEX_INITIALIZER;
    }
    void insertTask(int fd) //向任务队列中插入新的任务
    {
        deq.push_back(fd);
    }
    int size()
    {
        return deq.size();
    }
    int getTask() //线程取得新的任务
    {
        if (deq.empty())
            return -1;
        int ans = deq.front();
        deq.pop_front();
        return ans;
    }
    pthread_mutex_t mutex; //多线程对任务队列的互斥锁
    deque<int> deq; //存放accept 接收的 fd，
};
