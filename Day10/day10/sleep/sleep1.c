#include <func.h>
//sleep 和alarm混用
void sigFunc(int signum)
{
}
int main()
{
	signal(SIGALRM,sigFunc);
	alarm(2);
	sleep(10);
	printf("I am wake\n");
	pause();
	printf("later signal is coming\n");
	return 0;
}
