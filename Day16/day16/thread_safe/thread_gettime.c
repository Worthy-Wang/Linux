#include <func.h>
void* threadFunc(void* p)
{
    time_t now;
    time(&now);
    char ptime[100];
    ctime_r(&now,ptime);
    printf("child %s,%p\n",ptime,ptime);
    sleep(3);
    printf("child %s\n",ptime);
    return NULL;
}
int main()
{
    pthread_t thid;
    pthread_create(&thid,NULL,threadFunc,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char ptime[100];
    ctime_r(&now,ptime);
    printf("%s,%p\n",ptime,ptime);
    pthread_join(thid,NULL);
    return 0;
}

