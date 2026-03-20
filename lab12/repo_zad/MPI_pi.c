#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char *argv[]) 
{
    // program obliczania przybliżenia PI za pomocą wzoru Leibniza
    // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
    //
    int rank, size;
    int max_liczba_wyrazow;
    double suma_plus = 0.0;
    double suma_minus = 0.0;
    //
    double global_suma_plus;
    double global_suma_minus;
    double pi_approx;
    int i;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) 
    {
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }
    
   
    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
   //BLOKIII
    int local_n = max_liczba_wyrazow / size;
    int remainder = max_liczba_wyrazow % size;
    int start, end;
    
    if (rank < remainder) 
    {
        start = rank * (local_n + 1);
        end = start + local_n + 1;
    } 
    else 
    {
        start = rank * local_n + remainder;
        end = start + local_n;
    }
    
    
    for (i = start; i < end; i++) 
    {
        int j = 1 + 4 * i;
        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);
    }
    
    //DO PROCESU 0
    MPI_Reduce(&suma_plus, &global_suma_plus, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&suma_minus, &global_suma_minus, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        pi_approx = 4 * (global_suma_plus - global_suma_minus);
        printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }
    
    MPI_Finalize();
    return 0;
}