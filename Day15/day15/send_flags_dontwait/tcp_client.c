#include <func.h>
#define N 1048576
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
	int i;
	int total=0;
	for(i=0;i<N;i++)
	{
		ret=send(socketFd,"hello",5,MSG_DONTWAIT);
		if(-1==ret)
		{
			printf("errno=%d\n",errno);
			printf("total=%d\n",total);
			return -1;
		}
		total+=ret;
	}
	close(socketFd);
}
