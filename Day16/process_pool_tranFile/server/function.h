#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
using namespace std;

#define ARGS_CHECK(argc, val) {if (argc!=val){printf("Args ERROR\n"); return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) \
        {printf("%s:%s\n",funcName,strerror(ret));return -1;}}
#define ERROR_CHECK(ret, retval, filename) {if (ret == retval){perror(filename); return -1;}}  

/*****************************************结构体定义部分******************************************/
#define PROCESSNUM 10
#define IP "172.21.0.7"
#define PORT 2000
#define FILENAME "file"

struct Process_data
{
    pid_t pid;
    int fd;
    bool busy;
};

int tcpInit(int*);
int makeProcess(Process_data* pArr);
void doingTask(int fd);
int sendFd(int,int);
int recvFd(int,int*);
int tranFile(int);