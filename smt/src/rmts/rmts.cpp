#include "rmts.hpp"
#include "utils.cpp"
#include <assert.h>
#include <math.h>
#include <iostream>
#include <cstring>

using namespace std;

RMTS::RMTS() {
  lower = NULL;
  upper = NULL;
}

RMTS::~RMTS() {
  delete[] lower;
  delete[] upper;
}

void RMTS::setup(int nx, double * lower, double * upper) {
  this->nx = nx;
  this->lower = new double[nx];
  this->upper = new double[nx];

  memcpy(this->lower, lower, nx * sizeof(*lower));
  memcpy(this->upper, upper, nx * sizeof(*upper));
}

void RMTS::compute_ext_dist(int n, int nterm, double * x, double * dx) {
  double work;

  for (int i = 0; i < n; i++) {
    for (int ix = 0; ix < nx; ix++) {
      // compute the vector pointing from the nearest point in the domain to the current x
      work = x[i * nx + ix];
      work = max(lower[ix], work);
      work = min(upper[ix], work);
      work = x[i * nx + ix] - work;
      for (int iterm = 0; iterm < nterm; iterm++) {
        dx[i * nterm * nx + iterm * nx + ix] = work;
      }
    }
  }
}

void RMTS::compute_quadrature_points(int n, int * nelem_list, double * x) {
  int ielem_list[nx];
  double t;

  for (int i = 0; i < n; i++) {
    expand_index(nx, nelem_list, i, ielem_list);
    for (int ix = 0; ix < nx; ix++) {
      t = (1. + 2. * ielem_list[ix]) / 2. / nelem_list[ix];
      x[i * nx + ix] = lower[ix] + t * (upper[ix] - lower[ix]);
    }
  }
}
