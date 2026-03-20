#!/bin/bash


echo

echo "1. Program OpenMP - całka (calka_omp)"
echo "---------------------------"
for threads in 1 2 4 8; do
    echo "Liczba wątków: $threads"
    export OMP_NUM_THREADS=$threads
    time ./calka_omp
    echo
done

echo
echo "2. Program MPI - mnożenie macierz-wektor (mat_vec_row_MPI_modified)"
echo "-----------------------------------------------------------------"
for processes in 1 2 4 8; do
    echo "Liczba procesów: $processes"
    mpiexec -np $processes ./mat_vec_row_MPI_modified 2>/dev/null | tail -10
    echo
done

echo
echo "3. Program MPI - obliczanie π (MPI_pi)"
echo "-------------------------------------"

mpiexec -np 4 ./MPI_pi