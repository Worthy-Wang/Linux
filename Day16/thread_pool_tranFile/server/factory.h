#pragma once
#include "function.h"
#include "workQue.h"

void *doingTask(void *arg);
class Factory
{
public:
    Factory()
    {
        threadNum = THREADNUM;
        cond = PTHREAD_COND_INITIALIZER;
        startFlag = false;
    }
    void startFactory()
    {
        if (!startFlag)
        {
            for (int i = 0; i < threadNum; i++)
            {
                pthread_create(&threads[i], NULL, doingTask, this);
            }
            startFlag = true;
        }
    }

    WorkQue que;
    int threadNum;
    pthread_t threads[THREADNUM];
    pthread_cond_t cond;
    bool startFlag;
};

void *doingTask(void *arg)
{
    Factory *f = (Factory *)arg;
    cout << "child thread " << pthread_self() << " is waiting for task..." << endl;
    while (1)
    {
        pthread_mutex_lock(&f->que.mutex);
        while (0 == f->que.size())
            pthread_cond_wait(&f->cond, &f->que.mutex);
        int task = f->que.getTask();
        cout << "child thread " << pthread_self() << " is doing Task " << task << endl;
        tranFile(task);
        pthread_mutex_unlock(&f->que.mutex);
    }
}