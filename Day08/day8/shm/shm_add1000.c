#include <Unixfunc.h>
#define N 10000000
int main()
{
	int shmid;
	shmid=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int *pShm;
	pShm=(int*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	pShm[0]=0;
	int i;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			pShm[0]=pShm[0]+1;
		}
		return 0;
	}else{
		for(i=0;i<N;i++)
		{
			pShm[0]=pShm[0]+1;
		}
		wait(NULL);
		printf("result=%d\n",pShm[0]);
		return 0;
	}
}
