#include <func.h>
int main()
{
	if(signal(SIGINT,SIG_IGN)==SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	while(1);
}
