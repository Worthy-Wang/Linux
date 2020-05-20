#include <iostream>
#include <Unixfunc.h>
using namespace std;

/*
1、创建一个无名管道，fork子进程，然后子进程向管道写端写Hello，父进程接收数据并打印
*/
int test1()
{
    int fds[2];
    pipe(fds);
    if (fork() > 0)
    {
        sleep(1);
        close(fds[1]);
        char buf[100] = {0};
        read(fds[0], buf, sizeof(buf));
        cout << "father reading from pipe:" << buf << endl;
        wait(NULL);
        exit(0);
    }
    else
    {
        close(fds[0]);
        write(fds[1], "Hello", 5);
        exit(0);
    }
    return 0;
}

/*
2、新建共享内存，连接，然后往共享内存写入How are you,然后另外一个进程连接共享内存，读取数据并打印显示,删除共享内存
*/
int test2()
{
    int ret;
    int shmid = shmget((key_t)0x1234, 1024, 0666 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    char *buf = (char *)shmat(shmid, NULL, 0);
    ERROR_CHECK(buf, (char *)-1, "shmat");
    if (fork() > 0)
    {
        strcpy(buf, "How are you");
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    }
    else
    {
        sleep(1);
        cout << "reading shared memory:" << buf << endl;
        exit(0);
    }

    return 0;
}

/*
3、两个进程对一个共享内存各加1000万，查看最后结果
*/
int test3()
{
    int ret;
    int shmid = shmget((key_t)0x1234, 1024, 0666 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    int *buf = (int *)shmat(shmid, NULL, 0);
    ERROR_CHECK(buf, (int *)-1, "shmat");
    if (fork() > 0)
    {
        int cnt = 10000000;
        while (cnt > 0)
        {
            (*buf)++;
            cnt--;
        }
        wait(NULL);
        cout << "total: " << *buf << endl;
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        int cnt = 10000000;
        while (cnt > 0)
        {
            (*buf)++;
            cnt--;
        }
    }
    return 0;
}

int main()
{
    test3();
    return 0;
}