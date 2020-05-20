#include <Unixfunc.h>

int main()
{
	int shmid;
	shmid=shmget(1001,1024,0600|IPC_CREAT|IPC_EXCL);
	ERROR_CHECK(shmid,-1,"shmget");
	return 0;
}
