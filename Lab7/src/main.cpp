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

double calcY(const int &i, const double &delta)
{
  return static_cast<double>(i) * delta;
}

double calcQOut(const double &qin, const int &nx, const int &ny, const int &j1, const int &i1, const double &delta)
{
  return qin * ((cube(calcY(ny, delta)) - cube(calcY(j1, delta)) - 3.0 * calcY(j1, delta) * square(calcY(ny, delta)) +
                 3.0 * square(calcY(j1, delta)) * calcY(ny, delta)) /
                cube(calcY(ny, delta)));
}

void borderPsiA(double **psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  for (int j = j1; j <= ny; j++)
    psi[0][j] = (qin / (2.0 * mi)) *
                ((cube(calcY(j, delta)) / 3.0) -
                 ((square(calcY(j, delta)) / 2.0) * (calcY(j1, delta) + calcY(ny, delta))) + (calcY(j, delta) * calcY(j1, delta) * calcY(ny, delta)));
}

void borderPsiB(double **psi, const int &nx, const int &ny, const int &i1)
{
  for (int i = 1; i <= nx - 1; i++)
    psi[i][ny] = psi[0][ny];
}

void borderPsiC(double **psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  const double qout = calcQOut(qin, nx, ny, j1, i1, delta);
  for (int j = 0; j <= ny; j++)
    psi[nx][j] = ((qout / (2.0 * mi)) *
                  (cube(calcY(j, delta)) / 3.0 -
                   ((square(calcY(j, delta)) / 2.0) *
                    calcY(ny, delta)))) +
                 ((qin * square(calcY(j1, delta)) *
                   (-calcY(j1, delta) + 3.0 * calcY(ny, delta))) /
                  (12.0 * mi));
}

void borderPsiD(double **psi, const int &nx, const int &i1, const int &j1)
{
  for (int i = i1; i <= nx - 1; i++)
    psi[i][0] = psi[0][j1];
}

void borderPsiE(double **psi, const int &nx, const int &i1, const int &j1)
{
  for (int j = 1; j <= j1; j++)
    psi[i1][j] = psi[0][j1];
}

void borderPsiF(double **psi, const int &nx, const int &i1, const int &j1)
{
  for (int i = 1; i <= i1; i++)
    psi[i][j1] = psi[0][j1];
}

void setBorderPsi(double **psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  borderPsiA(psi, nx, ny, i1, j1, delta, mi, qin);
  borderPsiC(psi, nx, ny, i1, j1, delta, mi, qin);
  borderPsiB(psi, nx, ny, i1);
  borderPsiD(psi, nx, i1, j1);
  borderPsiE(psi, nx, i1, j1);
  borderPsiF(psi, nx, i1, j1);
}

void borderDzetaA(double **dzeta, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  for (int j = j1; j <= ny; j++)
    dzeta[0][j] = (qin / (2.0 * mi)) * (2.0 * calcY(j, delta) - calcY(j1, delta) - calcY(ny, delta));
}

void borderDzetaB(double **dzeta, double **const psi, const int &nx, const int &ny, const double &delta)
{
  for (int i = 1; i <= nx - 1; i++)
    dzeta[i][ny] = (2.0 / (square(delta))) * (psi[i][ny - 1] - psi[i][ny]);
}

void borderDzetaC(double **dzeta, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  const double qout = calcQOut(qin, nx, ny, j1, i1, delta);
  for (int j = 0; j <= ny; j++)
    dzeta[nx][j] = (qout / (2.0 * mi)) * (2.0 * calcY(j, delta) - calcY(ny, delta));
}

void borderDzetaD(double **dzeta, double **const psi, const int &nx, const int &ny, const int &i1, const double &delta)
{
  for (int i = i1 + 1; i <= nx - 1; i++)
    dzeta[i][0] = (2.0 / (square(delta))) * (psi[i][1] - psi[i][0]);
}

void borderDzetaE(double **dzeta, double **const psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta)
{
  for (int j = 1; j <= j1 - 1; j++)
    dzeta[i1][j] = (2.0 / (square(delta))) * (psi[i1 + 1][j] - psi[i1][j]);
}

void borderDzetaF(double **dzeta, double **const psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta)
{
  for (int i = 1; i <= i1; i++)
    dzeta[i][j1] = (2.0 / (square(delta))) * (psi[i][j1 + 1] - psi[i][j1]);
}

void setBorderDzeta(double **dzeta, double **const psi, const int &nx, const int &ny, const int &i1, const int &j1, const double &delta, const double &mi, const double &qin)
{
  borderDzetaA(dzeta, nx, ny, i1, j1, delta, mi, qin);
  borderDzetaC(dzeta, nx, ny, i1, j1, delta, mi, qin);
  borderDzetaB(dzeta, psi, nx, ny, delta);
  borderDzetaD(dzeta, psi, nx, ny, i1, delta);
  borderDzetaE(dzeta, psi, nx, ny, i1, j1, delta);
  borderDzetaF(dzeta, psi, nx, ny, i1, j1, delta);
  dzeta[i1][j1] = 0.5 * (dzeta[i1 - 1][j1] + dzeta[i1][j1 - 1]);
}

double errorControl(double **const psi, double **const dzeta, const int &nx, const int &j1, const double &delta)
{
  double s = 0.0;
  const int j2 = j1 + 2;
  for (int i = 1; i <= nx - 1; i++)
    s += (psi[i + 1][j2] + psi[i - 1][j2] + psi[i][j2 + 1] + psi[i][j2 - 1] - 4.0 * psi[i][j2] - square(delta) * dzeta[i][j2]);
  return s;
}

