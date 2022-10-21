#include <iostream>
#include <fstream>
#include <vector>

void saveToFile(const std::string &f, const double &a, const double &b)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b;
  file.close();
}

void eulerSchema()
{
  double y0 = 1.0;
  double lambda = -1.0;
  double t_start = 0.0;
  double t_end = 5.0;
  double time_steps[] = {0.01, 0.1, 1.0};

  for (const auto &ts : time_steps)
  {
    std::string filename = "euler" + std::to_string(ts) + ".csv";
    std::cout << filename << "\n";
    int n = (t_end - t_start) / ts;

    std::vector<double> y;
    y.push_back(1.0);

    for (int i = 0; i < n; i++)
    {
      double res = y[i] + ts * lambda * y[i];
      y.push_back(res);
      saveToFile(filename, i, res);
    }
  }
}

int main()
{
  std::cout << "asda";
  eulerSchema();
}