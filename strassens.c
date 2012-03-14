/* strassens.c
 *
 * This file contains an implementation of Strassen's matrix
 * multiplication algorithm for square matrices of equal dimensions
 * where the dimension SIZE must be a power of 2.
 *
 * @author: Henrik Almer <henrik.almer@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 128

/* Takes a pointer to a 2-dimensional array long matrix of int size and
 * prints it to stdout, preceeded by a char label.
 */
void print_matrix(char *label, int size, long (*matrix)[size])
{
    int i = 0;
    int j = 0;

    printf("%s\n", label);
    printf("{\n");
    for(i = 0; i < size; i++) {
        printf("\t[");
        for(j = 0; j < size; j++) {
            printf("%ld\t", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("}\n");
}

/* Takes a pointer to a 2-dimensional array long matrix of int size and
 * fills it with random numbers.
 */
void fill_matrix(int size, long (*matrix)[size])
{
    int i = 0;
    int j = 0;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

/* Iterative matrix multiplication. The naive implementation.
 */
void naive_matrix_multiplication(
    int size,
    long (*a)[size],
    long (*b)[size],
    long (*result)[size]
)
{
    int i = 0;
    int j = 0;
    int k = 0;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            result[i][j] = 0;
            for(k = 0; k < size; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/* Subtract two matrices
 */
void subtract_matrices(
    int size,
    long (*a)[size],
    long (*b)[size],
    long (*result)[size]
)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

/* Add two matrices
 */
void add_matrices(
    int size,
    long (*a)[size],
    long (*b)[size],
    long (*result)[size]
)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/* Implementation of Strassen's recursive matrix multiplication
 * algorithm.
 */
void strassens_multiplication(
    int size,
    long (*a)[size],
    long (*b)[size],
    long (*result)[size]
)
{
    if(size <= 2) {
        naive_matrix_multiplication(size, a, b, result);
    } else {
        int block_size = size / 2;

        // The four quadrants (blocks) of the first matrix
        long a11[block_size][block_size];
        long a12[block_size][block_size];
        long a21[block_size][block_size];
        long a22[block_size][block_size];
        // The four quadrants (blocks) of the second matrix
        long b11[block_size][block_size];
        long b12[block_size][block_size];
        long b21[block_size][block_size];
        long b22[block_size][block_size];
        // The four quadrants (blocks) of the resulting matrix
        long c11[block_size][block_size];
        long c12[block_size][block_size];
        long c21[block_size][block_size];
        long c22[block_size][block_size];

        // The 7 blocks defined by Strassen
        long m1[block_size][block_size];
        long m2[block_size][block_size];
        long m3[block_size][block_size];
        long m4[block_size][block_size];
        long m5[block_size][block_size];
        long m6[block_size][block_size];
        long m7[block_size][block_size];

        int i = 0;
        int j = 0;

        for(i = 0; i < block_size; i++) {
            for(j = 0; j < block_size; j++) {
                // Assign correct values to the different blocks
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j + block_size];
                a21[i][j] = a[i + block_size][j];
                a22[i][j] = a[i + block_size][j + block_size];
                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j + block_size];
                b21[i][j] = b[i + block_size][j];
                b22[i][j] = b[i + block_size][j + block_size];
            }
        }

        long add_result1[size][size];
        long add_result2[size][size];
        long subtract_result[size][size];

        // Calculate the values of Strassens blocks
        // m1
        add_matrices(block_size, a11, a22, add_result1);
        add_matrices(block_size, b11, b22, add_result2);
        strassens_multiplication(block_size, add_result1, add_result2,
            m1);
        // m2
        add_matrices(block_size, a21, a22, add_result1);
        strassens_multiplication(block_size, add_result1, b11, m2);
        // m3
        subtract_matrices(block_size, b12, b22, subtract_result);
        strassens_multiplication(block_size, a11, subtract_result, m3);
        // m4
        subtract_matrices(block_size, b21, b11, subtract_result);
        strassens_multiplication(block_size, a22, subtract_result, m4);
        // m5
        add_matrices(block_size, a11, a12, add_result1);
        strassens_multiplication(block_size, add_result1, b22, m5);
        // m6
        subtract_matrices(block_size, a21, a11, subtract_result);
        add_matrices(block_size, b11, b12, add_result1);
        strassens_multiplication(block_size, subtract_result,
            add_result1, m6);
        // m7
        subtract_matrices(block_size, a12, a22, subtract_result);
        add_matrices(block_size, b21, b22, add_result1);
        strassens_multiplication(block_size, subtract_result,
            add_result1, m7);

        // Calculate the resulting product matrix
        // c11
        add_matrices(block_size, m1, m4, add_result1);
        add_matrices(block_size, add_result1, m7, add_result2);
        subtract_matrices(block_size, add_result2, m5, c11);
        // c12
        add_matrices(block_size, m3, m5, c12);
        // c21
        add_matrices(block_size, m2, m4, c21);
        // c22
        add_matrices(block_size, m1, m3, add_result1);
        add_matrices(block_size, add_result1, m6, add_result2);
        subtract_matrices(block_size, add_result2, m2, c22);

        // Concatenate the four product blocks in our result matrix
        int k = 0;
        for(k = 0; k < block_size; k++) {
            for(j = 0; j < block_size; j++) {
                result[k][j] = c11[k][j];
                result[k][j + block_size] = c12[k][j];
                result[k + block_size][j] = c21[k][j];
                result[k + block_size][j + block_size] = c22[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int size = SIZE;

    long matrix_a[size][size];
    long matrix_b[size][size];
    long matrix_result[size][size];

    fill_matrix(size, matrix_a);
    fill_matrix(size, matrix_b);

    strassens_multiplication(size, matrix_a, matrix_b, matrix_result);

    print_matrix("Matrix A:", size, matrix_a);
    print_matrix("Matrix B:", size, matrix_b);
    print_matrix("Strassens Result:", size, matrix_result);

    return 0;
}
