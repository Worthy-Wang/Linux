#include <func.h>

int main()
{
	sigset_t procMask;
	sigemptyset(&procMask);
	sigaddset(&procMask,SIGINT);
	int ret;
	ret=sigprocmask(SIG_BLOCK,&procMask,NULL);
	ERROR_CHECK(ret,-1,"sigprocmask");
	signal(SIGINT,SIG_IGN);
	sleep(5);
	printf("this is important code\n");
	sigset_t pending;
	sigemptyset(&pending);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
	{
		printf("SIGINT is pending\n");
	}else{
		printf("SIGINT not is pending\n");
	}
	sigprocmask(SIG_UNBLOCK,&procMask,NULL);
	return 0;
}
