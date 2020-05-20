#include <func.h>

int main()
{
	int semArrId;
	semArrId=semget(1000,1,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	int ret;
	ret=semctl(semArrId,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	int semValue;
	semValue=semctl(semArrId,0,GETVAL);
	printf("semValue=%d\n",semValue);
	return 0;
}
