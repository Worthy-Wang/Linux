#include <stdio.h>
#include <string.h>
typedef struct{
	int num;
	char name[20];
	float score;
}Stu;
int main()
{
	Stu s;
	memset(&s,0,sizeof(s));
	char buf[128]="1001 lele 98.50";
	sscanf(buf,"%d%s%f",&s.num,s.name,&s.score);
	printf("%d %s %5.2f\n",s.num,s.name,s.score);
	return 0;
}
