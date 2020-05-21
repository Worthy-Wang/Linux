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
	ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);//缓冲区的大小，一瞬间能够放入的客户端连接信息
	int new_fd;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen=sizeof(client);
	char buf[128]={0};
	fd_set rdset;//定义一个集合
	fd_set needMonitorSet;
	FD_ZERO(&needMonitorSet);
	FD_SET(STDIN_FILENO,&needMonitorSet);
	FD_SET(socketFd,&needMonitorSet);
	while(1)
	{
		memcpy(&rdset,&needMonitorSet,sizeof(fd_set));
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(socketFd,&rdset))
		{
			new_fd=accept(socketFd,(struct sockaddr*)&client,&addrlen);
			ERROR_CHECK(new_fd,-1,"accept");
			printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
			FD_SET(new_fd,&needMonitorSet);
		}
		if(FD_ISSET(new_fd,&rdset))//判断new_fd是否就绪，如果就绪就读取内容并打印
		{
			bzero(buf,sizeof(buf));
			ret=recv(new_fd,buf,sizeof(buf),0);//对端断开，recv得到零
			ERROR_CHECK(ret,-1,"recv");
			if(0==ret)
			{
				printf("byebye\n");
				FD_CLR(new_fd,&needMonitorSet);
				close(new_fd);
				continue;
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
			ret=send(new_fd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(socketFd);
	return 0;
}
