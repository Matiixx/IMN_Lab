#pragma once

#include <iostream>
#include <vector>
#include <fstream>

void clearFile(const std::string &);
void saveToFile(const std::string &, const double &, const double &);
void saveToFile(const std::string &, const double &, const double &, const double &);
void saveToFile(const std::string &, const double &, const double &, const double &, const double &);
void saveVectorToFile(const std::string &, std::vector<std::vector<double>> &, const int &, const int &, const double &, const int &);