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

void saveToFile(const std::string &fn, const double &a, const double &b, const double &c, const double &d, const double &e, const double &f)
{
  std::fstream file;
  file.open(fn, std::ios::app);
  file << a << " " << b << " " << c << " " << d << " " << e << " " << f << "\n";
  file.close();
}

void saveVector2DToFile(const std::string &f, std::vector<std::vector<double>> &v, const int &nx, const int &ny, const double &delta, const int &k)
{
  clearFile(f);
  for (int i = 0; i <= nx; i += k)
  {
    for (int j = 0; j <= ny; j += k)
      saveToFile(f, delta * i, delta * j, v[i][j]);
    addEndLineToFile(f);
  }
}

void loadFromFile(const std::string &filename, double **array, const int &nx, const int &ny)
{
  std::fstream file;
  file.open(filename, std::ios::in);
  double a, b, c;
  for (int i = 0; i <= nx; i++)
    for (int j = 0; j <= ny; j++)
    {
      file >> a >> b >> c;
      array[i][j] = c;
    }

  file.close();
}

void addEndLineToFile(const std::string &f)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << "\n";
  file.close();
}