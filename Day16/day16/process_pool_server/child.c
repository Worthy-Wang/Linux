#include "function.h"
//创建子进程并初始化数据结构
int makeChild(Process_Data *pChild,int childNum)
{
	int i;
	pid_t pid;
	int fds[2];
	int ret;
	for(i=0;i<childNum;i++)
	{
		ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		ERROR_CHECK(ret,-1,"socketpair");
		pid=fork();
		if(0==pid)
		{
			close(fds[1]);
			childHandle(fds[0]);
		}
		close(fds[0]);
		pChild[i].pid=pid;
		pChild[i].fd=fds[1];
		pChild[i].busy=0;
	}
	return 0;
}

int childHandle(int fd)
{
	int newFd;
    int exitFlag;
	while(1)
	{
		recvFd(fd,&newFd,&exitFlag);//接收到任务
        if(exitFlag)
        {
		    tranFile(newFd);//给客户端发送文件
		    close(newFd);
        }else{
            exit(0);
        }
		write(fd,&newFd,1);//通知父进程我非忙碌了
	}
}
