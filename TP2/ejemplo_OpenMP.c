/*
  License: GNU GPLv2
  Authors: Matías Caputti
  Organization: Sistemas Operativos Avanzados 2017 - UTN FRLP
  Compile with: gcc ejemplo_OpenMP.c -fopenmp -o ejemplo_OpenMP
  Run with (using default thread_num): ./ejemplo_OpenMP
  Run alt  (overriding default thread_num): OMP_NUM_THREADS=4 ./ejemplo_OpenMP
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int actual, total;

  /* crea los distintos threads pasando a cada uno la copia de las variables */
  #pragma omp parallel private(total, actual)
  {
    /* toma el id del proceso actual */
    actual = omp_get_thread_num();

    /* toma la cantidad total de procesos */
    total = omp_get_num_threads();

    printf( "HOLA MUNDO: proceso %d de %d\n", actual, total );
  }

  return 0;
}
