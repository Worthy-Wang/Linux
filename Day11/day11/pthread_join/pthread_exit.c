#include <func.h>
void print()
{
	printf("I am print\n");
	pthread_exit(NULL);
}
//线程函数
void* threadFunc(void *p)
{
	printf("I am child thread\n");
	print();
	printf("after print\n");
	return NULL;
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
	pthread_join(pthID,NULL);
	printf("I am main thread\n");
	return 0;
}
