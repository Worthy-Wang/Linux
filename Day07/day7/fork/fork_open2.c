#include <func.h>
//进程各自打开
int main()
{
	pid_t pid;
	int ret;
	pid=fork();
	if(0==pid)
	{
		int fd=open("file",O_RDWR);
		printf("I am child process,pid=%d,ppid=%d\n",getpid(),getppid());
		ret=write(fd,"world",5);
		ERROR_CHECK(ret,-1,"write");
	}else{
		int fd=open("file",O_RDWR);
		printf("I am prarent process,child pid=%d,self pid=%d\n",pid,getpid());
		ret=write(fd,"hello",5);
		ERROR_CHECK(ret,-1,"write");
		sleep(1);
	}
}
