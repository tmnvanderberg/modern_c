#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool equal_digits(const double a, const double b, const int digits) {
  const double fac = 10 * digits;
  return fabs(a - b) < (1 / pow(10, digits));
}

double pi(const int digits) {
  double pi = 0;
  for (int n = 0; n != pow(10, digits); ++n) {
    const double incr = 4.0 / (2.0 * n + 1.0);
    pi += (n % 2 == 0) ? incr : -incr;
  }
  return pi;
}

int main() {
  assert(equal_digits(3.145, 3.1456999, 3));
  assert(!equal_digits(3.145, 3.1436999, 4));
  assert(equal_digits(3.145, 3.1436999, 2));

  assert(equal_digits(pi(3), 3.1415, 3));
  assert(equal_digits(pi(6), 3.14159265, 6));
  assert(!equal_digits(pi(6), 3.14159364, 6));
  assert(!equal_digits(pi(6), 3.14159265, 7));
  assert(!equal_digits(pi(5), 3.14159265, 6));
}
