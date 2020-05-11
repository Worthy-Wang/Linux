#include <stdio.h>
#define NUM 1+2
void print()
{
	int i=10;
	printf("i=%d\n",i);
}
int main()
{
	int *p;
	int arr[3]={1,2,3};
	int i=NUM*NUM;
	int j=10;
	arr[2]=4;
	p=arr;
	printf("i=%d\n",i);
	printf("j=%d\n",j);
	for(i=0;i<5;i++)
	{
		printf("Hello world\n");
	}
	print();
	return 0;
}
