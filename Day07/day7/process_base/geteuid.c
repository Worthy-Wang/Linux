#include <func.h>

int main()
{
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
	while(1);
}
