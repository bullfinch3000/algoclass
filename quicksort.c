/* quicksort.c
 *
 * Implementation of QuickSort.
 *
 * @author: Henrik Almer <henrik.almer@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

void print_array(char *label, int *array, int size)
{
    printf("%s", label);
    int i = 0;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int choose_pivot(int *array, int left, int right)
{
    return left;
}

void swap(int *array, int first_index, int second_index)
{
    int temp = array[first_index];
    array[first_index] = array[second_index];
    array[second_index] = temp;
}

void quicksort(int *array, int left, int right)
{
    int i, j;
    int pivot;

    if(left < right) {
        pivot = choose_pivot(array, left, right);
        i = left + 1;
        j = left + 1;
        for(j = left + 1; j < right; j++) {
            if(array[j] < array[pivot]) {
                swap(array, i, j);
                i++;
            }
        }
        swap(array, pivot, i - 1);
        quicksort(array, left, i - 1);
        quicksort(array, i, right);
    }
}

int main(int argc, char *argv[])
{
    int size = 10;
    int array[] = {9, 8, 7, 6, 5, 5, 4, 3, 2, 1};

    print_array("V: ", array, size);
    quicksort(array, 0, size);
    print_array("V: ", array, size);

    return 0;
}
