/* 
  License: GNU GPLv2
  Authors: Julián Perelli
  Organization: Sistemas Operativos Avanzados 2015 - UTN FRLP
  Compile with: gcc primos_omp.c -fopenmp -o primos_omp
  Run with (using default thread_num):      ./primos_omp 10000
  Run alt  (overriding default thread_num): OMP_NUM_THREADS=4 ./primos_omp 10000
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <omp.h>

int contar_primos(int a, int b) {
  /* Esta es una forma trivial (naive) de contar primos */
  int i;
  int j;
  int total;
  int primo;

  total = 0;
  #pragma omp parallel for private(i, j, primo) reduction(+:total) 
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

  // Leer numero maximo, hasta el cual contar primos
  int max;
  if ( argc < 2 ) {
      fprintf( stderr, "Uso: %s parametro_numerico\n", argv[0] );
      return 1;
  }
  max = strtoull( argv[1], NULL, 10 );
  if ( errno ) {
      fprintf( stderr, "%s: parametro %s: %s\n", argv[0], argv[1], strerror(errno) );
      return 2;
  }

  printf("Contando primos hasta el %i\n", max);
  
  // Llamar al contador de primos
  printf("Hay %i primos hasta el %i\n", contar_primos(0, max), max);
}