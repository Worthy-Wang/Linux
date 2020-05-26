#include <Unixfunc.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

/*
IPC 进程间通信(二) 共享内存

* key_t ftok(const char* filename, int proj_id)

通过已经存在的文件(filename) 与 proj_id(通常大于0) 创建出一个key值，用于进行共享内存的生成。

* int shmget(key_t key, size_t size, int shmflag)

key代表着与共享内存相关的一个关键字，如果该关键字已经存在，那么直接打开该共享内存，反之创建共享内存（一般使用 IPC_PRIVATE 用于创建新的共享内存）
size代表共享内存的大小
shmflag表示权限（一般为0600）, 如果时要进行创建的话则是 IPC_CREAT, 也可以加上 IPC_EXCL , 代表必须创建新的共享内存，已有则返回-1
成功返回shmid(共享内存段的id)，失败返回-1

* void* shmat(int shmid, char* shmaddr, int shmflag)

操作类似mmap内存映射。
shmid代表已经存在的共享内存id
shmaddr代表是否需要自定义共享内存映射到特定位置（一般为NULL，让系统来选择）
shmflag代表位标识（通常为0）
成功返回共享内存段的首地址，失败返回(void*)-1


* int shmctl(int shmid, int cmd, shmid_ds* buf)

一般用来删除共享内存段
shmid 代表共享内存段号
cmd 代表执行命令（一般为 IPC_RMID）
buf 结构体的信息（一般为NULL）

如果想要使用结构体的信息，也可以在cmd命令中输入 IPC_STAT 来获取结构体的信息，或是 IPC_SET 来设置结构体信息以改变共享内存


*/
int test0()
{
    int ret;
    key_t key = ftok("file", 1);
    ERROR_CHECK(key, -1, "ftok")
    int shmid = shmget(key, 1024, 0600 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    char *buf = (char *)shmat(shmid, NULL, 0);
    ERROR_CHECK(buf, (char *)-1, "shmat");
    strcpy(buf, "hello");
    cout << "shared memory:" << buf << endl;
    struct shmid_ds shminfo;
    ret = shmctl(shmid, IPC_STAT, &shminfo);
    ERROR_CHECK(ret, -1 , "IPC_STAT");
    cout << shminfo.shm_perm.cgid << endl;
    shminfo.shm_perm.cgid = 666;
    shmctl(shmid, IPC_SET, &shminfo);
    cout << shminfo.shm_perm.cgid << endl;

    ret = shmctl(shmid, IPC_RMID, NULL);
    ERROR_CHECK(ret, -1, "shmctl");
    return 0;
}

/*
案例一：亲属进程间通信，父进程写入Hello, 子进程读
*/
int test1()
{
    int shmid = shmget(IPC_PRIVATE, 1024, 0600);
    ERROR_CHECK(shmid, -1, "shmget");
    char* buf = (char*)shmat(shmid, NULL, 0);
    ERROR_CHECK(buf, (char*)-1, "shmat");
    
    if (fork() > 0)
    {
        strncpy(buf, "hello", 5);
        wait(NULL);
        int ret = shmctl(shmid, IPC_RMID, NULL);
        ERROR_CHECK(ret, -1, "shmctl");
        exit(0);
    }
    else
    {
        sleep(1);//等待父进程写完再读
        cout << "reading from shared memory:" << buf << endl; 
        exit(0);
    }
    return 0;
}


int main()
{
    test1();
    return 0;
}