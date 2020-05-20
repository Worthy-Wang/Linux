#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
本篇文章参考于：https://www.jianshu.com/p/7e3045cf1ab8（Linux系统编程—消息队列）

IPC进程间通信(四) 消息队列


* int msgget(key_t key, int flags)

创建消息队列，key作为是否使用同一个消息队列的标识，flags标识权限。
创建成功返回消息队列的id号，失败返回-1

* int msgsnd(int __msqid, const void *__msgp, size_t __msgsz, int __msgflg)

发送消息到消息队列
msqid: 标识号
msgp : 结构体的地址（注意是传入整个结构体，系统会读取type类型）
msgsz : 结构体中buf的大小
msgflg : 为0则会阻塞，或是IPC_NOWAIT 则不会阻塞，一般为0

* int msgrcv(int __msqid, void *__msgp, size_t __msgsz, long __msgtyp, int __msgflg)

从消息队列接收信息
msqid：标识号
msqid: 标识号
msgp : 结构体的地址（注意是传入整个结构体，系统会读取type类型）
msgsz : 结构体中buf的大小
msgtyp: 接收消息的类型
msgflg : 为0则会阻塞，或是IPC_NOWAIT 则不会阻塞，一般为0
*/


/*
struct Msg的结构体:
这个结构体十分重要，其中type类型必须写在前面，因为我们传入msg结构体的过程中，会通过如下方式对结构体进行读取type类型
*/
struct Msg
{
    long type;
    char buf[100];
};
void test0()
{
    struct Msg msg;
    msg.type = 4;
    long val = 0;
    memcpy(&val, &msg, 8);
    cout << val << endl;
}

/*
案例一 ：亲属进程间的通信
父进程发送消息，子进程接收
*/
int main()
{
    int ret;
    int msqid = msgget((key_t)0x1234, 0666 | IPC_CREAT);
    ERROR_CHECK(msqid, -1, "msgget");
    struct Msg msg;
    memset(&msg, 0, sizeof(msg));
    if (fork() > 0)
    {
        msg.type = 1;
        strcpy(msg.buf, "hello, i am your dad");
        ret = msgsnd(msqid, &msg, sizeof(msg.buf), 0);
        ERROR_CHECK(ret, -1, "msgend");
        wait(NULL);
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
    else
    {
        sleep(1);
        ret = msgrcv(msqid, &msg, sizeof(msg.buf), 1, 0);
        ERROR_CHECK(ret, -1, "msgrcv");
        cout << "receiving from dad: " << msg.buf << endl;
        exit(0);
    }
    return 0;
}