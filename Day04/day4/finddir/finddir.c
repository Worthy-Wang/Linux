#include <func.h>
int printDir(char* dirName,int width)
{
	DIR *dir;
	dir=opendir(dirName);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	char path[512]={0};
	while((p=readdir(dir)))
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
		{
			continue;
		}
		printf("%*s%s\n",width,"-",p->d_name);
		sprintf(path,"%s%s%s",dirName,"/",p->d_name);
		if(4==p->d_type)
		{
			printDir(path,width+4);
		}
	}
	closedir(dir);
}

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	puts(argv[1]);//传入的路径打印
	printDir(argv[1],4);
	return 0;
}
