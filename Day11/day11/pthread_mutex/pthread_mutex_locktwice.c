#include <func.h>

int main()
{
	pthread_mutex_t mutex;
	int ret;
	ret=pthread_mutex_init(&mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	printf("you can't see me\n");
	ret=pthread_mutex_destroy(&mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	return 0;
}
