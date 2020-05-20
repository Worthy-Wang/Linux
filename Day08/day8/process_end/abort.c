#include <Unixfunc.h>

void print()
{
	printf("I am print\n");
	abort();
	return;
}

int main()
{
	print();
	printf("I am main\n");
	return 0;
}
