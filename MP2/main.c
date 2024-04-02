#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

extern void process(double*, int, double*);

static double* process_c(double* X, int size, double* Y) {
    int start_index = 3;
    int end = size - 1;
    int counter = 0;

    for (int i = start_index; i <= end; i++) {
        if (i - 3 >= 0 && i + 3 < size) {
            Y[counter++] = X[i - 3] + X[i - 2] + X[i - 1] + X[i] + X[i + 1] + X[i + 2] + X[i + 3];
        }
    }

    return Y;
}

static void print_array_10(double* arr, int size) {
    int print_size = (size < 10) ? size : 10;
    for (int i = 0; i < print_size; i++) {
        printf("%.lf ", arr[i]);
    }
    printf("\n");
}

static bool compare_outputs(double* Y_c, double* Y_asm, int Y_size) {
    for (int i = 0; i < Y_size; i++) {
        if (Y_c[i] != Y_asm[i]) {
            return false;
        }
    }
    return true;
}

static void run_comparison(double* X, int vector_size, double* Y_c, double* Y_asm, int Y_size) {
    process_c(X, vector_size, Y_c);
    process(X, vector_size, Y_asm);

    printf("--------------------Vector Size: %d--------------------\n", vector_size);
    printf("First 10 elements of vector Y (C kernel): ");
    print_array_10(Y_c, Y_size);
    printf("First 10 elements of vector Y (ASM kernel): ");
    print_array_10(Y_asm, Y_size);

    // Check if C output and ASM output are exactly the same
    bool outputs_match = compare_outputs(Y_c, Y_asm, Y_size);
    if (outputs_match) {
        printf("Correctness Check: PASS\n");
        printf("C output and ASM output are exactly the same!\n");
    } else {
        printf("Correctness Check: FAIL\n");
        printf("C output and ASM output are different!\n");
    }

    printf("\n");
    printf("Runtime Comparison (30 attempts):\n\n");

    // C Kernel
    double total_time_c = 0.0;
    printf("C Execution Times (in ms): ");
    for (int i = 0; i < 30; i++) {
        clock_t start_c = clock();
        process_c(X, vector_size, Y_c);
        clock_t end_time_c = clock();
        double elapsed_c = (end_time_c - start_c) * 1000.0 / CLOCKS_PER_SEC;
        printf("%.1f ", elapsed_c);
        total_time_c += elapsed_c;
    }

    // ASM Kernel
    double total_time_asm = 0.0;
    printf("\nASM Execution Times (in ms): ");
    for (int i = 0; i < 30; i++) {
        clock_t start_asm = clock();
        process(X, vector_size, Y_asm);
        clock_t end_time_asm = clock();
        double elapsed_asm = (end_time_asm - start_asm) * 1000.0 / CLOCKS_PER_SEC;
        printf("%.1f ", elapsed_asm);
        total_time_asm += elapsed_asm;
    }

    // Average Execution Times
    double avg_time_c = total_time_c / 30.0;
    double avg_time_asm = total_time_asm / 30.0;
    printf("\n\n");
    printf("Average C Kernel Execution Time: %.5f ms\n", avg_time_c);
    printf("Average ASM Kernel Execution Time: %.5f ms\n", avg_time_asm);

    // Speed Ratio
    double speed_ratio = (avg_time_c / avg_time_asm) * 100.0;
    printf("The assembly kernel is %.2f%% the speed of the C kernel.\n", speed_ratio);
}

static void run_custom_input() {
    int size = 0;
    char input[500];

    // Get input
    printf("Enter comma-separated double values: ");
    fgets(input, sizeof(input), stdin);
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
        printf("Error: Memory allocation failed for vector X");
        return;
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
        return;
    }

    // Allocate memory for vector Y
    int Y_size = size - 6;
    double* Y_c = malloc(Y_size * sizeof(double));
    double* Y_asm = malloc(Y_size * sizeof(double));

    if (Y_c == NULL || Y_asm == NULL) {
        printf("Error: Memory allocation failed for vector Y");
        free(X);
        free(Y_c);
        free(Y_asm);
        return;
    }

    // Execute C program
    clock_t start_c = clock();
    process_c(X, size, Y_c);
    clock_t end_time_c = clock();
    double elapsed_c = (end_time_c - start_c) * 1000.0 / CLOCKS_PER_SEC;

    // Print first 10 elements of vector Y
    printf("First 10 elements of vector Y (C kernel): ");
    print_array_10(Y_c, Y_size);
    printf("C kernel execution time: %.5f ms\n\n", elapsed_c);

    // Execute ASM program
    clock_t start = clock();
    process(X, size, Y_asm);
    clock_t end_time = clock();
    double elapsed = (end_time - start) * 1000.0 / CLOCKS_PER_SEC;

    // Print first 10 elements of vector Y
    printf("First 10 elements of vector Y (ASM kernel): ");
    print_array_10(Y_asm, Y_size);
    printf("ASM kernel execution time: %.5f ms\n", elapsed);

    // Correctness Check
    bool outputs_match = compare_outputs(Y_c, Y_asm, Y_size);
    if (outputs_match) {
        printf("\nCorrectness Check: PASS\n");
        printf("C output and ASM output are exactly the same!");
    } else {
        printf("\nCorrectness Check: FAIL\n");
        printf("C output and ASM output are different!");
    }

    free(X);
    free(Y_c);
    free(Y_asm);
}

int main() {
    int choice;
    printf("Choose what you want the program to do.\n");
    printf("1. Run predefined comparisons\n");
    printf("2. Enter custom input\n");
    printf("Enter your choice (1 or 2): ");
    if (scanf_s("%d", &choice) != 1) {
        printf("Invalid input. Exiting the program.\n");
        return 1;
    }
    (void)getchar();

    if (choice == 1) {
        printf("\n\n");
        int sizes[] = { (int)pow(2, 20), (int)pow(2, 24), (int)pow(2, 30) };
        int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

        for (int i = 0; i < num_sizes; i++) {
            int vector_size = sizes[i];
            int Y_size = vector_size - 6;
            double* X = malloc(vector_size * sizeof(double));
            double* Y_c = malloc(Y_size * sizeof(double));
            double* Y_asm = malloc(Y_size * sizeof(double));

            // Ensure memory allocation success
            if (X == NULL || Y_c == NULL || Y_asm == NULL) {
                printf("Error: Memory allocation failed for vector size %d\n", vector_size);
                free(X);
                free(Y_c);
                free(Y_asm);
                break;
            }

            // Fill the vector with counting numbers
            for (int j = 0; j < vector_size; j++) {
                X[j] = j + 1;
            }

            run_comparison(X, vector_size, Y_c, Y_asm, Y_size);
            printf("\n\n");

            free(X);
            free(Y_c);
            free(Y_asm);
        }
    }
    else if (choice == 2) {
        printf("\n");
        run_custom_input();
    }
    else {
        printf("Invalid choice. Exiting the program.\n");
    }

    return 0;
}