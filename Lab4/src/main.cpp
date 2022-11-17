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

const double epsilon = 1.0,
             delta = 0.1,
             nx = 150,
             ny = 100,
             V1 = 10.0,
             V2 = 0.0,
             x_max = delta * nx,
             y_max = delta * ny,
             sigma_x = 0.1 * x_max,
             sigma_y = 0.1 * y_max,
             TOL = 1e-8;

double rho_1(const double &x, const double &y)
{
  return std::exp(-((x - 0.35 * x_max) * (x - 0.35 * x_max)) / (sigma_x * sigma_x) - ((y - 0.5 * y_max) * (y - 0.5 * y_max)) / (sigma_y * sigma_y));
}

double rho_2(const double &x, const double &y)
{
  return -std::exp(-((x - 0.65 * x_max) * (x - 0.65 * x_max)) / (sigma_x * sigma_x) - ((y - 0.5 * y_max) * (y - 0.5 * y_max)) / (sigma_y * sigma_y));
}

double rho(const double &x, const double &y)
{
  return rho_1(delta * x, delta * y) + rho_2(delta * x, delta * y);
}

void initVector(std::vector<std::vector<double>> &vec, const double &v = 0.0)
{
  for (int i = 0; i <= nx; i++)
  {
    std::vector<double> tmp;
    for (int j = 0; j <= ny; j++)
      tmp.push_back(v);
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

double calcS(const std::vector<std::vector<double>> &V)
{
  double S{};
  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      S += (delta * delta) *
           (0.5 * ((V[i + 1][j] - V[i][j]) / delta) * ((V[i + 1][j] - V[i][j]) / delta) +
            0.5 * ((V[i][j + 1] - V[i][j]) / delta) * ((V[i][j + 1] - V[i][j]) / delta) -
            rho(i, j) *
                V[i][j]);
    }
  }
  return S;
}

void globalRelaxation()
{
  const double omega_G_array[] = {0.6, 1.0};
  double V = 0;
  std::vector<std::vector<double>> density{};

  initVector(density);
  for (int i = 1; i < nx; i++)
    for (int j = 1; j < ny; j++)
      density[i][j] = rho(i, j);

  const double dde = (delta * delta) / epsilon;
  std::stringstream ss;

  for (const auto &omega_g : omega_G_array)
  {
    std::vector<std::vector<double>> Vs{};
    std::vector<std::vector<double>> Vn{};
    int iter = 0;
    double S_prev{};
    double S{};
    initVector(Vs);
    initVector(Vn);

    for (int j = 0; j <= nx; j++)
    {
      Vs[j][0] = V1;
      Vn[j][0] = V1;
    }

    ss.str("");
    ss.clear();
    ss << "global_s_" << omega_g << ".dat";
    std::string filename = ss.str();
    clearFile(filename);

    while (true)
    {
      for (int i = 1; i <= nx - 1; i++)
        for (int j = 1; j <= ny - 1; j++)
          Vn[i][j] = 0.25 * (Vs[i + 1][j] + Vs[i - 1][j] + Vs[i][j + 1] + Vs[i][j - 1] +
                             dde * density[i][j]);

      for (int j = 1; j <= ny - 1; j++)
      {
        Vn[nx][j] = Vn[nx - 1][j];
        Vn[0][j] = Vn[1][j];
      }

      for (int i = 0; i <= nx; i++)
        for (int j = 0; j <= ny; j++)
          Vs[i][j] = (1.0 - omega_g) * Vs[i][j] + omega_g * Vn[i][j];

      S_prev = S;
      S = calcS(Vn);

      if (iter % 5000 == 0)
      {
        std::cout << "Omega: " << omega_g << " iter: " << iter << " S: " << S << " Stop: " << std::fabs((S - S_prev) / S_prev) << "\n";
      }

      saveToFile(filename, iter, S);

      if (std::fabs((S - S_prev) / S_prev) < TOL)
      {
        std::cout << "Omega: " << omega_g << " stop iteration at: " << iter << "\n";
        break;
      }

      iter++;
    }

    ss.str("");
    ss.clear();
    ss << "global_v_" << omega_g << ".dat";
    filename = ss.str();
    clearFile(filename);
    for (int i = 0; i <= nx; i++)
      for (int j = 0; j <= ny; j++)
        saveToFile(filename, i * delta, j * delta, Vn[i][j]);
  }
}

void localRelaxation()
{
  const double omega_G_array[] = {1.0, 1.4, 1.8, 1.9};
  std::stringstream ss;

  std::vector<std::vector<double>> density{};
  initVector(density);
  for (int i = 1; i < nx; i++)
    for (int j = 1; j < ny; j++)
      density[i][j] = rho(i, j);

  for (const auto &omega_g : omega_G_array)
  {
    std::vector<std::vector<double>> V{};

    int iter = 0;
    double S_prev{};
    double S{};
    initVector(V);

    for (int j = 0; j <= nx; j++)
    {
      V[j][0] = V1;
    }

    ss.str("");
    ss.clear();
    ss << "local_s_" << omega_g << ".dat";
    std::string filename = ss.str();
    clearFile(filename);

    const double omega_min_1 = 1 - omega_g;
    const double omega_4 = omega_g * 0.25;
    const double dde = (delta * delta) / epsilon;

    while (true)
    {
      for (int i = 1; i < nx; i++)
      {
        for (int j = 1; j < ny; j++)
        {
          V[i][j] = omega_min_1 * V[i][j] +
                    omega_4 *
                        (V[i + 1][j] + V[i - 1][j] + V[i][j - 1] + V[i][j + 1] + dde * density[i][j]);
        }
      }

      for (int j = 1; j < ny; j++)
      {
        V[0][j] = V[1][j];
        V[nx][j] = V[nx - 1][j];
      }

      S_prev = S;
      S = calcS(V);

      if (iter % 5000 == 0)
        std::cout << "Omega: " << omega_g << " iter: " << iter << " S: " << S << " Stop: " << std::fabs((S - S_prev) / S_prev) << "\n";

      saveToFile(filename, iter, S);

      if (std::fabs((S - S_prev) / S_prev) < TOL)
      {
        std::cout << "Omega: " << omega_g << " stop iteration at: " << iter << "\n";
        break;
      }

      iter++;
    }
  }
}

int main()
{
  globalRelaxation();
  localRelaxation();
  return 0;
}