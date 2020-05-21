#include <Unixfunc.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
	printf("%d is coming,send uid=%d,send pid=%d\n",signum,p->si_uid,p->si_pid);
}
int main()
{
	int ret;
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sigFunc;
	act.sa_flags=SA_SIGINFO;
	ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	while(1);
}
