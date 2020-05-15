#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int ret;
	ret=chmod(argv[1],0666);
	if(-1==ret)
	{
		perror("chmod");
		return -1;
	}
	return 0;
}
