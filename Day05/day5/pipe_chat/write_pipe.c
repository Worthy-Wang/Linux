#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdw=open(argv[1],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	fdr=open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open1");
	printf("chat2 fdr=%d,fdw=%d\n",fdr,fdw);
	write(fdw,"I am chat2",10);
	char buf[128]={0};
	read(fdr,buf,sizeof(buf));
	printf("buf=%s\n",buf);
	return 0;
}

