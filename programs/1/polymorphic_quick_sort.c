#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_func)(void *, void *);

#define ARRAY_SIZE 10

void swap(void *left, void *right, const int element_size) {
  char tmp[element_size];
  memcpy(&tmp, left, element_size);
  memcpy(left, right, element_size);
  memcpy(right, &tmp, element_size);
}

int partition(void *array, const int left, const int right,
              const int element_size, compare_func compare) {
  int pivot = right;
  int i = left - 1;
  for (int j = left; j != right; ++j) {
    const int cmpr = compare((char *)array + j * element_size,
                             (char *)array + pivot * element_size);
    if (cmpr == -1 || cmpr == 0) { // less or equal
      i++;
      swap((char *)array + i * element_size, (char *)array + j * element_size,
           element_size);
    }
  }
  i++;
  swap((char *)array + i * element_size, (char *)array + right * element_size,
       element_size);
  return i;
}

void quick_sort(void *array, const int left, const int right,
                const int element_size, compare_func compare) {
  if (left >= right || right < 0) {
    return;
  }
  const int pivot_idx = partition(array, left, right, element_size, compare);
  quick_sort(array, left, pivot_idx - 1, element_size, compare);
  quick_sort(array, pivot_idx + 1, right, element_size, compare);
}

bool is_sorted(void *array, const int array_size, const int element_size,
               compare_func compare) {
  for (int i = 0; i != array_size - 1; i++) {
    const int cmpr = compare((char *)array + i * element_size,
                             (char *)array + (i + 1) * element_size);
    if (cmpr == 1) { // greater then
      return false;
    }
  }
  return true;
}

int compare_doubles(void *left, void *right) {
  double x = *(double *)left;
  double y = *(double *)right;
  if (x < y) {
    return -1;
  }
  if (x > y) {
    return 1;
  }
  return 0;
}

int main() {
  {
    double a = 4.44;
    double b = 2.99;
    assert(compare_doubles(&a, &b) == 1);
    assert(compare_doubles(&b, &a) == -1);
    assert(compare_doubles(&a, &a) == 0);
  }
  {
    double a = 4.4;
    double b = 9.2;
    swap(&a, &b, sizeof(double));
    assert(a == 9.2);
    assert(b == 4.4);
  }
  {
    double arr[ARRAY_SIZE] = {4.2, 2.3, 3.8, 1.2, 9.4,
                              9.3, 3.2, 4.1, 4.1, 11.9};
    quick_sort(arr, 0, ARRAY_SIZE - 1, sizeof(double), &compare_doubles);
    assert(is_sorted(arr, ARRAY_SIZE, sizeof(double), &compare_doubles));
  }
}
