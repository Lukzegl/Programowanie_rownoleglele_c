#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct 
{
    double a;
    double b;
    double wynik;

}Data;

void *funkcja_watku(void *arg)
{
    Data D = *(Data*)arg;
   
    D.wynik = (D.a + D .b)/2.0;
    printf("W:%f\n",D.wynik);
    
    return NULL;
}

#define LW 4

int main()
{
    pthread_t tid[LW];
    double a = 0.0;
    double b = 100;
    Data tabd[LW];

    double count = (b - a)/LW;

    for(int i=0;i<LW;i++)
    {
        tabd[i].a = a + i*count;
        tabd[i].b = a + (i+1)*count;
        pthread_create(&tid[i],NULL,funkcja_watku,&tabd[i]);
    }

    double suma = 0.0;
    for(int i=0;i<LW;i++)
    {
        pthread_join(tid[i],NULL);
        suma = suma + tabd[i].wynik;
    }

    printf("Suna srodkow przedzialow = %f\n",suma);

    return 0;
}