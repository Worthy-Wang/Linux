#include <func.h>
//设置锁的属性，设置为检错锁
int main()
{
	pthread_mutex_t mutex;
	int ret;
	pthread_mutexattr_t mutexAttr;
	pthread_mutexattr_init(&mutexAttr);
	pthread_mutexattr_settype(&mutexAttr,PTHREAD_MUTEX_RECURSIVE);
	ret=pthread_mutex_init(&mutex,&mutexAttr);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	pthread_mutex_lock(&mutex);
	ret=pthread_mutex_lock(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
	printf("you can't see me\n");
	ret=pthread_mutex_destroy(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	return 0;
}
