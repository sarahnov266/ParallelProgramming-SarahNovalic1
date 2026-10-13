#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size = 1000;
    double *array1, *array2, *result;

    array1 = (double*)malloc(size * sizeof(double));
    array2 = (double*)malloc(size * sizeof(double));
    result = (double*)malloc(size * sizeof(double));

    if (!array1 || !array2 || !result) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        array1[i] = i * 2.5;
        array2[i] = i * 1.5;
    }

    for (int i = 0; i < size; i++) {
        result[i] = array1[i] + array2[i];
    }

    printf("First 10 results:\n");

    for (int i = 0; i < 10; i++) {
        printf("result[%d] = %.2f\n", i, result[i]);
    }

    printf("Memory allocated: %lu bytes\n", 3 * size * sizeof(double));

    free(array1);
    free(array2);
    free(result);

    return 0;
}
