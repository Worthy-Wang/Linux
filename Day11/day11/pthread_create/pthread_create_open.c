#include <func.h>
//线程函数
void* threadFunc(void *p)
{
	int fd=*(int*)p;
	close(fd);
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t pthID;//线程ID
	int ret;
	int fd=open("file",O_RDWR);
	ret=pthread_create(&pthID,NULL,threadFunc,&fd);
	if(ret!=0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	ret=pthread_join(pthID,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	char buf[128]={0};
	ret=read(fd,buf,sizeof(buf));
	printf("I am main thread %d,%s\n",ret,buf);
	return 0;
}
