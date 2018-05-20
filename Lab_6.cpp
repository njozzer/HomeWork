#include <iostream>
#include <stdlib.h>
#include <stdio.h>
void fill_matrix(double **m, int l) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            m[i][j] = i + 5 * j;
        }
    }
}

double **copy(double **m, int length) {
    double **matrix = (double **) malloc(length * sizeof(double *));
    for (int i = 0; i < length; ++i) {
        matrix[i] = (double *) malloc(length * sizeof(double));
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; ++j) {
            matrix[i][j] = m[i][j];
        }
    }
    return matrix;
}

double **edit(double **m, int l, int num) {
    double **matrix = copy(m, l);
    int n = 1;
    while (n < l) {
        int k = 0;
        for (int i = n; i < l; ++i) {
            k++;
        }
        double *arr1=(double*)malloc(k* sizeof(double));
        double *arr2=(double*)malloc(k* sizeof(double));
        for (int i = n; i < l; ++i) {
            arr1[i - n] = matrix[i][i - n];
            arr2[i - n] = matrix[i - n][i];
        }
        for (int i = n; i < l; ++i) {
            matrix[i][i - n] = arr1[(i - n + num) % k];
            matrix[i - n][i] = arr2[(i - n + num) % k];

        }
        free(arr1);
        free(arr2);
        n++;
    }
    return matrix;
}

void main_free(double **arr, int l) {
    for (int i = 0; i < l; ++i) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    srand(time(NULL));
    int length = rand() % 10 + 1;
    int switch_n = rand() % 15;
    double **matrix = (double **) malloc(length * sizeof(double *));
    for (int i = 0; i < length; ++i) {
        matrix[i] = (double *) malloc(length * sizeof(double));
    }
    fill_matrix(matrix, length);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; ++j) {
            printf("%3.0lf ", matrix[i][j]);
        }
        printf("\n");
    }
    double **changed = edit(matrix, length, switch_n);
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; ++j) {
            printf("%3.0lf ", changed[i][j]);
        }
        printf("\n");
    }
    main_free(matrix, length);
    main_free(changed, length);
    return 0;
}
