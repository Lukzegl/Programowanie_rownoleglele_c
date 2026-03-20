#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

struct struktura_t { 
  int l_wkf;
  pthread_mutex_t *tab_kuf; 
  int l_kr;
  pthread_mutex_t *tab_kran;  
};
struct struktura_t pub_wsk;


int liczba_kufli;
pthread_mutex_t mutex_kufle;

void * watek_klient (void * arg);

int main( void )
{
  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;

  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  pub_wsk.l_wkf = l_kf;
  liczba_kufli = l_kl;


  printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  pub_wsk.l_kr = l_kr;

  pthread_mutex_init(&mutex_kufle,NULL);

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;

  pub_wsk.tab_kuf = (pthread_mutex_t *) malloc(l_kf*sizeof(pthread_mutex_t));
  for(i=0;i<l_kf;i++) pthread_mutex_init(&pub_wsk.tab_kuf[i], NULL);

  pub_wsk.tab_kran = (pthread_mutex_t *) malloc(l_kr*sizeof(pthread_mutex_t));
  for(i=0;i<l_kr;i++) pthread_mutex_init(&pub_wsk.tab_kran[i], NULL);

  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }

printf("\nLiczba kufli na poczatku: %d\n", l_kf);
  printf("Liczba kufli na koncu: %d\n", liczba_kufli);

  printf("\nZamykamy pub!\n");

  

}


void * watek_klient (void * arg_wsk){
  int moj_id = * ((int *)arg_wsk);
  int i, i_wypite, kran, kufel;
  long int wykonana_praca = 0;
  int success;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  printf("\nKlient %d, wchodze do pubu\n", moj_id); 
    
  for(i_wypite=0; i_wypite<ile_musze_wypic; i_wypite++)
  {
    //TRYLOCK
    success = 0;
    do {
      if (pthread_mutex_trylock(&mutex_kufle) == 0) 
      {
        //if (liczba_kufli > 0) 
        {
          liczba_kufli--;
          success = 1;
          kufel = liczba_kufli;
        }
        pthread_mutex_unlock(&mutex_kufle);
      }
      if (!success) 
      {
        wykonana_praca++; 
      }
    } while (!success);

    printf("\nKlient %d, wybralem kufel %d\n", moj_id, kufel); 

    // WYBIERANIE KRANU Z AKTYWNYM CZEKANIEM
    success = 0;
    do {
      kran = rand() % pub_wsk.l_kr; // Losowy kran
      if (pthread_mutex_trylock(&pub_wsk.tab_kran[kran]) == 0) 
      {
        success = 1;
      } 
      else 
      {
        wykonana_praca++; //WORK
      }
    } while (!success);
    
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, kran); 
    usleep(100);

    pthread_mutex_unlock(&pub_wsk.tab_kran[kran]);

    //KRAN1
    printf("\nKlient %d, pije piwo %d \n", moj_id,kran); 

    usleep(100);

    // ZWALNIANIE KRANU
    

    // ZWROT KUFLA
    pthread_mutex_lock(&mutex_kufle);
    liczba_kufli++;
    pthread_mutex_unlock(&mutex_kufle);

    printf("\nKlient %d, odkladam kufel %d\n", moj_id, kufel); 
  }

  printf("\nKlient %d, wychodze z pubu; wykonana praca %ld\n", moj_id, wykonana_praca); 
    
  return(NULL);
}