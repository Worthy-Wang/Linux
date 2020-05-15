#include <stdio.h>
typedef struct{
	int num;
	char name[20];
	float score;
}Stu;
int main()
{
	Stu s={1001,"lele",98.5};
	char buf[128]={0};
	sprintf(buf,"%d %s %5.2f",s.num,s.name,s.score);
	printf("%s\n",buf);
	return 0;
}
