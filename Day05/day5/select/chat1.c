#include <Unixfunc.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	fdw=open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open1");
	printf("chat1 fdr=%d,fdw=%d\n",fdr,fdw);
	char buf[128]={0};
	fd_set rdset;
	int ret;
	struct timeval t;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		memset(&t,0,sizeof(t));
		t.tv_sec=3;
		ret=select(fdr+1,&rdset,NULL,NULL,&t);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret)//代表对端断开
				{
					printf("byebye\n");
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("byebye\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}else{
			printf("time out\n");
		}
	}
	close(fdw);
	close(fdr);
	return 0;
}

