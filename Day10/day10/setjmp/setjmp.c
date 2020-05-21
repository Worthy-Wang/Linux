#include <func.h>

jmp_buf envbuf;//存放程序执行的现场

void secondFunc()
{
	printf("I am secondFunc\n");
	longjmp(envbuf,5);
}
void fisrtFunc()
{
	printf("I am fisrtFunc\n");
	secondFunc();
	printf("secondFunc over\n");
}

int main()
{
	int ret;
	ret=setjmp(envbuf);
	if(0==ret)
	{
		fisrtFunc();
	}
	printf("main over\n");
}
