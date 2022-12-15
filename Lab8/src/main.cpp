#include "fileUtils.h"
#include "vectorUtils.h"
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

double cube(const double &a)
{
  return a * a * a;
}

void calculate_v_x(double **psi, double **vx, const int &nx, const int &ny, const int &i1, const int &i2, const int &j1, const double &delta)
{
  for (int i = 1; i < nx; i++)
    for (int j = 1; j < ny; j++)
      vx[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2.0 * delta);

  for (int i = i1; i < i1; i++)
    for (int j = 0; j < j1; j++)
      vx[i][j] = 0.0;

  for (int i = 1; i < nx; i++)
    vx[i][0] = 0.0;

  for (int j = 0; j <= ny; j++)
  {
    vx[0][j] = vx[1][j];
    vx[nx][j] = vx[nx - 1][j];
  }
}

void calculate_v_y(double **psi, double **vy, const int &nx, const int &ny, const int &i1, const int &i2, const int &j1, const double &delta)
{
  for (int i = 1; i < nx; i++)
    for (int j = 1; j < ny; j++)
      vy[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2.0 * delta);

  for (int i = i1; i < i2; i++)
    for (int j = 0; j < j1; j++)
      vy[i][j] = 0.0;

  for (int i = 1; i < nx; i++)
    vy[i][ny] = 0.0;
}

double vectorLength(const double &a, const double &b)
{
  return sqrt(square(a) + square(b));
}

double calc_v_max(double **vx, double **vy, const int &nx, const int &ny)
{
  double v_max = 0.0;
  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
      if (vectorLength(vx[i][j], vy[i][j]) > v_max)
        v_max = vectorLength(vx[i][j], vy[i][j]);
  return v_max;
}

double calc_delta_t(double **vx, double **vy, const int &nx, const int &ny, const double &delta)
{
  return delta / (4.0 * calc_v_max(vx, vy, nx, ny));
}

double calcU(const int &x, const int &y, const double &sigma, const double &xa, const double &ya, const double &delta)
{
  return 1.0 / (2 * M_PI * square(sigma)) * std::exp(-(square((delta * x) - xa) + square((delta * y) - ya)) / (2.0 * square(sigma)));
}

void initU(double **u, const int &nx, const int &ny, const double &sigma, const double &xa, const double &ya, const double &delta)
{

  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
      u[i][j] = calcU(i, j, sigma, xa, ya, delta);
}

void copyVector(double **a, double **b, const int &nx, const int &ny)
{
  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
      a[i][j] = b[i][j];
}

double calcCrankNicolson(const int &i, const int &j, double **u, double **u_next, double **vx, double **vy, const double &delta, const double &delta_t, const double &D, const int &nx)
{
  return (1.0 / (1.0 + (2.0 * D * delta_t) / square(delta))) *
         (u[i][j] - delta_t / 2.0 * vx[i][j] * (((u[i + 1][j] - u[i - 1][j]) / (2.0 * delta)) + ((u_next[i + 1][j] - u_next[i - 1][j]) / (2.0 * delta))) - delta_t / 2.0 * vy[i][j] * (((u[i][j + 1] - u[i][j - 1]) / (2.0 * delta)) + ((u_next[i][j + 1] - u_next[i][j - 1]) / (2.0 * delta))) + delta_t / 2.0 * D * ((u[i + 1][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] - 4.0 * u[i][j]) / (square(delta)) + (u_next[i + 1][j] + u_next[i - 1][j] + u_next[i][j + 1] + u_next[i][j - 1]) / (square(delta))));
}

void crankNicolson(double **u, double **u_next, double **vx, double **vy, const int &nx, const int &ny, const double &D, const double &delta, const double &delta_t, const int &i1, const int &i2, const int &j1)
{
  copyVector(u_next, u, nx, ny);
  for (int k = 1; k <= 20; k++)
  {
    for (int i = 0; i <= nx; i++)
    {
      for (int j = 1; j < ny; j++)
      {
        if ((i >= i1) && (i <= i2) && (j <= j1))
          continue;
        else if (i == 0u)
          u_next[i][j] = (1.0 / (1.0 + 2.0 * D * delta_t / square(delta))) * (u[i][j] - delta_t / 2.0 * vx[i][j] * (((u[i + 1][j] - u[nx][j]) / (2.0 * delta)) + (u_next[i + 1][j] - u_next[nx][j]) / (2.0 * delta)) - 0.5 * delta_t * vy[i][j] * (((u[i][j + 1] - u[i][j - 1]) / (2.0 * delta)) + (u_next[i][j + 1] - u_next[i][j - 1]) / (2.0 * delta)) + delta_t / 2.0 * D * (((u[i + 1][j] + u[nx][j] + u[i][j + 1] + u[i][j - 1] - 4.0 * u[i][j]) / square(delta)) + (u_next[i + 1][j] + u_next[nx][j] + u_next[i][j + 1] + u_next[i][j - 1]) / square(delta)));
        else if (i == nx)
          u_next[i][j] = (1.0 / (1.0 + 2.0 * D * delta_t / square(delta))) * (u[i][j] - delta_t / 2.0 * vx[i][j] * (((u[0][j] - u[i - 1][j]) / (2.0 * delta)) + (u_next[0][j] - u_next[i - 1][j]) / (2.0 * delta)) - 0.5 * delta_t * vy[i][j] * (((u[i][j + 1] - u[i][j - 1]) / (2.0 * delta)) + (u_next[i][j + 1] - u_next[i][j - 1]) / (2.0 * delta)) + delta_t / 2.0 * D * (((u[0][j] + u[i - 1][j] + u[i][j + 1] + u[i][j - 1] - 4.0 * u[i][j]) / square(delta)) + (u_next[0][j] + u_next[i - 1][j] + u_next[i][j + 1] + u_next[i][j - 1]) / square(delta)));
        else
          u_next[i][j] = calcCrankNicolson(i, j, u, u_next, vx, vy, delta, delta_t, D, nx);
      }
    }
  }
}

