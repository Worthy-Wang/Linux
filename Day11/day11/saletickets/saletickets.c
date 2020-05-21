#include <func.h>

typedef struct{
	int tickets;
	pthread_mutex_t mutex;
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
			//printf("I am saleWindows1,the tickets is %d\n",pSale->tickets);
			pSale->tickets--;
			count++;
			//printf("sale finish,I am saleWindows1,the tickets is %d\n",pSale->tickets);
			pthread_mutex_unlock(&pSale->mutex);
		}else{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am windows1 sale %d\n",count);
			break;
		}
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
			//printf("I am saleWindows2,the tickets is %d\n",pSale->tickets);
			pSale->tickets--;
			count++;
			//printf("sale finish,I am saleWindows2,the tickets is %d\n",pSale->tickets);
			pthread_mutex_unlock(&pSale->mutex);
		}else{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am windows2 sale %d\n",count);
			break;
			break;
		}
	}
	return NULL;
}

typedef void* (*threadFunc)(void*);
int main()
{
	Train t;
	pthread_t pthId[2];
	int i;
	t.tickets=20000000;
	threadFunc pthreadFunc[2]={saleWindows1,saleWindows2};
	pthread_mutex_init(&t.mutex,NULL);
	for(i=0;i<2;i++)
	{
		pthread_create(pthId+i,NULL,pthreadFunc[i],&t);
	}
	for(i=0;i<2;i++)
	{
		pthread_join(pthId[i],NULL);
	}
	printf("sale over\n");
}
