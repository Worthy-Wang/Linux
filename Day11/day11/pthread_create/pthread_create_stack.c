#include <func.h>
//线程函数
void* threadFunc(void *p)
{
	*(int*)p=10;
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	int num=0;
	ret=pthread_create(&pthID,NULL,threadFunc,&num);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	ret=pthread_join(pthID,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %d\n",num);
	return 0;
}
