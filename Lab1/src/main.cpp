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

void eulerMethod()
{
  double y0 = 1.0;
  double lambda = -1.0;
  double t_start = 0.0;
  double t_end = 5.0;
  double time_stamps[] = {0.01, 0.1, 1.0};

  double res{};

  for (const auto &dt : time_stamps)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dt;
    std::string filename = "euler" + stream.str() + ".csv";
    clearFile(filename);
    std::string filenameDiffrence = "euler" + stream.str() + "_diff.csv";
    clearFile(filenameDiffrence);

    int n = (t_end - t_start) / dt;

    std::vector<double> y{};
    y.push_back(1.0);

    for (int i = 0; i < n; i++)
    {
      res = y[i] + dt * lambda * y[i];
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

void rk2Method()
{

  double y0 = 1.0;
  double lambda = -1.0;
  double t_start = 0.0;
  double t_end = 5.0;
  double time_stamps[] = {0.01, 0.1, 1.0};

  for (const auto &dt : time_stamps)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dt;
    std::string filename = "rk2" + stream.str() + ".csv";
    clearFile(filename);

    std::string filenameDiffrence = "rk2" + stream.str() + "_diff.csv";
    clearFile(filenameDiffrence);

    std::vector<double> y{};
    y.push_back(1.0);
    int n = (t_end - t_start) / dt;
    double res{}, k1{}, k2{};
    for (int i = 0; i < n; i++)
    {
      k1 = lambda * y[i];
      k2 = lambda * (y[i] + dt * k1);
      res = y[i] + dt / 2.0 * (k1 + k2);

      y.push_back(res);
      saveToFile(filename, static_cast<double>(i) * dt, res);

      saveToFile(filenameDiffrence, static_cast<double>(i) * dt, res - analticValue(static_cast<double>(i) * dt, lambda));
    }
  }
  double dt = 0.01;
  int n = (t_end - t_start) / dt;
  clearFile("rk2_analytic.csv");
  for (int i = 0; i < n; i++)
  {
    saveToFile("rk2_analytic.csv", static_cast<double>(i) * dt, analticValue(static_cast<double>(i) * dt, lambda));
  }
}

int main()
{
  eulerMethod();
  rk2Method();
  return 0;
}