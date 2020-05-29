#include "func.h"
#define RECV_BLOCK 65536
int recvCycle(int,char*,int);
int main(int argc,char* argv[])
{
	args_check(argc,3);
	int socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in serAddr;
	memset(&serAddr,0,sizeof(serAddr));
	serAddr.sin_family=AF_INET;
	serAddr.sin_port=htons(atoi(argv[2]));//把端口转换为网络字节序
	serAddr.sin_addr.s_addr=inet_addr(argv[1]);//把IP地址转换为网络字节序
	int ret;
	ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
	ERROR_CHECK(ret,-1,"connect");
	char buf[1000]={0};
	int dataLen;
	//接收文件名
	recvCycle(socketFd,(char*)&dataLen,sizeof(int));
	recvCycle(socketFd,buf,dataLen);
	//接文件大小
	off_t downLoadSize,fileSize,beforeSize,fileSlice;
	recvCycle(socketFd,(char*)&dataLen,sizeof(int));
	recvCycle(socketFd,(char*)&fileSize,dataLen);
	printf("fileSize=%ld\n",fileSize);
	//接文件内容
	int fd;
	fd=open(buf,O_CREAT|O_RDWR,0666);
	ERROR_CHECK(fd,-1,"open");
	fileSlice=fileSize/RECV_BLOCK;
	beforeSize=downLoadSize=0;
	struct timeval start,end;
	gettimeofday(&start,NULL);
	//splice接那么多长度的文件内容
	int fds[2];
	pipe(fds);
	int recvCount;
	if(fileSize>RECV_BLOCK)
	{
		while(downLoadSize+RECV_BLOCK<fileSize)
		{
			recvCount=splice(socketFd,NULL,fds[1],NULL,RECV_BLOCK,SPLICE_F_MORE | SPLICE_F_MOVE);
			ERROR_CHECK(recvCount,-1,"splice1");
			recvCount=splice(fds[0],NULL,fd,NULL,recvCount,SPLICE_F_MORE | SPLICE_F_MOVE);
			ERROR_CHECK(recvCount,-1,"splice2");
			downLoadSize+=recvCount;
		}
	}
	recvCount=splice(socketFd,NULL,fds[1],NULL,fileSize-downLoadSize,SPLICE_F_MORE | SPLICE_F_MOVE);
	ERROR_CHECK(recvCount,-1,"splice1");
	recvCount=splice(fds[0],NULL,fd,NULL,recvCount,SPLICE_F_MORE | SPLICE_F_MOVE);
	ERROR_CHECK(recvCount,-1,"splice2");
	gettimeofday(&end,NULL);
	//接结束符
	ret=recvCycle(socketFd,(char*)&dataLen,sizeof(int));
	if(-1==ret)
	{
		printf("recv error\n");
	}
	printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
	close(fd);
	close(socketFd);
}
