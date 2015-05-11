# Sistemas Operativos Avanzados

Código de los ejercicios de la parte práctica

## Contenido

### TP1

* desync.c: Muestra una desincronización en la ejecución con hilos.
* peterson_a.c: Código A para analizar el algoritmo de Peterson.
* peterson_b.c: Código B para ver fallas en el algoritmo de Peterson en la computación multiprocesamiento actual y el uso de `__sync_synchronize()`.

### TP2

* primos.c: Cuenta la cantidad de números primos desde cero hasta un número pasado como argumento por la línea de comandos al ejecutar.
* primos_omp.c: Lo mismo que primos.c pero paralelizado utilizando OpenMP.
* primos_mpi.c: Lo mismo que primos.c pero paralelizado utilizando MPI.

## Licencia

Todo el código en este repositorio tiene licencia GPLv3