#include <Unixfunc.h>
typedef struct msgbuf{
	long mtype;
	char mtext[64];
}MSG;
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int msgId;
	msgId=msgget(1000,IPC_CREAT|0600);
	ERROR_CHECK(msgId,-1,"msgget");
	MSG rcvmsg;
	int ret;
	ret=msgrcv(msgId,&rcvmsg,sizeof(rcvmsg.mtext),atoi(argv[1]),0);
	ERROR_CHECK(ret,-1,"msgrcv");
	printf("get msg=%s,type=%ld\n",rcvmsg.mtext,rcvmsg.mtype);
	return 0;
}
