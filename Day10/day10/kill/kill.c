#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int signum=atoi(argv[1]);
	pid_t pid=atoi(argv[2]);
	int ret;
	ret=kill(pid,signum);
	ERROR_CHECK(ret,-1,"kill");
	return 0;
}
