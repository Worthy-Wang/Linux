#include <func.h>

int main()
{
	pid_t pid;
	int num=10;
	pid=fork();
	if(0==pid)
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		printf("child num=%d,%p\n",num,&num);
	}else{
		printf("I am prarent process,child pid=%d,self pid=%d\n",pid,getpid());
		printf("parent num=%d,%p\n",num,&num);
		num=5;
		printf("parent num=%d,%p\n",num,&num);
		sleep(1);
	}
}
