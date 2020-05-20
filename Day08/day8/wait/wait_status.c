#include <func.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		return 5;
	}else{
		printf("I am prarent\n");
		pid_t childPid;
		int status;
		childPid=wait(&status);
		if(WIFEXITED(status))
		{
			printf("child exit normal %d\n",WEXITSTATUS(status));
		}else{
			printf("child crash\n");
		}
		printf("childPid is %d\n",childPid);
		return 0;
	}
}
