#include <func.h>
//主线程与子线程各加1000万
#define N 10000000
void* threadFunc(void *p)
{
	int *num=(int*)p;
	int i;
	for(i=0;i<N;i++)
	{
		*num+=1;
	}
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	int num=0;
	ret=pthread_create(&pthID,NULL,threadFunc,&num);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	int i;
	for(i=0;i<N;i++)
	{
		num=num+1;
	}
	pthread_join(pthID,NULL);
	printf("I am main thread,%d\n",num);
	return 0;
}
