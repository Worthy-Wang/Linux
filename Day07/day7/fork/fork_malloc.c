#include <func.h>

int main()
{
	pid_t pid;
	char *p=(char*)malloc(20);
	strcpy(p,"hello");
	pid=fork();
	if(0==pid)
	{
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		printf("child p=%s,%p\n",p,p);
	}else{
		printf("I am prarent process,child pid=%d,self pid=%d\n",pid,getpid());
		printf("parent num=%s,%p\n",p,p);
		strcpy(p,"world");
		printf("parent num=%s,%p\n",p,p);
		sleep(1);
	}
}
