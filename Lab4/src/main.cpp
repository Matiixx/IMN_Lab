#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>

void clearFile(const std::string &f)
{
  std::ofstream file;
  file.open(f, std::ofstream::out | std::ofstream::trunc);
  std::cout << f << "\n";
  file.close();
}

void saveToFile(const std::string &f, const double &a, const double &b)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << "\n";
  file.close();
}

void saveToFile(const std::string &f, const double &a, const double &b, const double &c, const double &d)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << " " << c << " " << d << "\n";
  file.close();
}

const double epsilon = 1,
             delta = 0.1,
             nx = 150,
             ny = 100,
             V1 = 10,
             V2 = 0,
             x_max = delta * nx,
             y_max = delta * ny,
             sigma_x = 0.1 * x_max,
             sigma_y = 0.1 * y_max;

double rho_1(const double &x, const double &y)
{
  return std::exp(-((x - 0.35 * x_max) * (x - 0.35 * x_max)) / (sigma_x * sigma_x) - ((y - 0.5 * y_max) * (y - 0.5 * y_max)) / (sigma_y * sigma_y));
}

double rho_2(const double &x, const double &y)
{
  return -std::exp(-((x - 0.65 * x_max) * (x - 0.35 * x_max)) / (sigma_x * sigma_x) - ((y - 0.5 * y_max) * (y - 0.5 * y_max)) / (sigma_y * sigma_y));
}

double rho(const double &x, const double &y)
{
  return rho_1(delta * x, delta * y) + rho_2(delta * x, delta * y);
}

void initVector(std::vector<std::vector<double>> &vec)
{
  for (int i = 0; i <= nx; i++)
  {
    std::vector<double> tmp;
    for (int j = 0; j <= ny; j++)
      tmp.push_back(0.0);
    vec.push_back(tmp);
  }
}

void printVector(std::vector<std::vector<double>> &vec)
{
  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
      std::cout << vec[i][j] << " ";
  }
}

int main()
{
  globalRelaxation();
  return 0;
}