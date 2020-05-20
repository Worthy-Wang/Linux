#include <Unixfunc.h>

int main()
{
	FILE* fp;
	fp=popen("./scanf","w");
	ERROR_CHECK(fp,NULL,"popen");
	char buf[128]="3 4";
	fputs(buf,fp);
	pclose(fp);
	return 0;
}
