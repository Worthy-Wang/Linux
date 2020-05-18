#include <func.h>

int main(int argc,char* argv[])
{
	FILE *fp;
	ARGS_CHECK(argc,2);
	fp=fopen(argv[1],"rb+");
	char buf[128]={0};
	int fd;
	fd=fileno(fp);
	read(fd,buf,sizeof(buf));
	printf("buf=%s\n",buf);
}
