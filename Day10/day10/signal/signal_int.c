#include <func.h>
void sigFunc(int signum)
{
	printf("%d is coming\n",signum);
}
int main()
{
	if(signal(SIGINT,sigFunc)==SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	while(1);
}
