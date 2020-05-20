#include <Unixfunc.h>

int main()
{
	int semArrId;
	semArrId=semget(1000,2,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	int ret;
	unsigned short arr[2]={3,4};
	ret=semctl(semArrId,0,SETALL,arr);
	ERROR_CHECK(ret,-1,"semctl");
	bzero(arr,sizeof(arr));
	ret=semctl(semArrId,0,GETALL,arr);
	printf("arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);
	return 0;
}
