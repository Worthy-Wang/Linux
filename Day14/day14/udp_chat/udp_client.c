#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int socketFd;
	socketFd=socket(AF_INET,SOCK_DGRAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);//点分十进制转为32位的网络字节序
	int ret;
	ret=sendto(socketFd,"h",1,0,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"sendto");
	char buf[128]={0};//最大填写为65535
	fd_set rdset;//定义一个集合
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(socketFd,&rdset);
		ret=select(socketFd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(socketFd,&rdset))//判断socketFd是否就绪，如果就绪就读取内容并打印
		{
			bzero(buf,sizeof(buf));
			bzero(buf,sizeof(buf));
			ret=recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
			ERROR_CHECK(ret,-1,"recvfrom");
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
			ret=sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,sizeof(ser));
			ERROR_CHECK(ret,-1,"sendto");
		}
	}
	close(socketFd);
}
	

