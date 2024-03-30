#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern double process(double arr[], int size);
extern double process_c(double num[], int size, int iteration);

int main() {
    double c_Ans = 0.0;
    double asm_Ans = 0.0;
    int size = 0;

    char input[500];  // Assume a maximum input length of 500 characters
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
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Parse the input string and store values in the array
    char* token = NULL;
    char* context = NULL;  // For strtok_s

    token = strtok_s(input, ",", &context);
    while (token != NULL && size < count) {
        arr[size++] = atof(token);
        token = strtok_s(NULL, ",", &context);
    }

    if (size < 7) {
        printf("Array must have a length 7 or greater");
        return 0;
    }

    // Print the parsed numbers
    printf("Parsed numbers:\n");
    for (int i = 0; i < size; i++) {
        printf("%lf\n", arr[i]);
    }

    printf("Answer (C kernel): ");
    c_Ans = process_c(arr, size, 3);

    printf("Answer (asm kernel): ");
    asm_Ans = process(arr, size);

    free(arr);

    return 0;
}