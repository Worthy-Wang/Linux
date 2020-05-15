#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	DIR *dir;
	dir=opendir(argv[1]);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	off_t pos;
	while(p=readdir(dir))
	{
		printf("%ld %d %d %s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
		if(!strcmp(p->d_name,"a.out"))
		{
			pos=telldir(dir);
		}
	}
	printf("--------------\n");
	seekdir(dir,pos);
	p=readdir(dir);
	printf("%s\n",p->d_name);
	closedir(dir);
	return 0;
}
