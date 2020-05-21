#include "function.h"

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);//点分十进制转为32位的网络字节序
	int ret;
	ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success\n");
	int dataLen;
	char buf[1000]={0};
    //接收文件名
	recvCycle(socketFd,&dataLen,4);
	recvCycle(socketFd,buf,dataLen);
	int fd;
	fd=open(buf,O_CREAT|O_WRONLY,0666);
	ERROR_CHECK(fd,-1,"open");
    //接文件大小
    off_t fileSize=0,oldSize=0,downLoadSize=0,sliceSize;
    recvCycle(socketFd,&dataLen,4);
    recvCycle(socketFd,&fileSize,dataLen);
    //接文件内容
    sliceSize=fileSize/10000;
	while(1)
	{
		ret=recvCycle(socketFd,&dataLen,4);
        if(-1==ret)
        {
            printf("server is update\n");
            break;
        }
		if(dataLen>0)
		{
			ret=recvCycle(socketFd,buf,dataLen);
            if(-1==ret)
            {
                break;
            }
			write(fd,buf,dataLen);
            downLoadSize+=dataLen;
            if(downLoadSize-oldSize>sliceSize)
            {
                printf("\r%5.2f%%",(float)downLoadSize/fileSize*100);
                fflush(stdout);
                oldSize=downLoadSize;
            }
		}else{
            printf("\r100%%   \n");
			break;
		}
	}
	close(fd);
	close(socketFd);
	return 0;
}
