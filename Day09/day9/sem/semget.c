#include <func.h>

int main()
{
	int semArrId;
	semArrId=semget(1000,1,IPC_CREAT|0600);
	ERROR_CHECK(semArrId,-1,"semget");
	return 0;
}
