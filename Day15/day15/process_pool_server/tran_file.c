#include "function.h"

int tranFile(int newFd)
{
	Train_t train;
	//发送文件名
	train.dataLen=strlen(FILENAME);
	strcpy(train.buf,FILENAME);
	send(newFd,&train,4+train.dataLen,0);
	int fd=open(FILENAME,O_RDONLY);
	ERROR_CHECK(fd,-1,"open");
	//发文件内容
	while((train.dataLen=read(fd,train.buf,sizeof(train.buf))))
	{
		send(newFd,&train,4+train.dataLen,0);
	}
	//发送结束标志
	send(newFd,&train,4,0);
	return 0;
}
