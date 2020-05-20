#include <func.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		while(1);
	}else{
		printf("I am prarent\n");
		return 0;
	}
}
