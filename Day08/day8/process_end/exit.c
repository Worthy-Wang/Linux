#include <func.h>

void print()
{
	printf("I am print");
	exit(5);
}

int main()
{
	print();
	printf("I am main\n");
	return 0;
}
