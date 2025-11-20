//
// Created by njfot on 19/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "hasse.h"

t_matrix createTransitionMatrix(t_adjacency_list* adj) {
    t_matrix matrix;
    matrix.rows = adj->size;
    matrix.cols = adj->size;

    // Allocate memory for the matrix
    matrix.data = (float**)malloc(matrix.rows * sizeof(float*));
    for (int i = 0; i < matrix.rows; i++) {
        matrix.data[i] = (float*)calloc(matrix.cols, sizeof(float));
    }

    // Fill the matrix with transition probabilities
    for (int i = 0; i < adj->size; i++) {
        t_cell* current = adj->tab[i].head;
        while (current != NULL) {
            // arrival_vertex is 1-indexed, so we subtract 1
            int col = current->arrival_vertex - 1;
            matrix.data[i][col] = current->probability;
            current = current->next;
        }
    }

    return matrix;
}

t_matrix createEmptyMatrix(int n) {
    t_matrix matrix;
    matrix.rows = n;
    matrix.cols = n;

    // Allocate and initialize to 0
    matrix.data = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        matrix.data[i] = (float*)calloc(n, sizeof(float));
    }

    return matrix;
}

void copyMatrix(t_matrix dest, t_matrix src) {
    if (dest.rows != src.rows || dest.cols != src.cols) {
        printf("Error: Matrix dimensions don't match for copy\n");
        return;
    }

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            dest.data[i][j] = src.data[i][j];
        }
    }
}

void multiplyMatrices(t_matrix m1, t_matrix m2, t_matrix result) {
    if (m1.cols != m2.rows || m1.rows != result.rows || m2.cols != result.cols) {
        printf("Error: Matrix dimensions incompatible for multiplication\n");
        return;
    }

    // Initialize result to 0
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.data[i][j] = 0.0f;
        }
    }

    // Perform multiplication
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m2.cols; j++) {
            for (int k = 0; k < m1.cols; k++) {
                result.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
}

float diff(t_matrix m1, t_matrix m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        printf("Error: Matrix dimensions don't match for diff\n");
        return -1.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            sum += fabs(m1.data[i][j] - m2.data[i][j]);
        }
    }

    return sum;
}

void displayMatrix(t_matrix matrix) {
    printf("Matrix %dx%d:\n", matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++) {
        printf("[ ");
        for (int j = 0; j < matrix.cols; j++) {
            printf("%.2f ", matrix.data[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

void freeMatrix(t_matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}

t_matrix matrixPower(t_matrix matrix, int n) {
    if (n < 0) {
        printf("Error: Negative power not supported\n");
        return createEmptyMatrix(0);
    }

    if (n == 0) {
        // Return identity matrix
        t_matrix identity = createEmptyMatrix(matrix.rows);
        for (int i = 0; i < matrix.rows; i++) {
            identity.data[i][i] = 1.0f;
        }
        return identity;
    }

    t_matrix result = createEmptyMatrix(matrix.rows);
    t_matrix temp = createEmptyMatrix(matrix.rows);

    // Copy matrix to result (M^1)
    copyMatrix(result, matrix);

    // Compute M^n
    for (int i = 1; i < n; i++) {
        multiplyMatrices(result, matrix, temp);
        copyMatrix(result, temp);
    }

    freeMatrix(temp);
    return result;
}

t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index) {
    t_partition_list partition_list = part.classes;
    t_partition_cell *curr = partition_list.head;
    for (int i = 0; i < compo_index; i++) {
        curr = curr->next;
    }
    t_class class = curr->class;
    int* class_arr = LinkedClass_to_Arrays(class);
    int n = class.size;
    t_matrix result = createEmptyMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = matrix.data[class_arr[i]-1][class_arr[j]-1];

        }
    }
    return result;

}

t_matrix stationaryDistribution(t_matrix matrix) {
    t_matrix Mn_prev = createEmptyMatrix(matrix.rows);
    t_matrix Mn = createEmptyMatrix(matrix.rows);
    copyMatrix(Mn, matrix);

    int n = 1;
    float epsilon = 0.01f;
    float difference;
    do {
        n++;
        copyMatrix(Mn_prev, Mn);
        t_matrix temp = matrixPower(matrix, n);
        copyMatrix(Mn, temp);
        freeMatrix(temp);

        difference = diff(Mn, Mn_prev);
        //printf("n=%d, diff=%.6f\n", n, difference);
    } while (difference > epsilon && n < 1000);
    return Mn;
}