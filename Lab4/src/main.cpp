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

int main()
{
  globalRelaxation();
  return 0;
}