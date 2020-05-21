#include <func.h>
//清理函数
void cleanup(void *p)
{
	printf("I am cleanup\n");
	free(p);
}
//线程函数
void* threadFunc(void *p)
{
	p=malloc(20);
	pthread_cleanup_push(cleanup,p);
	printf("I am child thread\n");
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	ret=pthread_create(&pthID,NULL,threadFunc,NULL);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
//	ret=pthread_cancel(pthID);
//	THREAD_ERROR_CHECK(ret,"pthread_cancel");
	long threadRet;	
	ret=pthread_join(pthID,(void**)&threadRet);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %ld\n",threadRet);
	return 0;
}
