#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergesort_seq(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergesort_seq(arr, l, m);
        mergesort_seq(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void mergesort_parallel(int arr[], int l, int r, int depth) {
    if (l < r) {
        int m = l + (r - l) / 2;

        if (depth <= 0) {
            mergesort_seq(arr, l, m);
            mergesort_seq(arr, m + 1, r);
        } else {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergesort_parallel(arr, l, m, depth - 1);

                #pragma omp section
                mergesort_parallel(arr, m + 1, r, depth - 1);
            }
        }

        merge(arr, l, m, r);
    }
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr_seq = (int *)malloc(n * sizeof(int));
    int *arr_par = (int *)malloc(n * sizeof(int));

    srand(42);

    for (int i = 0; i < n; i++) {
        arr_seq[i] = rand() % 1000000;
        arr_par[i] = arr_seq[i];
    }

    printf("Generated %d random elements.\n", n);

    double start, end;

    start = omp_get_wtime();
    mergesort_seq(arr_seq, 0, n - 1);
    end = omp_get_wtime();

    double time_seq = end - start;

    printf("Sequential mergesort time: %f seconds\n", time_seq);

    start = omp_get_wtime();
    mergesort_parallel(arr_par, 0, n - 1, 4);
    end = omp_get_wtime();

    double time_par = end - start;

    printf("Parallel mergesort time: %f seconds\n", time_par);

    printf("Speedup: %f\n", time_seq / time_par);

    free(arr_seq);
    free(arr_par);

    return 0;
}

//gcc -fopenmp mergesort.c -o mergesort.exe
//mergesort.exe
