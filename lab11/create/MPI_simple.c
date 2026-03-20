#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

typedef struct {
    int id;
    double wartosc;
    char imie[30];
    int liczby[5];
}Struktura;

int main(int argc, char** argv) 
{
    int rank, size, prev, next;
    MPI_Status status;
    MPI_Datatype MPI_MojaStruktura;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    prev = (rank + size - 1) % size;
    next = (rank + 1) % size;
    
    int blocklengths[4] = {1, 1, 30, 5};
    MPI_Datatype types[4] = {MPI_INT, MPI_DOUBLE, MPI_CHAR, MPI_INT};
    MPI_Aint offsets[4];
    
    Struktura dane;
   
    MPI_Type_create_struct(4, blocklengths, offsets, types, &MPI_MojaStruktura);
    MPI_Type_commit(&MPI_MojaStruktura);
    
    if(rank == 0) 
    {
        dane.id = 0;
        dane.wartosc = 3.14;
        strcpy(dane.imie, "Jan");
        for(int i = 0; i < 5; i++) dane.liczby[i] = i;
        
        MPI_Send(&dane, 1, MPI_MojaStruktura, next, 0, MPI_COMM_WORLD);
    }
    
    //odbieranie
    if(rank > 0) 
    {
        MPI_Recv(&dane, 1, MPI_MojaStruktura, prev, 0, MPI_COMM_WORLD, &status);
    }
    
    printf("Proces %d odebrał: id=%d, imie=%s, wartosc=%.2f\n",  rank, dane.id, dane.imie, dane.wartosc);
    
    //modyfikacja
    dane.id = rank;
    dane.wartosc += 1.0;
    snprintf(dane.imie, 30, "Proces%d", rank);
    
    if(rank < size - 1)
    {
        MPI_Send(&dane, 1, MPI_MojaStruktura, next, 0, MPI_COMM_WORLD);
    }
    
    MPI_Type_free(&MPI_MojaStruktura);
    MPI_Finalize();
    return 0;
}
