#include "func.h"

int tranFile(int new_fd)
{
	train t;//定义发送数据的结构体
	int ret;
	t.dataLen=strlen(FILENAME);
	strcpy(t.buf,FILENAME);
	//发送文件名给客户端
	ret=sendCycle(new_fd,(char*)&t,4+t.dataLen);
	if(-1==ret)
	{
		return -1;
	}
	int fd=open(FILENAME,O_RDONLY);
	//发送文件大小给客户端
	struct stat buf;
	fstat(fd,&buf);
	t.dataLen=sizeof(buf.st_size);
	memcpy(t.buf,&buf.st_size,sizeof(buf.st_size));
	ret=sendCycle(new_fd,(char*)&t,4+t.dataLen);
	if(-1==ret)
	{
		return -1;
	}
	//发送文件内容给客户端
	ret=sendfile(new_fd,fd,NULL,buf.st_size);
	if(-1==ret)
	{
		return -1;
	}
	printf("ret=%d\n",ret);
	t.dataLen=0;
	sendCycle(new_fd,(char*)&t,4);//发送文件发送结束标志
	return 0;
}

