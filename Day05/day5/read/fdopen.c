#include <func.h>

int main(int argc,char* argv[])
{
	FILE *fp;
	ARGS_CHECK(argc,2);
	int fd=open(argv[1],O_RDWR|O_CREAT,0600);
	ERROR_CHECK(fd,-1,"open");
	fp=fdopen(fd,"rb+");
	ERROR_CHECK(fp,NULL,"fdopen");
	return 0;
}
