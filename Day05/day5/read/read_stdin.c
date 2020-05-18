#include <func.h>

int main()
{
	char buf[128]={0};
	read(0,buf,sizeof(buf));
	printf("buf=%s\n",buf);
}
