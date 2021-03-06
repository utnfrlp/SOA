int main()
{
    int size;
    size = 500;
    long int i, j, k;
    double a[size][size];
    double b[size][size];
    double c[size][size];


    // Initialize buffers.
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            a[i][j] = (float)i + j;
            b[i][j] = (float)i - j;
            c[i][j] = 0.0f;
        }
    }

    // Compute matrix multiplication.
    // C <- C + A x B
    #pragma omp parallel for shared(a,b,c)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return 0;
}
