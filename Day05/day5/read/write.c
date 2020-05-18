#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	int arr[5]={1,2,3,4,5};
	int ret;
	ret=write(fd,arr,sizeof(arr));
	ERROR_CHECK(fd,-1,"write");
	lseek(fd,0,SEEK_SET);
	memset(arr,0,sizeof(arr));
	ret=read(fd,arr,sizeof(arr));
	ERROR_CHECK(fd,-1,"read");
	printf("ret=%d,arr[0]=%d,arr[3]=%d\n",ret,arr[0],arr[3]);
	return 0;
}
