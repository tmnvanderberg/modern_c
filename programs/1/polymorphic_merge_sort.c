#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_func)(void *, void *);

#define ARRAY_SIZE 10

void merge(void *left, int left_size, void *right, int right_size, void *result,
           int element_size, compare_func compare) {
  int i = 0, j = 0, k = 0;
  // compare until either left or right runs out
  while (i != left_size && j != right_size) {
    if (compare((char *)left + i * element_size,
                (char *)right + j * element_size) == 1) {
      memcpy((char *)result + k * element_size, (char *)left + i * element_size,
             element_size);
      i++;
    } else {
      memcpy((char *)result + k * element_size,
             (char *)right + j * element_size, element_size);
      j++;
    }
    k++;
  }

  // copy remaining elements, if any
  while (i < left_size) {
    memcpy((char *)result + k * element_size, (char *)left + i * element_size,
           element_size);
    k++;
    i++;
  }
  while (j < right_size) {
    memcpy((char *)result + k * element_size, (char *)right + i * element_size,
           element_size);
    k++;
    j++;
  }
}

void merge_sort(void *array, const int array_size, const int element_size,
                compare_func compare) {
  // base case
  if (array_size == 1)
    return;

  // split array into left and right half
  const int left_size = array_size / 2;
  const int right_size = array_size - left_size;
  void *left = malloc(element_size * left_size);
  void *right = malloc(element_size * right_size);
  for (int i = 0; i != left_size; ++i) {
    memcpy((char *)left + i * element_size, (char *)array + i * element_size,
           element_size);
  }
  for (int i = 0; i != right_size; ++i) {
    memcpy((char *)right + i * element_size, (char *)array + i * element_size,
           element_size);
  }

  // sort subsets
  merge_sort(left, left_size, element_size, compare);
  merge_sort(right, right_size, element_size, compare);

  // merge left and right into array
  merge(left, left_size, right, right_size, array, element_size, compare);
}

bool is_sorted(void *array, const int array_size, const int element_size,
               compare_func compare) {
  for (int i = 0; i != array_size - 1; i++) {
    if (compare((char *)array + i * element_size,
                (char *)array + (i + 1) * element_size) == -1)
      return false;
  }
  return true;
}

int compare_doubles(void *left, void *right) {
  double x = *(double *)left;
  double y = *(double *)right;
  if (x < y)
    return -1;
  if (x > y)
    return 1;
  return 0;
}

int main() {
  double arr[ARRAY_SIZE] = {4.2, 2.3, 3.8, 1.2, 9.4, 9.3, 3.2, 4.1, 4.1, 11.9};
  merge_sort(arr, ARRAY_SIZE, sizeof(double), &compare_doubles);
  assert(is_sorted(arr, ARRAY_SIZE, sizeof(double), &compare_doubles));
}
