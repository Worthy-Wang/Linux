#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	ftruncate(fd,4096);
	char *p;
	struct stat buf;
	fstat(fd,&buf);
	p=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED ,fd,0);
	ERROR_CHECK(p,(char*)-1,"mmap");
	memcpy(p,"HELLO",5);
	munmap(p,buf.st_size);
	return 0;
}
