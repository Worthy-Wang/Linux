#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"ab+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fread(buf,sizeof(char),5,fp);//从文件中读取5个字节
	printf("buf=%s\n",buf);
	strcpy(buf,"how are you");
	fwrite(buf,sizeof(char),strlen(buf),fp);
	memset(buf,0,sizeof(buf));
	fread(buf,sizeof(char),5,fp);
	printf("buf=%s\n",buf);
	fclose(fp);
}
