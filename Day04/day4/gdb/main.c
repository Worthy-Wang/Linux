#include <stdio.h>
#include <stdlib.h>
void print()
{
	int iNum=10;
	printf("I am print iNum=%d\n",iNum);
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int iNum=atoi(argv[1]);
	int j=atoi(argv[2]);
	printf("sum=%d\n",iNum+j);
	int arr[5]={1,2,3,4,5};
	for(iNum=0;iNum<j;iNum++)
	{
		printf("hello world\n");
	}
	print();
	return 0;
}
