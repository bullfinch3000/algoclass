/* mergesort.c
 *
 * Here be an implementation of the classic merge sort in C. It was
 * written as an excercise in learning C while looking at lectures from
 * algo-class <https://www.coursera.org/algo/class>. The code is stolen
 * from http://snippets.dzone.com/posts/show/4585 where it was posted
 * by Alexandru Scortvov.
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

void merge(int *array, int left, int middle, int right)
{
    int i = left;
    int j = middle + 1;

    int *temp = (int*)malloc((right - left + 1) * sizeof(int));
    int k = 0;

    while((i <= middle) && (j <= right)) {
        if(array[i] < array[j]) {
            temp[k] = array[i];
            i++;
        } else {
            temp[k] = array[j];
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
}

void merge_sort(int *array, int left, int right)
{
    if(left < right) {
        int middle = (left + right) / 2;
        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

int main(int argc, char *argv[])
{
    int size = 10;
    int array[] = {9, 8, 7, 6, 5, 5, 4, 3, 2, 1};

    print_array("V: ", array, size);
    merge_sort(array, 0, size - 1);
    print_array("V: ", array, size);

    return 0;
}
