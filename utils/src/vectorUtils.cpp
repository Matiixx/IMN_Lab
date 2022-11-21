#include "vectorUtils.h"

void initVector(std::vector<std::vector<double>> &vec, const int &x, const int &y, const double &v = 0.0)
{
  for (int i = 0; i <= x; i++)
  {
    std::vector<double> tmp;
    for (int j = 0; j <= y; j++)
      tmp.push_back(v);
    vec.push_back(tmp);
  }
}

void print2DVector(std::vector<std::vector<double>> &vec, const int &x, const int &y)
{
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
      std::cout << vec[i][j] << " ";
  }
}

void printVector(std::vector<double> &vec, const int &x)
{
  for (int i = 0; i < x; i++)
  {
    std::cout << vec[i] << " ";
  }
}