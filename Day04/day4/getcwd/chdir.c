#include <func.h>
//改变当前进程的工作目录
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	char path[512]={0};
	getcwd(path,sizeof(path));
	printf("%s\n",path);
	int ret;
	ret=chdir(argv[1]);
	if(-1==ret)
	{
		perror("chdir");
		return -1;
	}
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
