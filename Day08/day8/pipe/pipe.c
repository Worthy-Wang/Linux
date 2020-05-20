#include <Unixfunc.h>

int main()
{
	int fds[2];
	pipe(fds);//开启一条管道
	if(!fork())
	{
		close(fds[1]);
		char buf[128]={0};
		read(fds[0],buf,sizeof(buf));//通过管道的读端读取数据
		printf("child gets %s\n",buf);
	}else{
		sleep(3);
		close(fds[0]);
		write(fds[1],"hello",5);
		wait(NULL);
		return 0;
	}
}
