#include <func.h>

void* threadFunc(void* p)
{
	while(1);
}

int main()
{
	pthread_t pthId;
	pthread_create(&pthId,NULL,threadFunc,NULL);
	int ret;
	ret=pthread_cancel(pthId);
	THREAD_ERROR_CHECK(ret,"pthread_cancel");
	pthread_join(pthId,NULL);
	return 0;
}
