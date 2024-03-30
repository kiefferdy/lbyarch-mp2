#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void process_c(double num[], int size, int iteration) {
    int start = iteration;
    int end = size - 1;
    double result[999] = {};
    int i;
    int counter = 0;
    for (i = start; i <= end; i++) {
        // if greater or less than array break loop
        if (i - 3 < 0 || i + 3 >= size) {
            break;
        }
        else {
            result[counter] = num[i - 3] + num[i - 2] + num[i - 1] + num[i] + num[i + 1] + num[i + 2] + num[i + 3];
            if (counter > 0) {
                printf(", ");
            }
            printf("%.lf", result[counter]);
            counter++;
        }
    }
    printf("\n");
}