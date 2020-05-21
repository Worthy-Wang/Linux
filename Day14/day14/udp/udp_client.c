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
	ret=sendto(socketFd,"helloworld",10,0,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"sendto");
	char buf[128]={0};//最大填写为65535
	ret=recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("udp client gets %s\n",buf);
	close(socketFd);
}
	

