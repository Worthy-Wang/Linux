#include <stdio.h>

int main(int argc,char* argv[])
{
	printf("I am happy\n");//标准输出
	FILE *fp;
	int i;
	fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");//标准错误
		return -1;
	}
}
