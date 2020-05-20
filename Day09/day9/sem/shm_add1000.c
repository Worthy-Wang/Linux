#include <Unixfunc.h>
#define N 10000000
int main()
{
	int shmid;
	shmid=shmget((key_t)0x1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int *pShm;
	pShm=(int*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	pShm[0]=0;
	int semArrId;
	semArrId=semget(1000,1,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	int ret;
	ret=semctl(semArrId,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	int i;
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	struct timeval start,end;
	gettimeofday(&start,NULL);//获取当前时间，秒 和 微秒
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			semop(semArrId,&sopp,1);
			pShm[0]=pShm[0]+1;
			semop(semArrId,&sopv,1);
		}
		return 0;
	}else{
		for(i=0;i<N;i++)
		{
			semop(semArrId,&sopp,1);
			pShm[0]=pShm[0]+1;
			semop(semArrId,&sopv,1);
		}
		wait(NULL);
		gettimeofday(&end,NULL);
		printf("result=%d,use time=%ld\n",pShm[0],(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
		return 0;
	}
}
