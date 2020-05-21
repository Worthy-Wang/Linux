#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1)
{
	printf("%d is coming\n",signum);
}
int main()
{
	int ret;
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sigFunc;
	act.sa_flags=SA_SIGINFO|SA_RESETHAND;
	ret=sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	while(1);
}
