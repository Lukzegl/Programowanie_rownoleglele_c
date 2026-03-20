#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>


void* funkcja_watku(void *arg)
{
    int ID = *((int*)arg);

    //info
    pthread_attr_t atrybuty;
    pthread_getattr_np(pthread_self(), &atrybuty);

    

   size_t size;
    void *AD;
    pthread_attr_getstack(&atrybuty, &AD, &size);
    printf("Wątek %d: Rozmiar stosu = %zu \n", ID, size);
    int DUZA_TAB[100000000];

    //sprawdzanie stosu
    int d1;
    pthread_attr_getdetachstate(&atrybuty,&d1);
    
    if(d1 == PTHREAD_CREATE_JOINABLE)
    {
        printf("Wątek %d: Stan odlaczenia JOINABLE\n",ID);
    }
    else
    {
        printf("Wątek %d: Stan odlaczenia DETACHED\n",ID);
    }

}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    size_t rozmiar_stosu;
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &rozmiar_stosu);
    printf("Domyślny rozmiar stosu: %zu\n", rozmiar_stosu);
    //zmiana
    pthread_attr_setstacksize(&attr,512 * 1024 * 1024);
    int tab[1];
    tab[0] = 123;
    pthread_create(&tid,&attr,funkcja_watku,&tab[0]);
    pthread_join(tid,NULL);

}