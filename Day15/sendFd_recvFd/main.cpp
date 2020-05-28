#include <Unixfunc.h>
#include <iostream>
using namespace std;
int sendFd(int sfd, int fd)
{
	struct msghdr msg;
	memset(&msg, 0, sizeof(msg));
	struct iovec iov[2];
	char buf1[10] = "hello";
	char buf2[10] = "world";
	iov[0].iov_base = buf1;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf2;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	struct cmsghdr *cmsg;
	int len = CMSG_LEN(sizeof(int));
	cmsg = (struct cmsghdr *)calloc(1, len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg) = fd;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = sendmsg(sfd, &msg, 0);
	ERROR_CHECK(ret, -1, "sendmsg");
	return 0;
}

int recvFd(int sfd, int *fd)
{
	struct msghdr msg;
	memset(&msg, 0, sizeof(msg));
	struct iovec iov[2];
	char buf1[10];
	char buf2[10];
	iov[0].iov_base = buf1;
	iov[0].iov_len = 5;
	iov[1].iov_base = buf2;
	iov[1].iov_len = 5;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	struct cmsghdr *cmsg;
	int len = CMSG_LEN(sizeof(int));
	cmsg = (struct cmsghdr *)calloc(1, len);
	cmsg->cmsg_len = len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control = cmsg;
	msg.msg_controllen = len;
	int ret;
	ret = recvmsg(sfd, &msg, 0);
	ERROR_CHECK(ret, -1, "sendmsg");
	*fd = *(int *)CMSG_DATA(cmsg);
	return 0;
}

/*
前言

亲属进程之间传递文件描述符：
文件描述符间的传递，并不是简单的值之间的传递，而是要将文件描述符引用的文件一并传递，并且再将文件的引用计数+1，看似简单，实际关联了内核，较为困难
同时需要注意，进程间传递文件描述符相当于是dup, 需要将文件的引用计数+1 

父进程打开一个file文件句柄，写入helloWorld, 并将文件句柄传送给子进程, 子进程读出helloWorld
*/

int main()
{
	int fds[2];
	int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);//全双工管道
	ERROR_CHECK(ret, -1, "socketpair");
	cout << "fds[0] = " << fds[0]  << " , fsd[1] = " << fds[1] << endl;
	if (fork() == 0)
	{
		close(fds[1]);
		int fd;
		recvFd(fds[0], &fd);
		cout << "child process get fd:" << fd << endl;
		char buf[100] = {0};
		read(fd, buf, sizeof(buf));
		cout << "child process read:" << buf << endl;
		close(fds[0]);
		exit(0);
	}
	else
	{
		close(fds[0]);
		int fd = open("file", O_RDWR | O_CREAT, 0755);
		ERROR_CHECK(fd, -1, "open");
		cout << "father process get fd:" << fd << endl;
		write(fd, "helloWorld", 10);
		lseek(fd, 0, SEEK_SET);//注意此时文件指针已经读取到了末尾，所以要进行指针偏移，父子进程在文件指针的操作上同步
		sendFd(fds[1], fd);
		cout << "father process has send fd" << endl;
		close(fds[0]);
		wait(NULL);
		exit(0);
	}

	return 0;
}
