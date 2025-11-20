//
// Created by njfot on 19/11/2025.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "hasse.h"

typedef struct {
    float **data;
    int rows;
    int cols;
} t_matrix;

/**
 * @brief Creates a transition matrix from an adjacency list
 * @param adj The adjacency list representing the Markov graph
 * @return A matrix filled with transition probabilities
 */
t_matrix createTransitionMatrix(t_adjacency_list* adj);

/**
 * @brief Creates an empty n x n matrix filled with zeros
 * @param n The size of the matrix (n x n)
 * @return An empty matrix
 */
t_matrix createEmptyMatrix(int n);

/**
 * @brief Copies values from one matrix to another of the same size
 * @param dest The destination matrix
 * @param src The source matrix
 */
void copyMatrix(t_matrix dest, t_matrix src);

/**
 * @brief Multiplies two n x n matrices
 * @param m1 First matrix
 * @param m2 Second matrix
 * @param result The resulting matrix (must be pre-allocated)
 */
void multiplyMatrices(t_matrix m1, t_matrix m2, t_matrix result);

/**
 * @brief Calculates the difference between two matrices
 * @param m1 First matrix
 * @param m2 Second matrix
 * @return The sum of absolute differences between coefficients
 */
float diff(t_matrix m1, t_matrix m2);

/**
 * @brief Displays a matrix
 * @param matrix The matrix to display
 */
void displayMatrix(t_matrix matrix);

/**
 * @brief Frees memory allocated for a matrix
 * @param matrix The matrix to free
 */
void freeMatrix(t_matrix matrix);

/**
 * @brief Calculates the nth power of a matrix
 * @param matrix The base matrix
 * @param n The exponent
 * @return The resulting matrix M^n
 */
t_matrix matrixPower(t_matrix matrix, int n);

/**
* @brief Extracts a submatrix corresponding to a specific component of a graph partition.
* @param matrix The original adjacency matrix of the graph.
* @param part The partition of the graph into strongly connected components.
* @param compo_index The index of the component to extract.
* @return t_matrix The submatrix corresponding to the specified component.
*/
t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);

/**
 * @brief Compute the stationary distribution of a Matrix by computing her power untils the difference is less than 0.01
 * @param matrix The matrix use to compute the stationary distribution
 * @return The stationary distribution of the matrix
 */
t_matrix stationaryDistribution(t_matrix matrix);

#endif