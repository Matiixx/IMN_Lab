#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>

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

double analticValue(double l, double t)
{
  return std::exp(l * t);
}

void eulerSchema()
{
  double y0 = 1.0;
  double lambda = -1.0;
  double t_start = 0.0;
  double t_end = 5.0;
  double time_steps[] = {0.01, 0.1, 1.0};

  for (const auto &dt : time_steps)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dt;
    std::string filename = "euler" + stream.str() + ".csv";
    clearFile(filename);
    std::string filenameDiffrence = "euler" + stream.str() + "_diff.csv";
    clearFile(filenameDiffrence);

    int n = (t_end - t_start) / dt;

    std::vector<double> y;
    y.push_back(1.0);

    for (int i = 0; i < n; i++)
    {
      double res = y[i] + dt * lambda * y[i];
      y.push_back(res);
      saveToFile(filename, static_cast<double>(i) * dt, res);

      saveToFile(filenameDiffrence, static_cast<double>(i) * dt, res - analticValue(static_cast<double>(i) * dt, lambda));
    }
  }
  clearFile("euler_analytic.csv");
  double dt = 0.01;
  int n = (t_end - t_start) / dt;

  for (int i = 0; i < n; i++)
  {
    saveToFile("euler_analytic.csv", static_cast<double>(i) * dt, analticValue(static_cast<double>(i) * dt, lambda));
  }
}

int main()
{
  eulerSchema();
  return 0;
}