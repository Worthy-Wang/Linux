#include <Unixfunc.h>

int main()
{
	FILE* fp;
	fp=popen("./print","r");
	ERROR_CHECK(fp,NULL,"popen");
	char buf[128]={0};
	fgets(buf,sizeof(buf),fp);
	printf("buf=%s\n",buf);
	pclose(fp);
	return 0;
}
