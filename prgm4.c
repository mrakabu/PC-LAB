#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int is_prime(int num) {
    if (num <= 1)
        return 0;

    if (num == 2)
        return 1;

    if (num % 2 == 0)
        return 0;

    int limit = (int)sqrt(num);

    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int main() {
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    int *primes_serial = (int *)calloc(n + 1, sizeof(int));
    int *primes_parallel = (int *)calloc(n + 1, sizeof(int));

    double start, end;

    start = omp_get_wtime();

    for (int i = 1; i <= n; i++) {
        primes_serial[i] = is_prime(i);
    }

    end = omp_get_wtime();

    double serial_time = end - start;

    start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int i = 1; i <= n; i++) {
        primes_parallel[i] = is_prime(i);
    }

    end = omp_get_wtime();

    double parallel_time = end - start;

    int mismatch = 0;

    for (int i = 1; i <= n; i++) {
        if (primes_serial[i] != primes_parallel[i]) {
            mismatch = 1;
            printf("Mismatch at number %d\n", i);
            break;
        }
    }

    if (!mismatch)
        printf("Serial and parallel results match.\n");
    else
        printf("Results differ!\n");

    printf("Primes from 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        if (primes_parallel[i])
            printf("%d ", i);
    }

    printf("\n");

    printf("Serial execution time: %f seconds\n", serial_time);
    printf("Parallel execution time: %f seconds\n", parallel_time);
    printf("Speedup: %f\n", serial_time / parallel_time);

    free(primes_serial);
    free(primes_parallel);

    return 0;

  //gcc -fopenmp prog4.c -o prog4 -lm
  // ./prgm4
}
