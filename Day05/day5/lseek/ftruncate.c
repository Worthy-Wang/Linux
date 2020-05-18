#include <func.h>
//改变文件大小，变小，变大
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	int ret;
	ret=ftruncate(fd,1024);
	ERROR_CHECK(ret,-1,"ftruncate");
	close(fd);
	return 0;
}
