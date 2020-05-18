#include <Unixfunc.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdw=open(argv[1],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	fdr=open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open1");
	printf("chat2 fdr=%d,fdw=%d\n",fdr,fdw);
	char buf[128]={0};
	while(1)
	{
		memset(buf,0,sizeof(buf));
		read(0,buf,sizeof(buf));
		write(fdw,buf,strlen(buf)-1);
		memset(buf,0,sizeof(buf));
		read(fdr,buf,sizeof(buf));
		printf("%s\n",buf);
	}
	return 0;
}

