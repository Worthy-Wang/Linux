#include <Unixfunc.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(!pid)
	{
		printf("child pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
		setpgid(0,0);
		printf("child pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
		while(1);
	}else{
		printf("parent pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
		while(1);
	}
}

