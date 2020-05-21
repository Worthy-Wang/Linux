#include <func.h>
//主线程与子线程各加1000万
#define N 10000000
typedef struct{
	int num;
	pthread_mutex_t mutex;
}Data;
void* threadFunc(void *p)
{
	Data *pThreadInfo=(Data *)p;
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&pThreadInfo->mutex);
		pThreadInfo->num+=1;
		pthread_mutex_unlock(&pThreadInfo->mutex);
	}
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	Data threadInfo;
	threadInfo.num=0;
	ret=pthread_mutex_init(&threadInfo.mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	struct timeval start,end;
	gettimeofday(&start,NULL);
	ret=pthread_create(&pthID,NULL,threadFunc,&threadInfo);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&threadInfo.mutex);
		threadInfo.num+=1;
		pthread_mutex_unlock(&threadInfo.mutex);
	}
	pthread_join(pthID,NULL);
	gettimeofday(&end,NULL);
	ret=pthread_mutex_destroy(&threadInfo.mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	printf("I am main thread,%d,use time=%ld\n",threadInfo.num,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
	return 0;
}
