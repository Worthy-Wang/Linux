#include <func.h>

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
	fd_set rdset;//定义一个集合
	char buf[128];
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(socketFd,&rdset);
		ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(socketFd,&rdset))//判断socketFd是否就绪，如果就绪就读取内容并打印
		{
			bzero(buf,sizeof(buf));
			ret=recv(socketFd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0==ret)
			{
				printf("byebye\n");
				break;
			}
			printf("%s\n",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&rdset))//判断标准输入是否可读，读取标准输入并发送给对端
		{
			memset(buf,0,sizeof(buf));
			ret=read(STDIN_FILENO,buf,sizeof(buf));
			if(0==ret)
			{
				printf("byebye\n");
				break;
			}
			ret=send(socketFd,buf,strlen(buf)-1,0);
			printf("send count %d\n",ret);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(socketFd);
}
