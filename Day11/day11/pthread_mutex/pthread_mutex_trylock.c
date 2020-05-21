#include <func.h>
//trylock尝试加锁
int main()
{
	pthread_mutex_t mutex;
	int ret;
	ret=pthread_mutex_init(&mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	pthread_mutex_lock(&mutex);
	ret=pthread_mutex_trylock(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_trylock");
	ret=pthread_mutex_destroy(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	return 0;
}
