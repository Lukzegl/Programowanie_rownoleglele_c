#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main() 
{
    double a[WYMIAR][WYMIAR];
    
    for(int i=0; i<WYMIAR; i++)
    { 
        for(int j=0; j<WYMIAR; j++) 
        {
            a[i][j] = 1.02*i + 1.01*j;
        }
    }
   
    double suma = 0.0;
    for(int i=0; i<WYMIAR; i++) 
    {
        for(int j=0; j<WYMIAR; j++)
        {
            suma += a[i][j];
        }
    }
    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n\n", suma);
    
    printf(" DEKOMPOZYCJA  TABH\n");
    
    // SUM
    double sumy_wierszy[WYMIAR] = {0.0};
    
    for(int j=0; j<WYMIAR; j++) 
    {
        //W
        #pragma omp parallel for default(none) shared(a, sumy_wierszy, j) schedule(static, 1)
        for(int i=0; i<WYMIAR; i++) 
        {
            //#pragma omp ordered
            {
                sumy_wierszy[i] += a[i][j];
                printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
            }
        }
        printf("\n");
    }
    
  
    double suma_parallel = 0.0;
    for(int i=0; i<WYMIAR; i++) 
    {
        suma_parallel += sumy_wierszy[i];
    }
    
    printf("\nSuma wyrazów tablicy równolegle: %lf\n", suma_parallel);
    
    return 0;
}