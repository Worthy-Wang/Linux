#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd,fd1;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("\n");
	close(1);
	fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	close(fd);//关闭对应文件
	printf("you can't see me\n");
	return 0;
}

