#include <func.h>

void* threadFunc(void* p)
{
	printf("I am child thread\n");
	pthread_exit(NULL);
}
int main()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);//初始化线程属性
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_t pthId;
	pthread_create(&pthId,&attr,threadFunc,NULL);
	int ret;
	usleep(500);
	ret=pthread_join(pthId,NULL);
	printf("ret=%d\n",ret);
	return 0;
}
