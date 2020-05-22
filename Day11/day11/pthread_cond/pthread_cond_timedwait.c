#include <Unixfunc.h>
typedef struct{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}Data;
void* threadFunc(void* p)
{
	Data* pthreadInfo=(Data*)p;
	int ret;
	struct timespec t;
	t.tv_nsec=0;
	t.tv_sec=time(NULL) + 5;
	pthread_mutex_lock(&pthreadInfo->mutex);
	ret=pthread_cond_timedwait(&pthreadInfo->cond,&pthreadInfo->mutex,&t);
	printf("pthread_cond_timedwait ret=%d\n",ret);
	pthread_mutex_unlock(&pthreadInfo->mutex);
	printf("I am child,after wait\n");
	pthread_exit(NULL);
}
int main()
{
	Data threadInfo;
	int ret;
	ret=pthread_cond_init(&threadInfo.cond,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_cond_init");
	pthread_mutex_init(&threadInfo.mutex,NULL);
	pthread_t pthId;
	pthread_create(&pthId,NULL,threadFunc,&threadInfo);
	sleep(10);
	ret=pthread_cond_signal(&threadInfo.cond);
	THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
	printf("send signal ok\n");
	pthread_join(pthId,NULL);
	printf("I am main thread\n");
	return 0;
}
