#include <func.h>
void print()
{
	printf("I am print\n");
	char *p=(char*)malloc(20);
	strcpy(p,"helloworld");
	pthread_exit(p);
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
	void *threadRet;
	ret=pthread_join(pthID,&threadRet);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %s\n",(char*)threadRet);
	free(threadRet);
	return 0;
}
