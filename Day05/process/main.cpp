#include <Unixfunc.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

/*
linux 进程控制
*/

/*
一.进程标识
1. getpid()
2. getppid()
3. getuid()
*/
void test0()
{
    cout << "本进程ID:" << getpid() << endl;
    cout << "父进程ID:" << getppid() << endl;
    cout << "进程所属的用户ID" << getuid() << endl;
    cout << "进程所属的组ID" << getgid() << endl;
}

/*
二.进程的创建
1. int system(const char* command)
相当于在终端执行 command 语句
*/
void test1()
{
    system("ls -l"); //相当于在终端执行shell语言 ls -l
    system("clear"); //相当于在终端执行shell语言 clear
}

/*
2. pid_t fork(void)
返回值pid_t 
* 0则表示为子进程
* -1表示创建进程失败
* 父进程的返回值是子进程的进程号

可能会有疑问：
明明只有一段代码，为什么有两个进程可以执行？
在进行fork操作之后，fork以下的代码相当于有两个进程同时执行， 也就是有两个 有着不同pid值的test2()函数， 分别执行以下的代码。

fork调用子进程的过程中值得注意的一点：子进程会继承父进程的文件句柄
尽管在父进程中已经将fd进行了close, 但是子进程中不会相互收到影响
*/

void test2()
{
    int fd = open("file", O_RDWR | O_CREAT, 0755);
    pid_t pid = fork();
    if (pid < 0)
        cout << "fork ERROR" << endl;
    else if (pid == 0) //子进程
    {
        sleep(3);
        cout << "this is child process" << endl;
        char buff[100] = {0};
        read(fd, buff, sizeof(buff));
        cout << "buff:" << buff << endl;
        close(fd); 
    }
    else //父进程
    {
        cout << "this is parent process" << endl;
        close(fd);
    }
}

/*
3.孤儿进程
父进程提前退出，子进程仍在运行的进程叫做孤儿进程。
孤儿进程的状态为 R(运行)，其PPID(父进程) 为 init（祖先进程），也就是说当父进程提前退出时，祖先进程会来接管孤儿进程。

孤儿进程是没有危害的，init祖先进程会帮助我们处理。
*/
void test3()
{
    pid_t pid = fork();
    if (pid < 0)
        cout << "fork ERROR" << endl;
    else if (pid == 0) //子进程
    {
        sleep(30);
        cout << "this is child process" << endl;
    }
    else //父进程
    {
        cout << "this is parent process" << endl;
    }
}

/*
4.僵尸进程
子进程先退出，父进程仍在运行，那么叫子进程为僵尸进程。
此时子进程的进程状态为 Z(zombie僵尸)，因为没有父进程为其进行清理子进程的环境

此时在父进程中最好使用 wait(NULL) , 表示等待所有的子进程并清理环境
*/

void test4()
{
    pid_t pid = fork();
    if (pid < 0)
        cout << "fork ERROR" << endl;
    else if (pid == 0) //子进程
    {
        cout << "this is child process" << endl;
    }
    else //父进程
    {
        wait(NULL);//等待所有的子进程，来帮助清理子进程，注意必须放在父进程的一开头
        sleep(30);
        cout << "this is parent process" << endl;
    }
}


/*
5.守护进程
守护进程是一种特殊的后台程序，它独立于终端环境，不受终端的控制与影响，会一直运行到系统关闭
如下，编写一个守护进程，每隔1s向日志文件中写一条信息。
*/

void test5()
{
    if (fork() > 0)
        exit(0);
    setsid();
    chdir("/");
    umask(0);
    for (int i = 0; i < 64; i++)
        close(i);
    int cnt = 0;
    while (cnt < 30)
    {
        syslog(LOG_INFO, "this is %d message", cnt);
        cnt ++;
        sleep(1);
    }   
}

int main()
{
    test5();
    return 0;
}