#include <iostream>

class RMTS {
public:
  RMTS();
  ~RMTS();
  void setup(int nx, double * lower, double * upper);
  void compute_ext_dist(int n, int nterm, double * x, double * dx);
  void compute_quadrature_points(int n, int * nelem_list, double * x);

private:
  int nx;
  double * lower;
  double * upper;
};