double calcPsi(double **psi, double **dzeta, const double &delta, const int &i, const int &j)
{
  return 0.25 * (psi[i + 1][j] + psi[i - 1][j] + psi[i][j + 1] + psi[i][j - 1] - square(delta) * dzeta[i][j]);
}

double calcDzeta(double **psi, double **dzeta, const double &omega, const double &rho, const double &mi, const int &i, const int &j)
{
  return 0.25 * (dzeta[i + 1][j] + dzeta[i - 1][j] + dzeta[i][j + 1] + dzeta[i][j - 1]) -
         ((omega) * (rho / (16.0 * mi))) *
             ((psi[i][j + 1] - psi[i][j - 1]) * (dzeta[i + 1][j] - dzeta[i - 1][j]) -
              (psi[i + 1][j] - psi[i - 1][j]) * (dzeta[i][j + 1] - dzeta[i][j - 1]));
}

void calcUxy(double **u, double **psi, const int &nx, const int &ny, const double &delta)
{

  for (int i = 1; i <= nx - 1; i++)
  {
    for (int j = 1; j <= ny - 1; j++)
      u[i][j] = (psi[i][j + 1] - psi[i][j]) / delta;
  }
}

void calcVxy(double **v, double **psi, const int &nx, const int &ny, const double &delta)
{

  for (int i = 1; i <= nx - 1; i++)
  {
    for (int j = 1; j <= ny - 1; j++)
      v[i][j] = -(psi[i + 1][j] - psi[i][j]) / delta;
  }
}

void relaxation(double **psi, double **dzeta, const int &nx, const int &ny, const int &i1, const int &j1, const int &IT_MAX,
                const double &delta, const double &rho, const double &mi, const double &qin)
{
  for (int i = 0; i <= nx; i++)
  {
    for (int j = 0; j <= ny; j++)
    {
      psi[i][j] = 0.0;
      dzeta[i][j] = 0.0;
    }
  }

  double *y = new double[ny + 1];
  for (unsigned j = 0u; j <= ny; j++)
    y[j] = calcY(j, delta);

  setBorderPsi(psi, nx, ny, i1, j1, delta, mi, qin);

  double omega = 0.0;
  for (int it = 1; it <= IT_MAX; it++)
  {
    if (it < 2000)
      omega = 0.0;
    else
      omega = 1.0;

    for (int i = 1; i <= nx - 1; i++)
    {
      for (int j = 1; j <= ny - 1; j++)
      {
        if (i > i1 || j > j1)
        {
          psi[i][j] = calcPsi(psi, dzeta, delta, i, j);
          dzeta[i][j] = calcDzeta(psi, dzeta, omega, rho, mi, i, j);
        }
      }
    }
    setBorderDzeta(dzeta, psi, nx, ny, i1, j1, delta, mi, qin);
    // errorControl(psi, dzeta, nx, j1, delta);
  }
}

void navierStokesEquation(
    const int &nx, const int &ny, const int &i1, const int &j1, const int &IT_MAX,
    const double &delta, const double &rho, const double &mi, const double &qin,
    const std::string &filename)
{
  double **psi = new double *[nx + 1];
  double **dzeta = new double *[nx + 1];
  double **u_xy = new double *[nx + 1];
  double **v_xy = new double *[nx + 1];
  for (int i = 0; i <= nx; i++)
  {
    psi[i] = new double[ny + 1];
    dzeta[i] = new double[ny + 1];
    u_xy[i] = new double[ny + 1];
    v_xy[i] = new double[ny + 1];
  }

  relaxation(psi, dzeta, nx, ny, i1, j1, IT_MAX, delta, rho, mi, qin);

  calcUxy(u_xy, psi, nx, ny, delta);
  calcVxy(v_xy, psi, nx, ny, delta);

  for (int i = 0; i <= nx; i++)
  {
    for (int j = 0; j <= ny; j++)
      saveToFile(filename, {i * delta, j * delta, psi[i][j], dzeta[i][j], u_xy[i][j], v_xy[i][j]});
    addEndLineToFile(filename);
  }

  for (int i = 0; i <= nx; i++)
  {
    delete[] psi[i];
    delete[] dzeta[i];
    delete[] u_xy[i];
    delete[] v_xy[i];
  }
  delete[] u_xy;
  delete[] v_xy;
  delete[] psi;
  delete[] dzeta;
}

int main()
{
  auto begin = std::chrono::high_resolution_clock::now();
  const int nx = 200, ny = 90,
            i1 = 50, j1 = 55,
            IT_MAX = 20000;

  const double delta = 0.01,
               rho = 1.0,
               mi = 1.0;

  // 4
  double qin = -1000.0;
  navierStokesEquation(nx, ny, i1, j1, IT_MAX, delta, rho, mi, qin, "wyn.dat");

  // 5
  qin = -4000.0;
  navierStokesEquation(nx, ny, i1, j1, IT_MAX, delta, rho, mi, qin, "wyn_Qm4000.dat");

  // 6
  qin = 4000.0;
  navierStokesEquation(nx, ny, i1, j1, IT_MAX, delta, rho, mi, qin, "wyn_Q4000.dat");

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
  std::cout << "Time elapsed: " << elapsed.count() << "sec\n";

  return 0;
}