double calcC(double **u, const int &nx, const int &ny, const double &delta)
{
  double s = 0.0;
  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
      s += (u[i][j] * square(delta));
  return s;
}

double calcXsr(double **u, const int &nx, const int &ny, const double &delta)
{
  double s = 0.0;
  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
      s += (i * delta * u[i][j] * square(delta));
  return s;
}

void advectionDiffusionEquation(const int &nx, const int &ny, const int &i1, const int &i2, const int &j1, const int &IT_MAX,
                                const double &delta, const double &sigma, const double &xa, const double &ya, const double &D,
                                const std::string &psiFilename)
{
  double **psi = new double *[nx + 1];
  double **vx = new double *[nx + 1];
  double **vy = new double *[nx + 1];
  double **u = new double *[nx + 1];
  double **u_next = new double *[nx + 1];
  for (int i = 0; i <= nx; i++)
  {
    psi[i] = new double[ny + 1];
    vx[i] = new double[ny + 1];
    vy[i] = new double[ny + 1];
    u[i] = new double[ny + 1];
    u_next[i] = new double[ny + 1];
  }

  loadFromFile(psiFilename, psi, nx, ny);

  calculate_v_x(psi, vx, nx, ny, i1, i2, j1, delta);
  calculate_v_y(psi, vy, nx, ny, i1, i2, j1, delta);

  const double delta_t = calc_delta_t(vx, vy, nx, ny, delta);
  std::cout << "delta_t: " << delta_t << std::endl;
  if (D == 0.0)
  {
    clearFile("v.dat");
    for (int i = 0; i <= nx; i++)
    {
      for (int j = 0; j <= ny; j++)
        saveToFile("v.dat", {i * delta, j * delta, vx[i][j], vy[i][j]});
      addEndLineToFile("v.dat");
    }
  }
  initU(u, nx, ny, sigma, xa, ya, delta);

  std::stringstream ss;
  ss << "c_xsr_" << D << ".dat";
  std::string filename = ss.str();
  clearFile(filename);

  int arr[] = {
      1 * IT_MAX / 5,
      2 * IT_MAX / 5,
      3 * IT_MAX / 5,
      4 * IT_MAX / 5,
      5 * IT_MAX / 5,
  };
  int *k = arr;

  for (int i = 1; i <= IT_MAX; i++)
  {
    std::cout << "\r" << std::flush << "D: " << D << " Iteration: " << i;
    crankNicolson(u, u_next, vx, vy, nx, ny, D, delta, delta_t, i1, i2, j1);
    copyVector(u, u_next, nx, ny);
    saveToFile(filename, {i * delta_t, calcC(u_next, nx, ny, delta), calcXsr(u_next, nx, ny, delta)});

    if (*k == i)
    {
      std::cout << "\r" << std::flush << "k: " << *k << " t: " << i * delta_t << "\n";
      std::stringstream ss2;
      ss2 << "map_u_" << i << "_" << D << ".dat";
      std::string fileMap = ss2.str();
      clearFile(fileMap);

      for (int i = 0; i <= nx; i++)
      {
        for (int j = 0; j <= ny; j++)
          saveToFile(fileMap, {(double)i, (double)j, u[i][j] < 0.0 ? 0.0 : u[i][j]});
        addEndLineToFile(fileMap);
      }
      k++;
    }
  }
  std::cout << "\n";

  for (int i = 0; i <= nx; i++)
  {
    delete psi[i];
    delete vx[i];
    delete vy[i];
    delete u[i];
    delete u_next[i];
  }
  delete[] psi;
  delete[] vx;
  delete[] vy;
  delete[] u;
  delete[] u_next;
}

int main()
{
  auto begin = std::chrono::high_resolution_clock::now();
  const int nx = 400, ny = 90,
            i1 = 200, i2 = 210,
            j1 = 50, IT_MAX = 10000;

  const double delta = 0.01,
               sigma = delta * 10,
               xa = 0.45, ya = 0.45;
  double D = 0.0;

  advectionDiffusionEquation(nx, ny, i1, i2, j1, IT_MAX, delta, sigma, xa, ya, D, "psi.dat");
  D = 0.1;
  advectionDiffusionEquation(nx, ny, i1, i2, j1, IT_MAX, delta, sigma, xa, ya, D, "psi.dat");

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
  std::cout << "\nTime elapsed: " << elapsed.count() << "sec\n";

  return 0;
}