#include <func.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
	}else{
		printf("I am prarent\n");
		while(1);
		return 0;
	}
}
