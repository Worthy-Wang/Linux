#include <func.h>
typedef struct msgbuf{
	long mtype;
	char mtext[64];
}MSG;
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int msgId;
	msgId=msgget(1000,IPC_CREAT|0600);
	ERROR_CHECK(msgId,-1,"msgget");
	MSG sndmsg;
	sndmsg.mtype=atoi(argv[1]);
	strcpy(sndmsg.mtext,argv[2]);
	int ret;
	ret=msgsnd(msgId,&sndmsg,strlen(sndmsg.mtext),0);
	ERROR_CHECK(ret,-1,"msgsnd");
	return 0;
}
