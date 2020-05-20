#include <Unixfunc.h>

void print()
{
	printf("I am print\n");
	_exit(5);
}

int main()
{
	print();
	printf("I am main\n");
	return 0;
}
