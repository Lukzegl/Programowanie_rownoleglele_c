#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

double funkcja ( double x );

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;
//NEW
static double calka_global = 0.0;
//static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

//TAB na sumy
static double calka_czesc[100];

void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w)
{
  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  //globalne
  a_global = a;
  b_global = b;
  dx_global = dx_adjust;
  N_global = N;
  l_w_global = l_w;
  calka_global = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości

  //tablica - inicjalizacja
  for(int i = 0; i < l_w; i++) 
  {
    calka_czesc[i] = 0.0;
  }

  // tworzenie wątków
  pthread_t watki[l_w];
  int indeksy[l_w];

  for(int i = 0; i < l_w; i++) 
  {
    indeksy[i] = i;
    pthread_create(&watki[i], NULL, calka_fragment_petli_w, (void*)&indeksy[i]);
  }

  // oczekiwanie na zakończenie pracy wątków

  for(int i = 0; i < l_w; i++) 
  {
    pthread_join(watki[i], NULL);
  }

  for(int i = 0; i < l_w; i++) 
  {
    calka_global += calka_czesc[i];
  }


  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk)
{

  int my_id = *((int*)arg_wsk);

  //double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ? 

  double a = a_global;
  double dx = dx_global;
  
  

  //int N, l_w;      // wariant 1 - globalne

  int N = N_global;
  int l_w = l_w_global;

  // a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli

  // dekompozycja cykliczna
  int my_start = my_id;
  int my_end = N;
  int my_stride = l_w;

  // dekompozycja blokowa
  //int my_start = 0;
  //int my_end = 0;
  //int my_stride = 0;

  /*
  int block_size = (N + l_w - 1) / l_w; //zaokraglanie 
  int my_start = my_id * block_size;
  int my_end = (my_id + 1) * block_size;
  if(my_end > N) my_end = N;
  int my_stride = 1;
  */


  // something else ? (dekompozycja blokowo-cykliczna)

  printf("\nWątek %d: my_start %d, my_end %d, my_stride %d\n", my_id, my_start, my_end, my_stride);

  int i;
  double calka = 0.0;
  for(i=my_start; i<my_end; i+=my_stride)
  {

    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);

  }

   calka_czesc[my_id] = calka;

}

