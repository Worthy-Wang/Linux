#include <func.h>

int main()
{
	char buf[128];
	read(0,buf,sizeof(buf));
	printf("%s\n",buf);
}
