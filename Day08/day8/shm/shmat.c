#include <func.h>

int main()
{
	int shmid;
	shmid=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	char *pShm;
	pShm=(char*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	strcpy(pShm,"hello");
	while(1);
	return 0;
}
