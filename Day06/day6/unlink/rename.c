#include <Unixfunc.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int ret;
	ret=rename(argv[1],argv[2]);
	ERROR_CHECK(ret,-1,"rename");
	return 0;
}
