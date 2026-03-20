#include <pthread.h>

static pthread_mutex_t barrier_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  barrier_cond;

static int liczba_watkow;   
static int liczba_barier;    

void bariera_init(int n)
{
    pthread_mutex_lock(&barrier_mutex);
    liczba_watkow = n;
    liczba_barier = 0;
    pthread_mutex_unlock(&barrier_mutex);
}

void bariera(void)
{
    //L1
    pthread_mutex_lock(&barrier_mutex);

    liczba_barier++;

    if (liczba_barier == liczba_watkow) 
    {
        liczba_barier = 0;
        pthread_cond_broadcast(&barrier_cond);
    } 
    else 
    {
        pthread_cond_wait(&barrier_cond, &barrier_mutex);
    }

    //L1_zwolnij
    pthread_mutex_unlock(&barrier_mutex);
}
