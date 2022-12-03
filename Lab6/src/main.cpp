#include "fileUtils.h"
#include "vectorUtils.h"
#include "mgmres.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <chrono>
#include <math.h>
#include <sstream>

double square(const double &a)
{
  return a * a;
}

double rho_part5(const double &x, const double &y, const double &x_max, const double &y_max, const double &sigma)
{
  return 0.0;
}

double rho1(const double &x, const double &y, const double &x_max, const double &y_max, const double &sigma)
{
  return std::exp(-square(x - 0.25 * x_max) / square(sigma) - square(y - 0.5 * y_max) / square(sigma));
}

double rho2(const double &x, const double &y, const double &x_max, const double &y_max, const double &sigma)
{
  return -std::exp(-square(x - 0.75 * x_max) / square(sigma) - square(y - 0.5 * y_max) / square(sigma));
}

double rho_part6(const double &x, const double &y, const double &x_max, const double &y_max, const double &sigma)
{
  return rho1(x, y, x_max, y_max, sigma) + rho2(x, y, x_max, y_max, sigma);
}

int getJFromL(const int &l, const int &nx)
{
  return floor(l / (nx + 1));
}

int getIFromL(const int &l, const int &nx)
{
  return l - getJFromL(l, nx) * (nx + 1);
}

double getEpsilon(const int &l, const int &nx, const std::vector<double> &e)
{
  if (getIFromL(l, nx) <= nx / 2)
    return e[0];
  return e[1];
}

double a_l_l_mnx_m1(const int &l, const double &delta, const int &nx, const std::vector<double> &e)
{
  return getEpsilon(l, nx, e) / square(delta);
}

double a_l_l_m1(const int &l, const double &delta, const int &nx, const std::vector<double> &e)
{
  return getEpsilon(l, nx, e) / square(delta);
}

double a_l_l(const int &l, const double &delta, const int &nx, const std::vector<double> &e)
{
  return -(2 * getEpsilon(l, nx, e) + getEpsilon(l + 1, nx, e) + getEpsilon(l + nx + 1, nx, e)) / square(delta);
}

double a_l_l_p1(const int &l, const double &delta, const int &nx, const std::vector<double> &e)
{
  return getEpsilon(l + 1, nx, e) / square(delta);
}

double a_l_l_pnx_p1(const int &l, const double &delta, const int &nx, const std::vector<double> &e)
{
  return getEpsilon(l + nx + 1, nx, e) / square(delta);
}

void fillMatrices(const int &nx, const int &ny,
                  const int &N,
                  const double &delta,
                  const std::vector<double> &VBorder,
                  const std::vector<double> &epsilon,
                  double *a, int *ia, int *ja, double *b,
                  const double &x_max, const double &y_max,
                  const double &sigma,
                  const std::function<double(const double &, const double &, const double &, const double &, const double &)> &rho)
{
  int k = -1;

  bool border;
  int i,
      j;
  double vb;

  // std::stringstream filename1;
  // filename1 << "matrixA_fill_" << nx << ".dat";
  // std::stringstream filename2;
  // filename2 << "vectorB_fill_" << nx << ".dat";
  // clearFile(filename1.str());
  // clearFile(filename2.str());

  for (int l = 0; l < N; l++)
  {
    border = false;
    vb = 0.0;
    i = getIFromL(l, nx);
    j = getJFromL(l, nx);

    if (i == 0)
    {
      border = true;
      vb = VBorder[0];
    }
    if (j == ny)
    {
      border = true;
      vb = VBorder[1];
    }
    if (i == nx)
    {
      border = true;
      vb = VBorder[2];
    }
    if (j == 0)
    {
      border = true;
      vb = VBorder[3];
    }

    b[l] = -(rho(i * delta, j * delta, x_max, y_max, sigma));

    if (border)
      b[l] = vb;

    ia[l] = -1;

    if (l - nx - 1 > 0 && border == false)
    {
      k++;
      if (ia[l] < 0)
        ia[l] = k;
      a[k] = a_l_l_mnx_m1(l, delta, nx, epsilon);
      ja[k] = l - nx - 1;
    }

    if (l - 1 >= 0 && border == false)
    {
      k++;
      if (ia[l] < 0)
        ia[l] = k;
      a[k] = a_l_l_m1(l, delta, nx, epsilon);
      ja[k] = l - 1;
    }

    k++;
    if (ia[l] < 0)
      ia[l] = k;
    if (border == false)
      a[k] = a_l_l(l, delta, nx, epsilon);
    else
      a[k] = 1;
    ja[k] = l;

    if (l < N && border == false)
    {
      k++;
      a[k] = a_l_l_p1(l, delta, nx, epsilon);
      ja[k] = l + 1;
    }

    if (l < N - nx - 1 && border == false)
    {
      k++;
      a[k] = a_l_l_pnx_p1(l, delta, nx, epsilon);
      ja[k] = l + nx + 1;
    }

    // saveToFile(filename1.str(), l, getIFromL(l, nx), getJFromL(l, nx), a[l]);
    // saveToFile(filename2.str(), l, getIFromL(l, nx), getJFromL(l, nx), b[l]);
  }
  ia[N] = k + 1;
}

