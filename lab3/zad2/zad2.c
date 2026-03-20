#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define LW 5

void *funkcja_watku(void *arg)
{
    int ID = *((int*)arg);

    printf("Self: %lu\n ID = %d\n\n",pthread_self(),ID);

    //to jest ciekawe 
    //printf("Self: %lu\n",pthread_self());
    //printf("ID = %d\n\n",ID);

return NULL;
}

int main()
{
pthread_t tid[LW];
int ID[LW];

for(int i =0;i<LW;i++)
{
    ID[i] = i;
    pthread_create(&tid[i],NULL,funkcja_watku,&ID[i]);
}

for(int i=0;i<LW;i++)
{
    pthread_join(tid[i],NULL);
}

    return 0;
}