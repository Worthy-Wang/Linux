#include <func.h>

int main()
{
	pid_t pid,ppid;
	pid=getpid();
	ppid=getppid();
	printf("pid=%d,ppid=%d\n",pid,ppid);
	while(1);
}
