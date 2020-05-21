#include <func.h>
//不能跨函数使用goto
void print()
{
label:
	printf("I am print\n");
}
int main()
{
	int i=0;
	if(i<3)
	{
		printf("start lable\n");
		i++;
		goto label;
	}
}
