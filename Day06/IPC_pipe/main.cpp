#include <Unixfunc.h>
#include <iostream>
using namespace std;

/*
Linux IPC(一) 管道

1.读写标准管道流
* FILE *popen(const char *__command, const char *__modes)
command 代表shell指令
modes 分为 "r"读 和 "w"写
具体功能和Linux命令中的管道基本相同
*/
void test1()
{
    FILE *fp = popen("wc", "w");
    char buf[100] = "aa bbb ccc dddd\n \n eeeee";
    fwrite(buf, sizeof(char), strlen(buf) - 1, fp);
    pclose(fp);
}

/*
2.无名管道
* 只能在亲缘进程之间使用
* 为半双工管道（即只能一端读，一端写）
* 无名管道是特殊的文件，只能存在于内存中
案例：创建一个无名管道 与 父子进程，进行父写子读
*/
void test2()
{
    int fds[2] = {0};
    pipe(fds); //fds[0] = 3, fds[1] = 4;
    if (fork() == 0)
    {
        close(fds[1]);
        char buf[100] = {0};
        read(fds[0], buf, sizeof(buf));
        cout << "child process reading:" << buf << endl;
        close(fds[0]);
        exit(0);
    }
    close(fds[0]);
    char buf[100] = "Helloworld";
    write(fds[1], buf, strlen(buf));
    cout << "father process is writing" << endl;
    close(fds[1]);
    wait(NULL);
}

int main()
{
    test2();
    return 0;
}