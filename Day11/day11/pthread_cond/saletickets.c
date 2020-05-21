#include <func.h>

typedef struct{
	int tickets;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}Train;
void* saleWindows1(void* p)
{
	Train *pSale=(Train*)p;
	int count=0;
	while(1)
	{
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0)
		{
			printf("I am saleWindows1,the tickets is %d\n",pSale->tickets);
			pSale->tickets--;
			if(0==pSale->tickets)
			{
				pthread_cond_signal(&pSale->cond);
			}
			count++;
			printf("sale finish,I am saleWindows1,the tickets is %d\n",pSale->tickets);
			pthread_mutex_unlock(&pSale->mutex);
		}else{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am windows1 sale %d\n",count);
			break;
		}
		sleep(1);
	}
	return NULL;
}
void* saleWindows2(void* p)
{
	Train *pSale=(Train*)p;
	int count=0;
	while(1)
	{
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0)
		{
			printf("I am saleWindows2,the tickets is %d\n",pSale->tickets);
			pSale->tickets--;
			if(0==pSale->tickets)
			{
				pthread_cond_signal(&pSale->cond);
			}
			count++;
			printf("sale finish,I am saleWindows2,the tickets is %d\n",pSale->tickets);
			pthread_mutex_unlock(&pSale->mutex);
		}else{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am windows2 sale %d\n",count);
			break;
		}
		sleep(1);
	}
	return NULL;
}
void* setTickets(void* p)
{
	Train *pSale=(Train*)p;
	pthread_mutex_lock(&pSale->mutex);
	if(pSale->tickets>0)
	{
		pthread_cond_wait(&pSale->cond,&pSale->mutex);
	}
	pSale->tickets=20;
	pthread_mutex_unlock(&pSale->mutex);
	return NULL;
}
typedef void* (*threadFunc)(void*);
#define N 3
int main()
{
	Train t;
	pthread_t pthId[N];
	int i;
	t.tickets=20;
	threadFunc pthreadFunc[N]={saleWindows1,saleWindows2,setTickets};
	pthread_mutex_init(&t.mutex,NULL);
	pthread_cond_init(&t.cond,NULL);
	for(i=0;i<N;i++)
	{
		pthread_create(pthId+i,NULL,pthreadFunc[i],&t);
	}
	for(i=0;i<N;i++)
	{
		pthread_join(pthId[i],NULL);
	}
	printf("sale over\n");
}
