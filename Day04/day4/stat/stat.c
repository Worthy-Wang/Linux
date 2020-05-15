#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	struct stat buf;
	int ret;
	ret=stat(argv[1],&buf);
	ERROR_CHECK(ret,-1,"stat");
	printf("%ld %x %ld %s %s %ld %s\n",buf.st_ino,buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,ctime(&buf.st_mtime));
	return 0;
}
