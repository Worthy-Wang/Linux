#include <func.h>

void Daemon()
{
	setsid();
	chdir("/");//为了磁盘能够正常解除挂载
	umask(0);
	int i;
	for(i=0;i<3;i++)
	{
		close(i);
	}
}

int main()
{
	if(fork())
	{
		exit(0);
	}
	Daemon();
	while(1)
	{
		sleep(1);
	}
	return 0;
}
