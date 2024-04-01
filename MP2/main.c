#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern double process(double arr[], int size);

double* process_c(double num[], int size, int iteration) {
    int start_index = iteration;
    int end = size - 1;
    double* result = (double*)malloc(999 * sizeof(double));
    int i;
    int counter = 0;

    for (i = start_index; i <= end; i++) {
        // if greater or less than array break loop
        if (i - 3 < 0 || i + 3 >= size) {
            break;
        }
        else {
            result[counter] = num[i - 3] + num[i - 2] + num[i - 1] + num[i] + num[i + 1] + num[i + 2] + num[i + 3];
            counter++;
        }
    }

    return result;
}

int main() {
    double* c_Ans;
    double asm_Ans;
    int size = 0;
    char input[500];
    printf("Enter comma-separated double values: ");
    fgets(input, sizeof(input), stdin);

    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    // Count the number of commas to determine the number of elements
    int count = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ',') {
            count++;
        }
    }

    double* arr = malloc(sizeof(double) * count);
    if (arr == NULL) {
        printf("Error: Memory allocation failed");
        return 1;
    }

    // Parse the input string and store values in the array
    char* token = NULL;
    char* context = NULL; // For strtok_s
    token = strtok_s(input, ",", &context);
    while (token != NULL && size < count) {
        arr[size++] = atof(token);
        token = strtok_s(NULL, ",", &context);
    }

    if (size < 7) {
        printf("Array must be of length 7 or greater");
        return 0;
    }

    printf("Answer (C kernel): ");
    clock_t C_start = clock();
    c_Ans = process_c(arr, size, 3);
    clock_t C_end_time = clock();
    double C_elapsed = ((double)(C_end_time - C_start)) * 1000.0 / CLOCKS_PER_SEC;
    for (int i = 0; i < size - 6; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.lf", c_Ans[i]);
    }
    printf("\n");
    printf("C kernel execution time: %.5f ms\n\n", C_elapsed);

    printf("Answer (ASM kernel): ");
    clock_t start = clock();
    asm_Ans = process(arr, size);

    /* Print for when is this 
    for (int i = 0; i < size - 6; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.lf", asm_Ans[i]);
    }
     */
        
    clock_t end_time = clock();
    double elapsed = ((double)(end_time - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("\nASM kernel execution time: %.5f ms\n", elapsed);

    free(arr);
    free(c_Ans);

    return 0;
}