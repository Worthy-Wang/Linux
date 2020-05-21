#include <func.h>
//线程函数
void* threadFunc(void *p)
{
	printf("I am child thread %d\n",*(int*)p);
	return NULL;
}

int main()
{
	pthread_t pthID,pthID1;//线程ID
	int ret;
	int threadNum=1;
	ret=pthread_create(&pthID,NULL,threadFunc,&threadNum);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	threadNum=2;
	pthread_create(&pthID1,NULL,threadFunc,&threadNum);
	pthread_join(pthID,NULL);
	pthread_join(pthID1,NULL);
	printf("I am main thread\n");
	return 0;
}
