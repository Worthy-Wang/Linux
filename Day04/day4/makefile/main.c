#include <stdio.h>

void print();
int sub(int,int);
int main()
{
	printf("I am main\n");
	print();
	print();
	printf("sub result=%d\n",sub(5,3));
	return 0;
}
