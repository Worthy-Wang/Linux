#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
此篇文章参考于：https://www.jianshu.com/p/45118a062241（Linux系统编程—信号量）

# 前言
信号量的使用方法与 共享内存，消息队列均不同，后者是主要方便进程间通信，而信号量的作用是 对共享资源的互斥访问
当信号量的资源数量 <= 0 时，则会阻塞，直到资源数量 >0 时才开始进行操作，另外信号量的操作均为原子操作。

信号量的主要两种用法（根据信号量初始资源数量的不同, 或者说有没有利用到信号量的资源值）：
1. 互斥锁（信号量的初始值为1）
可以将信号量的资源数量设置为1， P操作加锁，V操作解锁，主要用于实现对公共资源的互斥访问

2. 条件等待(信号量的初始值 > 1)
信号量的初始值大于1时，进行P操作进行消费， V操作进行生产，当信号量的资源值<=0 时阻塞等待，主要用于实现生产者消费者案例


IPC 进程间通信(二) 信号量

* int semget(key_t keys, int nsems, int flags)

创建一个（或多个信号量）
keys: 用来判断是创建新的信号量还是用已有的信号量
nsems: 信号量的数量
flags: 创建的权限及特性

* int semop(int semid, struct sembuf* sops, size_t nops)

将要进行的操作 sop 添加到信号量semid中
semid: 信号量的标识
sops: 添加的操作结构体
nops: 添加操作结构体的个数，若添加的操作只有1个，那么 nops=1。

struct sembuf* sops 有三个成员
sem_num : 代表着要操作的信号量的下标(从0开始)
sem_op : 要进行的操作， 一般是 1 或 -1  , 也就是 P/V操作
sem_flg : 一般为0， 表示undo


* int semctl(int semid, int semnum, int cmd)

对信号量semid进行操作
* sennum 信号量集合中的下标，一般来说只有一个信号量，也就是为 0
* cmd 执行的命令，一般有如 GETVAL , IPC_RMID, SETVAL, SETVALL 等操作
通过以下示例程序可以更深入理解。

*/

//1.针对一个信号量集合中只有一个信号量的情况
int test1()
{
    int ret;
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    ERROR_CHECK(semid, -1, "semget");

    semctl(semid, 0, SETVAL, 10); //设置信号量的初始值为10
    struct sembuf sop;
    sop.sem_num = 0; //下标为0的信号量
    sop.sem_op = 1;  //V操作
    sop.sem_flg = 0; //undo操作
    ret = semop(semid, &sop, 1);
    ERROR_CHECK(ret, -1, "semop");
    cout << semctl(semid, 0, GETVAL) << endl;
    ret = semctl(semid, 0, IPC_RMID);
    ERROR_CHECK(ret, -1, "semctl");
    return 0;
}

//2.针对一个信号量集合中有多个信号量的情况
int test2()
{
    int ret;
    int semid = semget((key_t)0x1234, 3, 0666 | IPC_CREAT);
    ERROR_CHECK(semid, -1, "semget");
    unsigned short array[3] = {10, 20, 30}; //为三个信号量设定初始值
    semctl(semid, 0, SETALL, array);

    //为三个信号量分别 +1 +2 +3
    struct sembuf sop[3];
    sop[0].sem_num = 0;
    sop[0].sem_op = 1;
    sop[0].sem_flg = 0;

    sop[1].sem_num = 1;
    sop[1].sem_op = 2;
    sop[1].sem_flg = 0;

    sop[2].sem_num = 2;
    sop[2].sem_op = 3;
    sop[2].sem_flg = 0;

    ret = semop(semid, sop, 3);
    ERROR_CHECK(ret, -1, "semop");
    cout << "第0个信号量的值: " << semctl(semid, 0, GETVAL) << endl;
    cout << "第1个信号量的值: " << semctl(semid, 1, GETVAL) << endl;
    cout << "第2个信号量的值: " << semctl(semid, 2, GETVAL) << endl;
    semctl(semid, 0, IPC_RMID);
    return 0;
}

/*
信号量的用法一：互斥锁
案例：两个进程同时加一千万(在共享内存中),并查看最终值是否为两千万
*/
int add_and_count()
{
    int N = 10000000;
    int shmid = shmget((key_t)0x1000, 4, 0666 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    int *sum = (int *)shmat(shmid, NULL, 0);
    ERROR_CHECK(sum, (int *)-1, "shmat");
    *sum = 0;
    int semid = semget((key_t)0x1234, 1, 0666 | IPC_CREAT);
    ERROR_CHECK(semid, -1, "semget");
    semctl(semid, 0, SETVAL, 1);
    struct sembuf P, V;
    P = {0, -1, 0};
    V = {0, 1, 0};
    if (fork() > 0)
    {
        for (int i = 0; i < N; i++)
        {
            semop(semid, &P, 1);
            (*sum)++;
            semop(semid, &V, 1);
        }
        wait(NULL);
        cout << "final sum = " << *sum << endl;
        semctl(semid, 0, IPC_RMID);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            semop(semid, &P, 1);
            (*sum)++;
            semop(semid, &V, 1);
        }
    }

    return 0;
}

/*
信号量的用法二 ： 条件等待
案例:生产者消费者
一个仓库有10个空位置存放产品，生产者生产产品（没有空位子时等待），消费者消费产品（没有产品时等待）
*/
int producer_consumer()
{
    int ret;
    int semid = semget((key_t)0x1234, 2, 0666 | IPC_CREAT);
    ERROR_CHECK(semid, -1, "semget");
    unsigned short array[2] = {10, 0}; //空位子，成品数
    semctl(semid, 0, SETALL, array);
    struct sembuf P1, V1, P2, V2;
    P1 = {0, -1, 0};
    P2 = {1, -1, 0};
    V1 = {0, 1, 0};
    V2 = {1, 1, 0};

    //生产者
    if (fork() > 0)
    {
        for (int i = 0; i < 5; i++)
        {
            semop(semid, &P1, 1);
            cout << "Producing..." << endl;
            semop(semid, &V2, 1);
            cout << "after producing, space = " << semctl(semid, 0, GETVAL) << " , production = " << semctl(semid, 1, GETVAL) << endl;
            sleep(2);
        }
        wait(NULL);
        semctl(semid, 0, IPC_RMID);
    }
    //消费者
    else
    {
        for (int i = 0; i < 5; i++)
        {
            semop(semid, &P2, 1);
            cout << "Consuming..." << endl;
            semop(semid, &V1, 1);
            cout << "after consuming, space = " << semctl(semid, 0, GETVAL) << " , production = " << semctl(semid, 1, GETVAL) << endl;
            sleep(1);
        }
    }
    return 0;
}

int main()
{
    add_and_count();
    // producer_consumer();
    return 0;
}