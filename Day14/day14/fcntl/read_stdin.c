#include <Unixfunc.h>
void changeNonblock(int fd)
{
	int status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;
	fcntl(fd,F_SETFL,status);
}
int main()
{
	sleep(5);
	char buf[128]={0};
	int ret;
	changeNonblock(0);
	ret=read(0,buf,sizeof(buf));
	printf("ret=%d,buf=%s\n",ret,buf);
	return 0;
}
