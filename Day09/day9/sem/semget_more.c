#include <func.h>
//创建多个信号量
int main()
{
	int semArrId;
	semArrId=semget(1000,2,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	return 0;
}
