#include <Unixfunc.h>
#include <iostream>
#define N 20
using namespace std;

/*
案例：窗口卖票程序(也可以说是生产者消费者案例：两个消费者，一个生产者)
创建两个子线程卖票，第三个子线程放票，两个子线程卖完20张票后，
第三个子线程把票重新设置为20，然后两个子线程继续卖票，把票卖光
*/

struct Train
{
    int tickets;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} train;

typedef void *(*Func)(void *);

void *sell_window1(void *arg)
{
    Train *train = (Train *)arg;
    while (1)
    {
        pthread_mutex_lock(&train->mutex);
        while (train->tickets == 0)
            pthread_cond_wait(&train->cond, &train->mutex);
        train->tickets--;
        cout << "window1 sell 1 ticket, there are " << train->tickets << " left " << endl;
        pthread_mutex_unlock(&train->mutex);
        sleep(1);
    }
}

void *sell_window2(void *arg)
{
    Train *train = (Train *)arg;
    while (1)
    {
        pthread_mutex_lock(&train->mutex);
        while (train->tickets == 0)
            pthread_cond_wait(&train->cond, &train->mutex);
        train->tickets--;
        cout << "window2 sell 1 ticket, there are " << train->tickets << " left " << endl;
        pthread_mutex_unlock(&train->mutex);
        sleep(1);
    }
}

void *set_tickets(void *arg)
{
    Train *train = (Train *)arg;
    while (1)
    {
        pthread_mutex_lock(&train->mutex);
        if (train->tickets == 0)
        {
            train->tickets = 20;
            cout << "reset 20 tickets" << endl;
            pthread_cond_signal(&train->cond);
        }
        pthread_mutex_unlock(&train->mutex);
    }
}

int main()
{
    train.tickets = N;
    train.cond = PTHREAD_COND_INITIALIZER;
    train.mutex = PTHREAD_MUTEX_INITIALIZER;
    Func threadFuncs[3] = {sell_window1, sell_window2, set_tickets};
    pthread_t pids[3];
    for (int i = 0; i < 3; i++)
        pthread_create(&pids[i], NULL, threadFuncs[i], &train);

    for (int i = 0; i < 3; i++)
        pthread_join(pids[i], NULL);

    return 0;
}
