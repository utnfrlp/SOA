/*
  License: GNU GPLv2
  Authors: Matías Caputti
  Organization: Sistemas Operativos Avanzados 2017 - UTN FRLP
  Compile with: mpicc ejemplo_MPI.c -o ejemplo_MPI
  Run with: mpirun -n 4 ./ejemplo_MPI
*/

#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
  int actual, total;

  /* inicializa MPI, crea MPI_COMM_WORLD */
  MPI_Init (&argc, &argv);

  /* toma el id del proceso actual */
  MPI_Comm_rank (MPI_COMM_WORLD, &actual);

  /* toma la cantidad total de procesos */
  MPI_Comm_size (MPI_COMM_WORLD, &total);

  printf( "HOLA MUNDO: proceso %d de %d\n", actual, total );

  /* finaliza MPI */
  MPI_Finalize();

  return 0;
}
