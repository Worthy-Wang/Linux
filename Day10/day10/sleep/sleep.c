#include <func.h>

void sigFunc(int signum)
{
}
int main()
{
	signal(SIGALRM,sigFunc);
	alarm(5);
	pause();//放弃CPU
	return 0;
}
