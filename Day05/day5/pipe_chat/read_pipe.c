#include <func.h>

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
	read(fdr,buf,sizeof(buf));
	printf("buf=%s\n",buf);
	write(fdw,"I am chat1",10);
	return 0;
}

