#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDONLY);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	char buf[128]={0};
	int ret;
	ret=read(fd,buf,sizeof(buf));
	ERROR_CHECK(ret,-1,"read");
	printf("buf=%s\n",buf);
	return 0;
}
