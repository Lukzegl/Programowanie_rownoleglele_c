#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main() {
    double a[WYMIAR][WYMIAR];
    
    // Inicjalizacja
    for(int i=0; i<WYMIAR; i++) 
    {
        for(int j=0; j<WYMIAR; j++) 
        {
            a[i][j] = 1.02*i + 1.01*j;
        }
    }
    // Suma sekwencyjna
    double suma = 0.0;
    for(int i=0; i<WYMIAR; i++) 
    {
        for(int j=0; j<WYMIAR; j++) 
        {
            suma += a[i][j];
        }
    }
    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n\n", suma);
    
    
    printf("DEKOMPOZYCJA 2D ZZ\n");
    
    //ROWNOLLEGLOSC
    omp_set_nested(1);
    
    double suma_parallel = 0.0;
    
    //3 po wierszach
    #pragma omp parallel for default(none) shared(a) schedule(static,2) num_threads(3) reduction(+:suma_parallel)
    for(int i=0; i<WYMIAR; i++)
    {
        int id_w_zew = omp_get_thread_num();
        
        // Loksum
        double local_sum = 0.0;
        
        // 2WK
        #pragma omp parallel for default(none) shared(a,i,id_w_zew) schedule(static,2) num_threads(2) reduction(+:local_sum)
        for(int j=0; j<WYMIAR; j++) 
        {
            int id_w_wew = omp_get_thread_num();
            
            local_sum += a[i][j];

            //#pragma omp ordered
            printf("(%1d,%1d)-W_%1d.%1d ", i, j, id_w_zew, id_w_wew);
        }
        
       
        suma_parallel += local_sum;

        #pragma omp ordered
        printf("\n");
    }
    
    printf("\nSuma wyrazów tablicy równolegle: %lf\n", suma_parallel);
   
    return 0;
}