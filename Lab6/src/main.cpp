#include "fileUtils.h"
#include "vectorUtils.h"
#include "mgmres.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>

double rho(const double &x, const double &y)
{
  return 0.0;
}

void poissonEqationAlgebraic(const int &nx, const int &ny, const double &delta, const std::vector<double> &epsilon, const std::vector<double> &VBorder)
{
  const int N = (nx + 1) * (ny + 1);
  double *a = new double[N * 5];
  int *ja = new int[N * 5];
  int *ia = new int[N + 1];
  double *b = new double[N];
  double *V = new double[N];
  for (int i = 0; i < N + 1; i++)
  {
    ia[i] = -1;
  }

  delete a;
  delete ja;
  delete ia;
  delete b;
  delete V;
}

int main()
{
  const int nx = 4, ny = 4;

  const double delta = 0.1,
               epsilon1 = 1.0,
               epsilon2 = 1.0,
               V1 = 10.0,
               V2 = -10.0,
               V3 = 10.0,
               V4 = -10.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4});
  return 0;
}