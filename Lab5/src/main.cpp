#include "fileUtils.h"
#include "vectorUtils.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>

// void clearFile(const std::string &f)
// {
//   std::ofstream file;
//   file.open(f, std::ofstream::out | std::ofstream::trunc);
//   std::cout << f << "\n";
//   file.close();
// }

// void saveToFile(const std::string &f, const double &a, const double &b)
// {
//   std::fstream file;
//   file.open(f, std::ios::app);
//   file << a << " " << b << "\n";
//   file.close();
// }

// void saveToFile(const std::string &f, const double &a, const double &b, const double &c)
// {
//   std::fstream file;
//   file.open(f, std::ios::app);
//   file << a << " " << b << " " << c << "\n";
//   file.close();
// }

// void saveToFile(const std::string &f, const double &a, const double &b, const double &c, const double &d)
// {
//   std::fstream file;
//   file.open(f, std::ios::app);
//   file << a << " " << b << " " << c << " " << d << "\n";
//   file.close();
// }

// void initVector(std::vector<std::vector<double>> &vec, const double &v = 0.0)
// {
//   for (int i = 0; i <= nx; i++)
//   {
//     std::vector<double> tmp;
//     for (int j = 0; j <= ny; j++)
//       tmp.push_back(v);
//     vec.push_back(tmp);
//   }
// }

// void printVector(std::vector<std::vector<double>> &vec)
// {
//   for (int i = 0; i < nx; i++)
//   {
//     for (int j = 0; j < ny; j++)
//       std::cout << vec[i][j] << " ";
//   }
// }

void setBorder(std::vector<std::vector<double>> &vec, const int &startX, const int &endX, const int &startY, const int &endY, const std::function<double(double)> &calc)
{
  for (int x = startX; x < endX; x++)
    for (int y = startY; y < endY; y++)
      vec[x][y] = calc(y);
}

void setBorder2(std::vector<std::vector<double>> &vec, const int &startX, const int &endX, const int &startY, const int &endY, const std::function<double(double)> &calc)
{
  for (int x = startX; x < endX; x++)
    for (int y = startY; y < endY; y++)
      vec[x][y] = calc(x);
}

void discretization(std::vector<std::vector<double>> &v, const int &nx, const int &ny, const int &k)
{
  for (int i = k; i <= nx - k; i += k)
    for (int j = k; j <= ny - k; j += k)
      v[i][j] = 0.25 * (v[i + k][j] + v[i - k][j] + v[i][j + k] + v[i][j - k]);
}

double square(const double &a)
{
  return a * a;
}

double calcS(std::vector<std::vector<double>> &v, const int &nx, const int &ny, const double &delta, const int &k)
{
  double s{};
  const double a = (k * delta) * (k * delta) / 2.0;
  const double b = 2.0 * k * delta;
  for (int i = 0; i <= nx - k; i += k)
    for (int j = 0; j <= ny - k; j += k)
    {
      s += a * (square((v[i + k][j] - v[i][j]) / b +
                       (v[i + k][j + k] - v[i][j + k]) / b) +
                square((v[i][j + k] - v[i][j]) / b +
                       (v[i + k][j + k] - v[i + k][j]) / b));
    }
  return s;
}

void thickenMesh(std::vector<std::vector<double>> &v, const double &nx, const double &ny, const int &k)
{
  if (k != 1)
    for (int i = 0; i <= nx - k; i += k)
      for (int j = 0; j <= ny - k; j += k)
      {
        v[i + k / 2][j + k / 2] = 0.25 * (v[i][j] + v[i + k][j] + v[i][j + k] + v[i + k][j + k]);
        v[i + k][j + k / 2] = 0.5 * (v[i + k][j] + v[i + k][j + k]);
        v[i + k / 2][j + k] = 0.5 * (v[i][j + k] + v[i + k][j + k]);
        v[i + k / 2][j] = 0.5 * (v[i][j] + v[i + k][j]);
        v[i][j + k / 2] = 0.5 * (v[i][j] + v[i][j + k]);
      }
}

void mulitMeshRelaxation(const double &delta, const int &nx, const int &ny, const double &TOL, const int &startK)
{
  const double x_max = delta * nx,
               y_max = delta * ny;
  int k = startK;

  std::vector<std::vector<double>> V{};
  initVector(V, nx + 1, ny + 1, 0.0);

  // VB1
  setBorder(V, 0, 1, 0, ny + 1, [&y_max, &delta](double y)
            { return std::sin(M_PI * delta * y / y_max); });
  // VB2
  setBorder2(V, 0, nx + 1, ny, ny + 1, [&x_max, &delta](double x)
             { return -1.0 * std::sin(2 * M_PI * delta * x / x_max); });
  // VB3
  setBorder(V, nx, nx + 1, 0, ny + 1, [&y_max, &delta](double y)
            { return std::sin(M_PI * delta * y / y_max); });
  // VB4
  setBorder2(V, 0, nx + 1, 0, 1, [&x_max, &delta](double x)
             { return std::sin(2 * M_PI * delta * x / x_max); });

  int iter{};

  while (k >= 1)
  {
    double S{}, S_prev{};

    std::stringstream ss{};
    std::string filename;
    ss.str("");
    ss.clear();

    ss << "mulitmesh_S_" << k << ".dat";
    filename = ss.str();
    clearFile(filename);

    while (true)
    {
      discretization(V, nx, ny, k);

      S_prev = S;
      S = calcS(V, nx, ny, delta, k);
      // std::cout << "S: " << S << std::endl;
      saveToFile(filename, iter, S);

      if (std::fabs((S - S_prev) / S_prev) < TOL)
      {
        std::cout << "k=" << k << " END AT: " << iter << "\n";
        ss.str("");
        ss.clear();
        ss << "mulitmesh_V_" << k << ".dat";
        filename = ss.str();
        saveVectorToFile(filename, V, nx + 1, ny + 1, delta, k);
        break;
      }
      iter++;
    }
    if (k != 1)
    {
      thickenMesh(V, nx + 1, ny + 1, k);
      setBorder(V, 0, 1, 0, ny + 1, [&y_max, &delta](double y)
                { return std::sin(M_PI * delta * y / y_max); });
      // VB2
      setBorder2(V, 0, nx + 1, ny, ny + 1, [&x_max, &delta](double x)
                 { return -1.0 * std::sin(2 * M_PI * delta * x / x_max); });
      // VB3
      setBorder(V, nx, nx + 1, 0, ny + 1, [&y_max, &delta](double y)
                { return std::sin(M_PI * delta * y / y_max); });
      // VB4
      setBorder2(V, 0, nx + 1, 0, 1, [&x_max, &delta](double x)
                 { return std::sin(2 * M_PI * delta * x / x_max); });
    }

    k /= 2;
  }
}

int main()
{
  mulitMeshRelaxation(0.2, 128, 128, 1e-8, 16);
  return 0;
}