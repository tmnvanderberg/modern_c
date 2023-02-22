#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(const size_t *arr, size_t size, char *name) {
  printf("%s: \n", name);
  for (int i = 0; i != size; ++i) {
    printf("[%d, %zu] ", i, arr[i]);
  }
  printf("\n");
}

// matrix A[i], where A[i] == j <=> j is parent of i,
// and A[i] == SIZE_MAX indicates that i is the root element
size_t *forest_malloc(const size_t size) {
  size_t *forest = (size_t *)malloc(size * sizeof(size_t));
  return forest;
}

size_t *forest_init_singleton(const size_t size) {
  size_t *forest = forest_malloc(size * sizeof(size_t));
  for (int i = 0; i != size; ++i) {
    forest[i] = size;
  }
  return forest;
}

size_t get_random(const size_t size) {
  const size_t rand_n = rand() % size;
  return rand_n;
}

size_t *get_permutation(const size_t size) {
  size_t *numbers = (size_t *)malloc(size * sizeof(size_t));
  for (int i = 0; i != size; i++) {
    numbers[i] = i;
  }
  for (int i = 0; i != size; i++) {
    const size_t rand_idx = get_random(size - i) + i;
    const size_t num_at_rand_idx = numbers[rand_idx];
    numbers[rand_idx] = numbers[i];
    numbers[i] = num_at_rand_idx;
  }
  return numbers;
}

int get_nth_nonzero_idx(size_t *parented, const size_t parented_sz,
                        const size_t n) {
  int i = 0;
  int counter = 0;
  while (counter != n && i != parented_sz - 1) {
    if (parented[i] != 0) { // found a non-zero
      counter++;
    }
    i++;
  }
  return i;
}

size_t *forest_init_random(const size_t size, const size_t num_roots) {
  size_t *roots_perm = get_permutation(size);
  size_t parented[size];
  for (int i = 0; i != size; ++i) {
    parented[i] = 0;
  }
  size_t num_parents = 0;
  for (int i = 0; i != num_roots; ++i) {
    parented[roots_perm[i]] = 1; // roots are their own parent
    num_parents++;
  }
  size_t *forest = forest_init_singleton(size);
  for (int i = 0; i != size; ++i) {
    if (!parented[i]) {
      const int random_parent_idx =
          get_nth_nonzero_idx(parented, size, get_random(num_parents));
      parented[random_parent_idx] = 1;
      forest[i] = random_parent_idx;
      num_parents++;
    }
  }
  return forest;
}

void assert_is_permutation(const size_t *arr, const size_t size) {
  for (int i = 0; i != size; ++i) {
    for (int j = i + 1; j != size; ++j) {
      if (i != j) {
        assert(arr[i] != arr[j]);
      }
    }
  }
}

enum Verbosity { ROOT_FIND_VERBOSITY_VERBOSE, ROOT_FIND_VERBOSITY_SILENT };

size_t find_root(const size_t *forest, const size_t size, const size_t start,
                 enum Verbosity verbosity) {
  size_t parent = start;
  size_t index = 0;
  if (verbosity == ROOT_FIND_VERBOSITY_VERBOSE) {
    printf("%zu", parent);
  }
  while (parent < size) {
    index = parent;
    parent = forest[index];
    if (verbosity == ROOT_FIND_VERBOSITY_VERBOSE) {
      printf("-> %zu", parent);
    }
  }
  if (verbosity == ROOT_FIND_VERBOSITY_VERBOSE) {
    printf("\n");
  }
  return index;
}

int main() {
  srand((unsigned)time(NULL));

  const size_t size = 5;
  assert(forest_malloc(5));

  const size_t *singleton_forest = forest_init_singleton(size);
  for (int i = 0; i != size; ++i) {
    assert(singleton_forest[i] == size);
  }

  const size_t perm_sz = 10;
  const size_t *perm = get_permutation(perm_sz);
  assert_is_permutation(perm, perm_sz);

  const size_t random_forest_sz = 42;
  const size_t num_roots = 4;
  const size_t *random_forest = forest_init_random(random_forest_sz, num_roots);
  print_arr(random_forest, random_forest_sz, "random forest");
  const size_t root =
      find_root(random_forest, random_forest_sz, get_random(random_forest_sz),
                ROOT_FIND_VERBOSITY_VERBOSE);
  printf("root is: %zu\n", root);
}
