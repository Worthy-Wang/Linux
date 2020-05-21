#include <func.h>

int main()
{
	signal(SIGINT,SIG_IGN);
	sleep(5);
	sigset_t pending;
	sigemptyset(&pending);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
	{
		printf("SIGINT is pending\n");
	}else{
		printf("SIGINT not is pending\n");
	}
	printf("this is important code\n");
	signal(SIGINT,SIG_DFL);
	return 0;
}
