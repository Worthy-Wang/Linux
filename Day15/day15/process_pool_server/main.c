#include "function.h"

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,4);
	int childNum=atoi(argv[3]);
	Process_Data *pChild=(Process_Data*)calloc(childNum,sizeof(Process_Data));
	makeChild(pChild,childNum);
	int socketFd;
	tcpInit(&socketFd,argv[1],argv[2]);
	int epfd;
	epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(childNum+1,sizeof(struct epoll_event));
	event.events=EPOLLIN;
	event.data.fd=socketFd;
	int ret;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	int i;
	for(i=0;i<childNum;i++)
	{
		event.data.fd=pChild[i].fd;
		ret=epoll_ctl(epfd,EPOLL_CTL_ADD,pChild[i].fd,&event);
		ERROR_CHECK(ret,-1,"epoll_ctl");
	}
	int readyFdNum;
	int newFd;
	int j;
#ifdef DEBUG
	printf("epfd=%d,socketFd=%d\n",epfd,socketFd);
#endif
	while(1)
	{
		readyFdNum=epoll_wait(epfd,evs,childNum+1,-1);
		for(i=0;i<readyFdNum;i++)
		{
			if(evs[i].events==EPOLLIN && evs[i].data.fd==socketFd)
			{
				newFd=accept(socketFd,NULL,NULL);
				for(j=0;j<childNum;j++)
				{
					if(!pChild[j].busy)//找到非忙碌的子进程，把任务给它
					{
						sendFd(pChild[j].fd,newFd);
						pChild[j].busy=1;
						printf("%d child is busy\n",pChild[j].pid);
						break;
					}
				}
				close(newFd);
			}
			for(j=0;j<childNum;j++)
			{
				if(evs[i].data.fd==pChild[j].fd)
				{
					read(pChild[j].fd,&ret,1);
					pChild[j].busy=0;
					printf("%d child is not busy\n",pChild[j].pid);
				}
			}
		}
	}
}
