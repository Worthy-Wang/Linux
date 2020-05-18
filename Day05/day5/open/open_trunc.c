#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDONLY|O_TRUNC,0600);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}
