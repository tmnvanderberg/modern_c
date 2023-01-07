#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void merge(double left[], int left_size, double right[], int right_size,
           double *result) {
  int i = 0, j = 0, k = 0;
  // compare until either left or right runs out
  while (i != left_size && j != right_size) {
    if (left[i] < right[j]) {
      result[k] = left[i];
      i++;
    } else {
      result[k] = right[j];
      j++;
    }
    k++;
  }

  // copy remaining elements, if any
  while (i < left_size)
    result[k++] = left[i++];
  while (j < right_size)
    result[k++] = left[j++];
}

void merge_sort(double array[], const int array_size) {
  // base case
  if (array_size == 1)
    return;

  // split array into left and right half
  const int left_size = array_size / 2;
  const int right_size = array_size - left_size;
  double left[left_size];
  double right[right_size];
  for (int i = 0; i != left_size; ++i)
    left[i] = array[i];
  for (int i = 0; i != right_size; ++i)
    right[i] = array[i + left_size];

  // sort subsets
  merge_sort(left, left_size);
  merge_sort(right, right_size);

  // merge left and right into array
  merge(left, left_size, right, right_size, array);
}

bool is_sorted(double array[], const int array_size) {
  for (int i = 0; i != array_size - 1; i++) {
    if (array[i] > array[i + 1])
      return false;
  }
  return true;
}

int main() {
  double arr[ARRAY_SIZE] = {4.2, 2.3, 3.8, 1.2, 9.4, 9.3, 3.2, 4.1, 4.1, 11.9};
  merge_sort(arr, ARRAY_SIZE);
  assert(is_sorted(arr, ARRAY_SIZE));
}
