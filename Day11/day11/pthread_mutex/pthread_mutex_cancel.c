#include <func.h>
void cleanup(void *p)
{
	pthread_mutex_unlock((pthread_mutex_t*)p);
	printf("unlock success\n");
}
//线程加锁以后被cancel怎么办
void* threadFunc(void *p)
{
	pthread_mutex_t* pMutex=(pthread_mutex_t*)p;
	pthread_cleanup_push(cleanup,pMutex);
	pthread_mutex_lock(pMutex);
	sleep(3);
	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}
int main()
{
	pthread_mutex_t mutex;
	int ret;
	ret=pthread_mutex_init(&mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	pthread_t pthId[2];
	int i;
	for(i=0;i<2;i++)
	{
		pthread_create(pthId+i,NULL,threadFunc,&mutex);
	}
	for(i=0;i<2;i++)
	{
		ret=pthread_cancel(pthId[i]);
		THREAD_ERROR_CHECK(ret,"pthread_cancel");
	}
	for(i=0;i<2;i++)
	{
		pthread_join(pthId[i],NULL);
	}
	ret=pthread_mutex_destroy(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	return 0;
}