void saveVectorToFile(const std::string &f, const double *V, const int &N, const int &nx)
{
  clearFile(f);
  int i, j;
  for (int l = 0; l < N; l++)
  {
    i = getIFromL(l, nx);
    j = getJFromL(l, nx);
    saveToFile(f, i * 0.1, j * 0.1, V[l]);
    if (i == nx)
      addEndLineToFile(f);
  }
}

void poissonEqationAlgebraic(const int &nx, const int &ny,
                             const double &delta,
                             const std::vector<double> &epsilon,
                             const std::vector<double> &VBorder,
                             const double &x_max, const double &y_max,
                             const double &sigma,
                             const std::function<double(const double &, const double &, const double &, const double &, const double &)> &rho,
                             const std::string &filename)
{
  const int N = (nx + 1) * (ny + 1);
  double *a = new double[N * 5];
  int *ja = new int[N * 5];
  int *ia = new int[N + 1];
  double *b = new double[N];
  double *V = new double[N];

  fillMatrices(nx, ny, N, delta, VBorder, epsilon, a, ia, ja, b, x_max, y_max, sigma, rho);

  pmgmres_ilu_cr(N, ia[N], ia, ja, a, V, b, 500, 500, 1e-8, 1e-8);

  saveVectorToFile(filename, V, N, nx);

  delete a;
  delete ja;
  delete ia;
  delete b;
  delete V;
}

int main()
{
  auto begin = std::chrono::high_resolution_clock::now();
  // 5
  int nx = 50, ny = 50;

  double delta = 0.1,
         epsilon1 = 1.0,
         epsilon2 = 1.0,
         V1 = 10.0,
         V2 = -10.0,
         V3 = 10.0,
         V4 = -10.0,
         x_max = delta * nx,
         y_max = delta * ny,
         sigma = x_max / 10.0;

  // 5A
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part5, "V5_50.dat");
  // 5B
  nx = ny = 100;
  x_max = delta * nx;
  y_max = delta * ny;
  sigma = x_max / 10.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part5, "V5_100.dat");
  // 5C
  nx = ny = 200;
  x_max = delta * nx;
  y_max = delta * ny;
  sigma = x_max / 10.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part5, "V5_200.dat");

  // 6
  nx = ny = 100;
  x_max = delta * nx;
  y_max = delta * ny;
  sigma = x_max / 10.0;
  V1 = V2 = V3 = V4 = 0.0;

  // 6A
  epsilon1 = 1.0;
  epsilon2 = 1.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part6, "V6_1.dat");
  // 6B
  epsilon1 = 1.0;
  epsilon2 = 2.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part6, "V6_2.dat");
  // 6C
  epsilon1 = 1.0;
  epsilon2 = 10.0;
  poissonEqationAlgebraic(nx, ny, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4}, x_max, y_max, sigma, rho_part6, "V6_10.dat");

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
  std::cout << "Time elapsed: " << elapsed.count() << "sec\n";

  return 0;
}