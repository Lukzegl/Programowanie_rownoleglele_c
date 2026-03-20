#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/
//pisarz
pthread_cond_t wait_cond_pisarz = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//czytelnik
pthread_cond_t wait_cond_czytelnik = PTHREAD_COND_INITIALIZER;

int oczekujacy_pisarze = 0;

int my_read_lock_lock(cz_t* cz_p)
{
  pthread_mutex_lock(&mutex);

  if(oczekujacy_pisarze || cz_p->l_p>0)
  {
    pthread_cond_wait(&wait_cond_czytelnik, &mutex);  
  }

  pthread_cond_signal(&wait_cond_czytelnik);
  cz_p->l_c++;

  pthread_mutex_unlock(&mutex);
}


int my_read_lock_unlock(cz_t* cz_p)
{
  pthread_mutex_lock(&mutex);

  cz_p->l_c--;

  if(cz_p->l_c==0)
  {
    pthread_cond_signal(&wait_cond_pisarz);
  }

  pthread_mutex_unlock(&mutex);
}


int my_write_lock_lock(cz_t* cz_p)
{
  pthread_mutex_lock(&mutex);

  if(cz_p->l_p + cz_p->l_c > 0)
  {
    oczekujacy_pisarze++;
  }
  pthread_cond_wait(&wait_cond_pisarz, &mutex);
  oczekujacy_pisarze--;

  cz_p->l_p++;

  pthread_mutex_unlock(&mutex);
}


int my_write_lock_unlock(cz_t* cz_p)
{
 pthread_mutex_lock(&mutex); 

  cz_p->l_p--;
  pthread_cond_signal(&wait_cond_czytelnik);

  pthread_mutex_unlock(&mutex);
}

void inicjuj(cz_t* cz_p)
{

  cz_p->l_p = 0;
  cz_p->l_c = 0;  

}

void czytam(cz_t* cz_p)
{

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit

if(cz_p->l_p>1)
  {
    printf("Blad: wiecej niz jeden pisarz!\n");
    exit(0);
  }
  else if(cz_p->l_p==1 && cz_p->l_c>0)
  {
    printf("Blad: pisarz z czytelnikami!\n");
    exit(0);
  }
  else if(cz_p->l_p<0)
  {
    printf("Blad: ujemna liczba pisarzy!\n");
    exit(0);
  }
  else if(cz_p->l_c<0)
  {
    printf("Blad: ujemna liczba czytelnikow!\n");
    exit(0);
  }

// warunek:
/*
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    //exit(0);
  }
*/

    usleep(rand()%3000000);
}

void pisze(cz_t* cz_p)
{

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit

if(cz_p->l_p>1)
  {
    printf("Blad: wiecej niz jeden pisarz!\n");
    exit(0);
  }
  else if(cz_p->l_p==1 && cz_p->l_c>0)
  {
    printf("Blad: pisarz z czytelnikami!\n");
    exit(0);
  }
  else if(cz_p->l_p<0)
  {
    printf("Blad: ujemna liczba pisarzy!\n");
    exit(0);
  }
  else if(cz_p->l_c<0)
  {
    printf("Blad: ujemna liczba czytelnikow!\n");
    exit(0);
  }
/*
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    //exit(0);
  }
*/
    usleep(rand()%3000000);
}


