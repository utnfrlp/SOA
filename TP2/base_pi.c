#include <stdio.h>
#include <math.h>
 
int main(int argc, char *argv[]) 
{ 
  // cantidad de rectangulos a calcular
  int n = 1000;

	// calculo de PI
	double h = 1.0 / (double) n;
	double sum = 0.0;

	for (int i = 1; i <= n; i++) {
		double x = h * ((double)i - 0.5);
		sum += (4.0 / (1.0 + x*x));
	}

	double pi = sum * h;

  printf("El valor aproximado de PI es: %.16f", pi);
	return 0;
}
