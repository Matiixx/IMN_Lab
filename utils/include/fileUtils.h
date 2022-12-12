#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <initializer_list>

void clearFile(const std::string &);
void saveToFile(const std::string &, const double &, const double &);
void saveToFile(const std::string &, const double &, const double &, const double &);
void saveToFile(const std::string &, const double &, const double &, const double &, const double &);
void saveToFile(const std::string &, const double &, const double &, const double &, const double &, const double &, const double &);
void saveVector2DToFile(const std::string &, std::vector<std::vector<double>> &, const int &, const int &, const double &, const int &);
void addEndLineToFile(const std::string &f);

template <typename T>
void saveToFile(const std::string &filename, std::initializer_list<T> list)
{
  std::fstream file;
  file.open(filename, std::ios::app);
  for (const auto el : list)
  {
    file << el << " ";
  }
  file << "\n";
  file.close();
}