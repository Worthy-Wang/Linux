#include <func.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		while(1);
	}else{
		printf("I am prarent process,child pid=%d,self pid=%d\n",pid,getpid());
		sleep(1);
		while(1);
	}
}
