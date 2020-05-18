#include <Unixfunc.h>

int main()
{
	int fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	write(fd,"hello",5);
	int ret;
	ret=fsync(fd);
	ERROR_CHECK(ret,-1,"fsync");
	// sleep(20);
	close(fd);
	return 0;
}
