#include <func.h>
//制造文件空洞
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	int ret;
	ret=lseek(fd,1024,SEEK_SET);
	printf("lseek ret=%d\n",ret);
	char c='H';
	write(fd,&c,sizeof(c));
	close(fd);
	return 0;
}
