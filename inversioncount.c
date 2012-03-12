/* inversioncount.c
 *
 * Using mergesort.c as a template this file contains an implementation
 * of an algorithm that counts array inversions.
 *
 * @author: Henrik Almer <henrik.almer@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(char *label, int *array, int size)
{
    printf("%s", label);
    int i = 0;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int merge_and_count(int *array, int left, int middle, int right)
{
    int inversions = 0;

    int i = left;
    int j = middle + 1;

    int *temp = (int*)malloc((right - left + 1) * sizeof(int));
    int k = 0;

    while((i <= middle) && (j <= right)) {
        if(array[i] <= array[j]) {
            temp[k] = array[i];
            i++;
        } else {
            temp[k] = array[j];
            inversions += middle - i + 1; 
            j++;
        }
        k++;
    }

    while(i <= middle) {
        temp[k] = array[i];
        i++;
        k++;
    }

    while(j <= right) {
        temp[k] = array[j];
        j++;
        k++;
    }

    memcpy(array + left, temp, (right - left + 1) * sizeof(int));
    free(temp);

    return inversions;
}

int merge_sort_and_count(int *array, int left, int right)
{
    if(left < right) {
        int inversions = 0;
        int middle = (left + right) / 2;
        inversions += merge_sort_and_count(array, left, middle);
        inversions += merge_sort_and_count(array, middle + 1, right);
        inversions += merge_and_count(array, left, middle, right);

        return inversions;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int inversions = 0;
    int size = 10;
    int array[] = {9, 8, 7, 6, 5, 5, 4, 3, 2, 1};

    print_array("V: ", array, size);
    inversions = merge_sort_and_count(array, 0, size - 1);
    print_array("V: ", array, size);
    printf("Inversions: %d\n", inversions);

    return 0;
}
