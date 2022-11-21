#include "fileUtils.h"

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

void saveToFile(const std::string &f, const double &a, const double &b, const double &c)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << " " << c << "\n";
  file.close();
}

void saveToFile(const std::string &f, const double &a, const double &b, const double &c, const double &d)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << " " << c << " " << d << "\n";
  file.close();
}

void saveVectorToFile(const std::string &f, std::vector<std::vector<double>> &v, const int &nx, const int &ny, const double &delta, const int &k)
{
  clearFile(f);
  for (int i = 0; i <= nx - k; i += k)
    for (int j = 0; j <= ny - k; j += k)
      saveToFile(f, delta * i, delta * j, v[i][j]);
}