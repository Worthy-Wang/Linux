#include <stdio.h>

int main()
{
	int i=10;
#ifdef DEBUG
	printf("this is debug information,i=%d\n",i);
#endif
	return 0;
}
