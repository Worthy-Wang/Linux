#include <Unixfunc.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

/*
案例二：非亲属进程间通信
写端 写入HelloWorld ， 读端进行读取
*/


int main()
{
    key_t key = ftok("file", 1);
    ERROR_CHECK(key, -1, "ftok");
    int shmid = shmget(key, 1024, 0600);
    ERROR_CHECK(shmid, -1, "shmget");
    char* buf = (char*)shmat(shmid, NULL, 0);
    ERROR_CHECK(buf, (char*)-1, "shmat");
    cout << "reading from shared memory:" << buf << endl;
    int ret = shmctl(shmid, IPC_RMID, NULL);
    ERROR_CHECK(ret, -1, "shmctl");
    return 0;   
}