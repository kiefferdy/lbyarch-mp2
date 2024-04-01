#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
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

static bool compare_outputs(double* Y_c, double* Y_asm, int Y_size) {
    for (int i = 0; i < Y_size; i++) {
        if (Y_c[i] != Y_asm[i]) {
            return false;
        }
    }
    return true;
}

void run_comparison(double* X, int vector_size) {
    int Y_size = vector_size - 6;
    double* Y_c = (double*)malloc(Y_size * sizeof(double));
    double* Y_asm = (double*)malloc(Y_size * sizeof(double));

    if (Y_c == NULL || Y_asm == NULL) {
        printf("Error: Memory allocation failed for vector size %d\n", vector_size);
        free(Y_c);
        free(Y_asm);
        return;
    }

    process_c(X, vector_size, Y_c);
    process(X, vector_size, Y_asm);

    printf("-----Vector Size: %d-----\n", vector_size);

    // Print first and last values of C program output
    printf("Answer (C kernel): ");
    printf("First value: %.lf, Last value: %.lf\n", Y_c[0], Y_c[Y_size - 1]);

    // Print first and last values of ASM program output
    printf("Answer (ASM kernel): ");
    printf("First value: %.lf, Last value: %.lf\n", Y_asm[0], Y_asm[Y_size - 1]);

    // Check if C output and ASM output are exactly the same
    bool outputs_match = compare_outputs(Y_c, Y_asm, Y_size);
    if (outputs_match) {
        printf("Correctness Check: PASS\n");
        printf("C output and ASM output are exactly the same!\n");
    }
    else {
        printf("Correctness Check: FAIL\n");
        printf("C output and ASM output are different!\n");
    }

    printf("\n");

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

    printf("Runtime Comparison:\n");
    printf("Average C Kernel Execution Time: %.5f ms\n", avg_time_c);
    printf("Average ASM Kernel Execution Time: %.5f ms\n", avg_time_asm);

    double speed_ratio = (avg_time_c / avg_time_asm) * 100.0;
    printf("The assembly kernel is %.2f%% the speed of the C kernel\n\n", speed_ratio);

    free(Y_c);
    free(Y_asm);
}

int main() {
    int size = 0;
    char input[500];

    int sizes[] = { (int)pow(2, 20), (int)pow(2, 24), (int)pow(2, 30) };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int vector_size = sizes[i];
        double* X = (double*)malloc(vector_size * sizeof(double));
        if (X == NULL) {
            printf("Error: Memory allocation failed for vector size %d\n", vector_size);
            continue;
        }

        // Fill the vector with counting numbers
        for (int j = 0; j < vector_size; j++) {
            X[j] = j + 1;
        }

        run_comparison(X, vector_size);
        printf("\n\n");

        free(X);
    }

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
    double* X = (double*)malloc(count * sizeof(double));
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

    int Y_size = size - 6;
    double* Y_c = (double*)malloc(Y_size * sizeof(double));
    if (Y_c == NULL) {
        printf("Error: Memory allocation failed");
        free(X);
        return 1;
    }

    clock_t start_c = clock();
    process_c(X, size, Y_c);
    clock_t end_time_c = clock();
    double elapsed_c = (end_time_c - start_c) * 1000.0 / CLOCKS_PER_SEC;

    // Print first and last values of C program output
    printf("Answer (C kernel): ");
    printf("First value: %.lf, Last value: %.lf\n", Y_c[0], Y_c[Y_size - 1]);
    printf("C kernel execution time: %.5f ms\n\n", elapsed_c);

    // -----------
    // ASM PROGRAM
    // -----------

    double* Y_asm = (double*)malloc(Y_size * sizeof(double));
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

    // Print first and last values of ASM program output
    printf("Answer (ASM kernel): ");
    printf("First value: %.lf, Last value: %.lf\n", Y_asm[0], Y_asm[Y_size - 1]);
    printf("ASM kernel execution time: %.5f ms\n", elapsed);

    // Check if C output and ASM output are exactly the same
    bool outputs_match = compare_outputs(Y_c, Y_asm, Y_size);
    if (outputs_match) {
        printf("\nCorrectness Check: PASS\n");
        printf("C output and ASM output are exactly the same!");
    }
    else {
        printf("\nCorrectness Check: FAIL\n");
        printf("C output and ASM output are different!");
    }

    // Free memory allocs
    free(X);
    free(Y_c);
    free(Y_asm);

    return 0;
}