#include <func.h>

int main()
{
	printf("I am execute execl\n");
	char buf1[10]="print1";
	char buf2[10]="print2";
	char *const argv[]={buf1,buf2,NULL};
	execv("./print",argv);
	printf("you can't see me\n");
}
