/* 
  License: GNU GPLv2
  Authors: Julian Perelli, Martin Zugnoni
    with ideas from http://people.sc.fsu.edu/~jburkardt/c_src/mpi/mpi.html
  Organization: Sistemas Operativos Avanzados 2015 - UTN FRLP
  Compile with: mpicc primos_mpi.c -o primos_mpi
  Run with: mpirun -n 4 ./primos_mpi 10000
*/

#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int contar_primos(int a, int b) {
  /* Esta es una forma trivial (naive) de contar primos */
  int i, j, total, primo;

  total = 0;
  for ( i = a; i < b; i++ ) {
    primo = 1;
    for ( j = 2; j < i; j++ ) {
      if ( ( i % j ) == 0 ) {
        primo = 0;
        break;
      }
    }
    total = total + primo;
  }
  return total;
}

int main(int argc, char *argv[]) {
  
  int max, id, ierr, p, primes, primes_part, a, b, i, j, total, primo, from, to;
  
  // Leer numero maximo, hasta el cual contar primos
  if ( argc < 2 ) {
      fprintf( stderr, "Uso: %s parametro_numerico\n", argv[0] );
      return 1;
  }
  errno = 0;
  max = strtoull( argv[1], NULL, 10 );
  if ( errno ) {
      fprintf( stderr, "%s: parametro %s: %s\n", argv[0], argv[1], strerror(errno) );
      return 2;
  }
    
  // Initialize MPI.
  ierr = MPI_Init ( &argc, &argv );
  
  // Get the number of processes.
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
  
  // Determine this processes's rank.
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );

  if ( id == 0 ) {
    printf("Contando primos hasta el %i\n", max);
  }
  
  from = id*(max / p);
  to   = (id+1)*((max / p));
  primes_part = contar_primos( from , to );
  printf("Proceso %i llama a contar_primos con %i, %i = %i\n", id, from, to, primes_part );

  ierr = MPI_Reduce(&primes_part, &primes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  // End MPI.
  ierr = MPI_Finalize();
  
  if ( id == 0 ) {
    
    int resto = max % p;
    if ( resto != 0 ) {
      from = p*((max / p));
      to   = from + resto;
      int restantes = contar_primos(from, to);
      printf("Master calculando %i restantes de %i a %i. Hubo %i en el resto\n", resto, from, to, restantes);
      primes = primes + restantes;
    }

    printf("\nHay %i primos hasta el %i\n", primes, max);
  }

  return 0;
}
