#include <func.h>

int main()
{
	int shmid;
	shmid=shmget(1000,1024,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	return 0;
}
