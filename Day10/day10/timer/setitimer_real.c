#include <func.h>

void sigFunc(int signum)
{
	time_t now;
	now=time(NULL);
	printf("%s\n",ctime(&now));
}
int main()
{
	signal(SIGALRM,sigFunc);
	struct itimerval t;
	bzero(&t,sizeof(t));
	t.it_value.tv_sec=3;
	t.it_interval.tv_sec=2;
	int ret;
	sigFunc(0);
	ret=setitimer(ITIMER_REAL,&t,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	char buf[128]={0};
	read(STDIN_FILENO,buf,sizeof(buf));
	printf("buf=%s\n",buf);
	while(1);
}
	

