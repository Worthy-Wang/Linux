#include <func.h>

int main()
{
	printf("I am execute execl\n");
	const char *envp[]={"PATH=/usr/bin",NULL};
	int ret=execle("./change_env","change_env","first","second",NULL,envp);
	ERROR_CHECK(ret,-1,"execle");
	printf("you can't see me\n");
}
