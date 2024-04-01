#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void process(double*, int, double*);

static double* process_c(double* X, int size, double* Y) {
    int start_index = 3;
    int end = size - 1;
    int i;
    int counter = 0;

    for (i = start_index; i <= end; i++) {
        // Break loop if out of bounds
        if (i - 3 < 0 || i + 3 >= size) {
            break;
        }
        else {
            Y[counter] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
            counter++;
        }
    }

    return Y;
}

void run_comparison(int vector_size) {
    double* X = malloc(vector_size * sizeof(double));
    if (X == NULL) {
        printf("Error: Memory allocation failed");
        return;
    }

    // Fill the vector with counting numbers
    for (int i = 0; i < vector_size; i++) {
        X[i] = i + 1;
    }

    int Y_size = vector_size - 6;
    double* Y_c = malloc(Y_size * sizeof(double));
    double* Y_asm = malloc(Y_size * sizeof(double));

    if (Y_c == NULL || Y_asm == NULL) {
        printf("Error: Memory allocation failed");
        free(X);
        free(Y_c);
        free(Y_asm);
        return;
    }

    double total_time_c = 0.0;
    double total_time_asm = 0.0;

    for (int i = 0; i < 30; i++) {
        clock_t start_c = clock();
        process_c(X, vector_size, Y_c);
        clock_t end_time_c = clock();
        double elapsed_c = (end_time_c - start_c) * 1000.0 / CLOCKS_PER_SEC;
        total_time_c += elapsed_c;

        clock_t start_asm = clock();
        process(X, vector_size, Y_asm);
        clock_t end_time_asm = clock();
        double elapsed_asm = (end_time_asm - start_asm) * 1000.0 / CLOCKS_PER_SEC;
        total_time_asm += elapsed_asm;
    }

    double avg_time_c = total_time_c / 30.0;
    double avg_time_asm = total_time_asm / 30.0;

    printf("Vector Size: %d\n", vector_size);
    printf("Average C Kernel Execution Time: %.5f ms\n", avg_time_c);
    printf("Average ASM Kernel Execution Time: %.5f ms\n\n", avg_time_asm);

    free(X);
    free(Y_c);
    free(Y_asm);
}

int main() {
    int sizes[] = { (int)pow(2, 20), (int)pow(2, 24), (int)pow(2, 30) };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        run_comparison(sizes[i]);
    }

    return 0;
}