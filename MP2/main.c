#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern double process(double*, int, double*);

static double* process_c(double* X, int size, double* Y) {
    int start_index = 3;
    int end = size - 1;
    int i;
    int counter = 0;

    for (i = start_index; i <= end; i++) {
        // if greater or less than array break loop
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

int main() {
    int size = 0;
    char input[500];

    // Get input
    printf("Enter comma-separated double values: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline character
    input[strcspn(input, "\n")] = '\0';

    // Count the number of commas to determine the number of elements
    int count = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ',') {
            count++;
        }
    }

    // Parse the input string and store values in the array
    double* X = malloc(count * sizeof(double));
    if (X == NULL) {
        printf("Error: Memory allocation failed");
        return 1;
    }
    char* token = NULL;
    char* context = NULL; // For strtok_s
    token = strtok_s(input, ",", &context);
    while (token != NULL && size < count) {
        X[size++] = atof(token);
        token = strtok_s(NULL, ",", &context);
    }
    if (size < 7) {
        printf("Array must be of length 7 or greater");
        return 0;
    }

    // ---------
    // C PROGRAM
    // ---------

    printf("Answer (C kernel): ");

    double* Y_c = malloc(size * sizeof(double));
    if (Y_c == NULL) {
        printf("Error: Memory allocation failed");
        free(X);
        return 1;
    }

    clock_t start_c = clock();
    process_c(X, size, Y_c);
    clock_t end_time_c = clock();
    double elapsed_c = (end_time_c - start_c) * 1000.0 / CLOCKS_PER_SEC;

    // Print results of C program
    for (int i = 0; i < size - 6; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.lf", Y_c[i]);
    }
    printf("\nC kernel execution time: %.5f ms\n\n", elapsed_c);

    // -----------
    // ASM PROGRAM
    // -----------

    printf("Answer (ASM kernel): ");

    double* Y_asm = malloc(size * sizeof(double));
    if (Y_asm == NULL) {
        printf("Error: Memory allocation failed");
        free(X);
        free(Y_c);
        return 1;
    }

    clock_t start = clock();
    process(X, size, Y_asm);
    clock_t end_time = clock();
    double elapsed = (end_time - start) * 1000.0 / CLOCKS_PER_SEC;

    // Print results of ASM program
    for (int i = 0; i < size - 6; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.lf", Y_asm[i]);
    }
    printf("\nASM kernel execution time: %.5f ms\n", elapsed);

    // Free memory allocs
    free(X);
    free(Y_c);
    free(Y_asm);

    return 0;
}