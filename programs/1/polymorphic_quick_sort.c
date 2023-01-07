#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_func)(void *, void *);

#define ARRAY_SIZE 10

void swap(void *left, void *right, const int element_size) {
  printf("swapping left: %f, and right %f\n", *(double *)left,
         *(double *)right);
  char tmp[element_size];
  memcpy(&tmp, left, element_size);
  memcpy(left, right, element_size);
  memcpy(right, &tmp, element_size);
  printf("after swapping left: %f, and right %f\n", *(double *)left,
         *(double *)right);
}

int partition(void *array, const int left, const int right,
              const int element_size, compare_func compare) {
  printf(" -> partition with left: %d, right: %d \n", left, right);
  void *pivot = (char *)array + right * element_size;
  printf("pivot: %f\n", *(double *)pivot);
  int i = left - 1;
  for (int j = left; j != right; ++j) {
    if (compare((char *)array + j * element_size, pivot) == -1) {
      i++;
      printf("swapping i: %d, and j: %d\n", i, j);
      swap((char *)array + i * element_size, (char *)array + j * element_size,
           element_size);
    }
  }
  i++;
  swap((char *)array + i * element_size, (char *)array + right * element_size,
       element_size);
  printf("returning from partition: %d\n", i + 1);
  return i + 1;
}

void quick_sort(void *array, const int left, const int right,
                const int element_size, compare_func compare) {
  printf("quicksort with left, right: %d, %d\n", left, right);
  if (left < right) {
    const int pivot_idx = partition(array, left, right, element_size, compare);
    quick_sort(array, left, pivot_idx - 1, element_size, compare);
    quick_sort(array, pivot_idx + 1, right, element_size, compare);
  }
}

bool is_sorted(void *array, const int array_size, const int element_size,
               compare_func compare) {
  for (int i = 0; i != array_size - 1; i++) {
    if (compare((char *)array + i * element_size,
                (char *)array + (i + 1) * element_size) == -1) {
      printf("false for %d with values %f, %f\n", i,
             *(double *)array + i * element_size,
             *(double *)array + (i + 1) * element_size);
      return false;
    }
  }
  return true;
}

int compare_doubles(void *left, void *right) {
  double x = *(double *)left;
  double y = *(double *)right;
  printf("comparing %f and %f, ", x, y);
  if (x < y) {
    printf("<, returning -1\n");
    return -1;
  }
  if (x > y) {
    printf(">, returning 1\n");
    return 1;
  }
  printf("==, returning 0\n");
  return 1;
  return 0;
}

int main() {
  double arr[ARRAY_SIZE] = {4.2, 2.3, 3.8, 1.2, 9.4, 9.3, 3.2, 4.1, 4.1, 11.9};
  quick_sort(arr, 0, ARRAY_SIZE - 1, sizeof(double), &compare_doubles);
  printf("sorted array:");
  for (int i = 0; i != ARRAY_SIZE; ++i) {
    printf("%f\n", arr[i]);
  }
  assert(is_sorted(arr, ARRAY_SIZE, sizeof(double), &compare_doubles));
}
