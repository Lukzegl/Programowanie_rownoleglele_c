#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

typedef struct {
    int id;
    double wartosc;
    char imie[30];
    int liczby[5];
} MojaStruktura;

int main(int argc, char** argv) {
    int rank, size, prev, next;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    prev = (rank + size - 1) % size;
    next = (rank + 1) % size;
    
    MojaStruktura dane;
    char bufor[500];
    int position = 0;
    
    if(rank == 0) {
      
        dane.id = 0;
        dane.wartosc = 3.14;
        strcpy(dane.imie, "Jan");
        for(int i = 0; i < 5; i++) dane.liczby[i] = i;
        
        //pakowanie
        MPI_Pack(&dane.id, 1, MPI_INT, bufor, 500, &position, MPI_COMM_WORLD);
        MPI_Pack(&dane.wartosc, 1, MPI_DOUBLE, bufor, 500, &position, MPI_COMM_WORLD);
        MPI_Pack(dane.imie, 30, MPI_CHAR, bufor, 500, &position, MPI_COMM_WORLD);
        MPI_Pack(dane.liczby, 5, MPI_INT, bufor, 500, &position, MPI_COMM_WORLD);
        
        MPI_Send(bufor, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
    }
    
    //odbieranie 
    if(rank > 0) 
    {
        MPI_Recv(bufor, 500, MPI_PACKED, prev, 0, MPI_COMM_WORLD, &status);
        position = 0;
        
        MPI_Unpack(bufor, 500, &position, &dane.id, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(bufor, 500, &position, &dane.wartosc, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Unpack(bufor, 500, &position, dane.imie, 30, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(bufor, 500, &position, dane.liczby, 5, MPI_INT, MPI_COMM_WORLD);
    }
    
    
    printf("Proces %d odebrał: id=%d, imie=%s, wartosc=%.2f\n", 
           rank, dane.id, dane.imie, dane.wartosc);
    
    //modyfikacja 
    dane.id = rank;
    dane.wartosc += 1.0;
    snprintf(dane.imie, 30, "Proces%d", rank);
    
    //pakowanie2
    position = 0;
    MPI_Pack(&dane.id, 1, MPI_INT, bufor, 500, &position, MPI_COMM_WORLD);
    MPI_Pack(&dane.wartosc, 1, MPI_DOUBLE, bufor, 500, &position, MPI_COMM_WORLD);
    MPI_Pack(dane.imie, 30, MPI_CHAR, bufor, 500, &position, MPI_COMM_WORLD);
    MPI_Pack(dane.liczby, 5, MPI_INT, bufor, 500, &position, MPI_COMM_WORLD);
    
    if(rank < size - 1) {
        MPI_Send(bufor, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
