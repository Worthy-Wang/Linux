#include <Unixfunc.h>
//使用计数信号量
int main()
{
	int semArrId;
	semArrId=semget(1000,2,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	int ret;
	unsigned short arr[2]={10,0};//0号信号量代表仓库位置个数，1号信号量代表产品数目
	ret=semctl(semArrId,0,SETALL,arr);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	if(!fork())
	{
		//生成者
		sopp.sem_num=0;
		sopp.sem_op=-1;
		sopp.sem_flg=0;
		sopv.sem_num=1;
		sopv.sem_op=1;
		sopv.sem_flg=0;
		while(1)
		{
			printf("I am producer,productor=%d,space=%d\n",semctl(semArrId,1,GETVAL),semctl(semArrId,0,GETVAL));
			semop(semArrId,&sopp,1);
			printf("I will produce\n");
			semop(semArrId,&sopv,1);
			printf("I am producer,productor=%d,space=%d\n",semctl(semArrId,1,GETVAL),semctl(semArrId,0,GETVAL));
			sleep(1);
		}
	}else{
		//消费者
		sopp.sem_num=1;
		sopp.sem_op=-1;
		sopp.sem_flg=0;
		sopv.sem_num=0;
		sopv.sem_op=1;
		sopv.sem_flg=0;
		while(1)
		{
			printf("I am customer,productor=%d,space=%d\n",semctl(semArrId,1,GETVAL),semctl(semArrId,0,GETVAL));
			semop(semArrId,&sopp,1);
			printf("I will consume\n");
			semop(semArrId,&sopv,1);
			printf("I am customer,productor=%d,space=%d\n",semctl(semArrId,1,GETVAL),semctl(semArrId,0,GETVAL));
			sleep(2);
		}
	}

	return 0;
}
