#include <Unixfunc.h>
#include <iostream>
using namespace std;

int Daemon()
{
    if (fork() > 0)
        exit(0);
    setsid();
    chdir("/tmp");
    umask(0);
    for (int i = 0; i < 64; i++)
        close(i);
    
    int fd = open("log", O_RDWR | O_CREAT, 0755);
    for (int i = 0; i < 10; i++)
    {
        write(fd, "I have run 5 seconds", strlen("I have run 5 seconds"));
        sleep(5);
    }
    close(fd);
    return 0;
}

int main()
{
    Daemon();
    return 0;
}