#include "fileUtils.h"
#include "vectorUtils.h"
#include "mgmres.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>

const int nx = 50, ny = 50;

const double delta = 0.1,
             epsilon1 = 1.0,
             epsilon2 = 1.0,
             V1 = 10.0,
             V2 = -10.0,
             V3 = 10.0,
             V4 = -10.0;

double pow(const double &a)
{
  return a * a;
}

double rho()
{
  return 0.0;
}

// double rho1(const double &x, const double &y)
// {
//   return std::exp(-pow(x-0.25*)/());
// }

int getJFromL(const int &l, const int &nx)
{
  return floor(l / (nx + 1));
}

int getIFromL(const int &l, const int &nx)
{
  return l - getJFromL(l, nx) * (nx + 1);
}

double getEpsilon(const int &l, const int &nx)
{
  if (getIFromL(l, nx) <= nx / 2)
    return epsilon1;
  return epsilon2;
}

double a_l_l_mnx_m1(const int &l, const double &delta, const int &nx)
{
  return getEpsilon(l, nx) / pow(delta);
}

double a_l_l_m1(const int &l, const double &delta, const int &nx)
{
  return getEpsilon(l, nx) / pow(delta);
}

double a_l_l(const int &l, const double &delta, const int &nx)
{
  return -(2 * getEpsilon(l, nx) + getEpsilon(l + 1, nx) + getEpsilon(l + nx + 1, nx)) / pow(delta);
}

double a_l_l_p1(const int &l, const double &delta, const int &nx)
{
  return getEpsilon(l + 1, nx) / pow(delta);
}

double a_l_l_pnx_p1(const int &l, const double &delta, const int &nx)
{
  return getEpsilon(l + nx + 1, nx) / pow(delta);
}

void fillMatrices(const int &nx, const int &ny, const int &N, const std::vector<double> &VBorder, double *a, int *ia, int *ja, double *b)
{
  int k = -1;

  bool border;
  int i,
      j;
  double vb;

  std::string filename1 = "matrixA_fill.dat";
  std::string filename2 = "vectorB_fill.dat";
  clearFile(filename1);
  clearFile(filename2);

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

    b[l] = -(rho() + rho());

    if (border)
      b[l] = vb;

    ia[l] = -1;

    if (l - nx - 1 > 0 && border == false)
    {
      k++;
      if (ia[l] < 0)
        ia[l] = k;
      a[k] = a_l_l_mnx_m1(l, delta, nx);
      ja[k] = l - nx - 1;
    }

    if (l - 1 >= 0 && border == false)
    {
      k++;
      if (ia[l] < 0)
        ia[l] = k;
      a[k] = a_l_l_m1(l, delta, nx);
      ja[k] = l - 1;
    }

    k++;
    if (ia[l] < 0)
      ia[l] = k;
    if (border == false)
      a[k] = a_l_l(l, delta, nx);
    else
      a[k] = 1;
    ja[k] = l;

    if (l < N && border == false)
    {
      k++;
      a[k] = a_l_l_p1(l, delta, nx);
      ja[k] = l + 1;
    }

    if (l < N - nx - 1 && border == false)
    {
      k++;
      a[k] = a_l_l_pnx_p1(l, delta, nx);
      ja[k] = l + nx + 1;
    }

    saveToFile(filename1, l, getIFromL(l, nx), getJFromL(l, nx), a[l]);
    saveToFile(filename2, l, getIFromL(l, nx), getJFromL(l, nx), b[l]);
  }
  ia[N] = k + 1;
}

void saveVectorToFile(const std::string &f, const double *V, const int &N, const int &nx)
{
  clearFile(f);
  for (int l = 0; l < N; l++)
  {
    saveToFile(f, getIFromL(l, nx), getJFromL(l, nx), V[l]);
    if (getIFromL(l, nx) == nx)
      addEndLineToFile(f);
  }
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

  fillMatrices(nx, ny, N, VBorder, a, ia, ja, b);

  pmgmres_ilu_cr(N, ia[N], ia, ja, a, V, b, 500, 500, 1e-8, 1e-8);

  saveVectorToFile("V_50.dat", V, N, nx);

  delete a;
  delete ja;
  delete ia;
  delete b;
  delete V;
}

int main()
{

  poissonEqationAlgebraic(50, 50, delta, {epsilon1, epsilon2}, {V1, V2, V3, V4});
  return 0;
}