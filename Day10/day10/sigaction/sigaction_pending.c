#include <func.h>
//拿出正在挂起的信号集合
void sigFunc(int signum,siginfo_t *p,void *p1)
{
	printf("before sleep %d is coming\n",signum);
	sleep(3);
	sigset_t pending;
	sigpending(&pending);
	if(sigismember(&pending,SIGQUIT))
	{
		printf("SIGQUIT is pending\n");
	}else{
		printf("SIGQUIT not is pending\n");
	}
	printf("after sleep %d is coming\n",signum);
}
int main()
{
	int ret;
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sigFunc;
	act.sa_flags=SA_SIGINFO;
	sigaddset(&act.sa_mask,SIGQUIT);
	ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	ret=sigaction(SIGQUIT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	while(1);
}
