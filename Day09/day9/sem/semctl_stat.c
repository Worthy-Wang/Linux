#include <Unixfunc.h>

int main()
{
	int semArrId;
	semArrId=semget(1000,2,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	int ret;
	struct semid_ds buf;
	ret=semctl(semArrId,0,IPC_STAT,&buf);
	ERROR_CHECK(ret,-1,"semctl");
	printf("mode=%o,sem_nsems=%ld\n",buf.sem_perm.mode,buf.sem_nsems);
	buf.sem_perm.mode=0666;
	semctl(semArrId,0,IPC_SET,&buf);
	return 0;
}
