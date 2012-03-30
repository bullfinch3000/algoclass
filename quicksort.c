/* quicksort.c
 *
 * Implementation of QuickSort.
 *
 * @author: Henrik Almer <henrik.almer@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

#define PIVOT 2

long comparisons = 0;

void print_array(char *label, int *array, int size)
{
    printf("%s", label);
    int i = 0;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *array, int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int median_of_three(int *array, int left, int right)
{
    int middle = left + ((right - left + 1)  / 2) - 1;

    // order left and middle values
    if(array[left] > array[middle]) {
        swap(array, left, middle);
    }
    // order left and right values
    if(array[left] > array[right - 1]) {
        swap(array, left, right - 1);
    }
    // order middle and right values
    if(array[middle] > array[right - 1]) {
        swap(array, middle, right - 1);
    }
    swap(array, middle, right - 1);

    return right - 1;
}

int choose_pivot(int *array, int left, int right)
{
    int pivot;

    switch(PIVOT)
    {
        case 0:
            // return the first elemnt
            pivot = left;
            break;
        case 1:
            // return the last element
            pivot = right - 1;
            break;
        case 2:
            // return the "median-of-three"
            pivot = median_of_three(array, left, right);
            break;
        default:
            pivot = left;
            break;
    }

    return pivot;
}

int partition_array(int *array, int left, int right)
{
    int i, j;
    int pivot;

    pivot = choose_pivot(array, left, right);
    swap(array, left, pivot);
    pivot = left;
    i = left + 1;
    j = left + 1;
    for(j = left + 1; j < right; j++) {
        if(array[j] < array[pivot]) {
            swap(array, i, j);
            i++;
        }
    }
    swap(array, pivot, i - 1);

    return i;
}

void quicksort(int *array, int left, int right)
{
    if(left < right) {
        // update comparison count
        comparisons += (right - left) - 1;

        int i = partition_array(array, left, right);
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

    printf("Number of comparisons: %ld\n", comparisons);

    return 0;
}
