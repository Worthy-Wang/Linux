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
	ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));//针对udp，bind后，端口已经激活
	ERROR_CHECK(ret,-1,"bind");
	char buf[128]={0};//最大填写为65535
	struct sockaddr_in client;
	int addrlen=sizeof(client);
	ret=recvfrom(socketFd,buf,5,0,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	printf("udp server gets %s\n",buf);
	bzero(buf,sizeof(buf));
	ret=recvfrom(socketFd,buf,5,0,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("udp server gets %s\n",buf);
	ret=sendto(socketFd,"world",5,0,(struct sockaddr*)&client,sizeof(client));
	ERROR_CHECK(ret,-1,"sendto");
	close(socketFd);
}
	

