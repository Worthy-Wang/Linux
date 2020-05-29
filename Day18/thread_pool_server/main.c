#include "factory.h"

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,5);
	Factory_t f;
	int threadNum=atoi(argv[3]);
	int capacity=atoi(argv[4]);
	factoryInit(&f,threadNum,capacity);
	factoryStart(&f);
	int socketFd;
	tcpInit(&socketFd,argv[1],argv[2]);
	int new_fd;
	pQue_t pq=&f.que;
	while(1)
	{
		new_fd=accept(socketFd,NULL,NULL);
		pNode_t pnew=(pNode_t)calloc(1,sizeof(Node_t));
		pnew->new_fd=new_fd;
		pthread_mutex_lock(&pq->mutex);
		queInsert(pq,pnew);
		pthread_mutex_unlock(&pq->mutex);
		pthread_cond_signal(&f.cond);
	}
}
