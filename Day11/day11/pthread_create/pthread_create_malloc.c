#include <func.h>
//线程函数
void* threadFunc(void *p)
{
	strcpy((char*)p,"helloworld");
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	char *pMain=(char*)malloc(20);
	ret=pthread_create(&pthID,NULL,threadFunc,pMain);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	ret=pthread_join(pthID,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %s\n",pMain);
	return 0;
}
