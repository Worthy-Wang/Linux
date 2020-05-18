#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd,fd1;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	fd1=open(argv[1],O_RDWR);
	char buf[128]={0};
	int ret;
	ret=read(fd,buf,5);
	ERROR_CHECK(ret,-1,"read");
	printf("ret=%d,buf=%s\n",ret,buf);
	memset(buf,0,sizeof(buf));
	ret=read(fd1,buf,5);
	printf("ret=%d,buf=%s\n",ret,buf);
	return 0;
}

