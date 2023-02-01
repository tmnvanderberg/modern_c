#include <assert.h>
#include <math.h>
#include <stdio.h>

#define ERR_LIM 0.00001

double derivative(double (*fun)(double), double x) {
  double delta = 1.0;
  double dfdx = 0.0;
  double dfdx_prev = 1;
  while (fabs(dfdx_prev - dfdx) > ERR_LIM) {
    dfdx_prev = dfdx;
    const double df = fun(x + delta) - fun(x - delta);
    const double dx = 2.0 * delta;
    dfdx = df / dx;
    delta /= 2.0;
  }
  return dfdx;
}

double func(double x) { return x * x; }

double func_symb_der(double x) { return 2 * x; }

int main() {
  const double x = 4.3;
  assert(fabs(derivative(&func, x) - func_symb_der(x)) <= ERR_LIM);
}
