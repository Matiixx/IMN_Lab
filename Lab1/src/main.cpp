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

void saveToFile(const std::string &f, const double &a, const double &b, const double &c)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << " " << c << "\n";
  file.close();
}

double analticValue(double l, double t)
{
  return std::exp(l * t);
}

double eulerRes(const double &y, const double &dt, const double &lambda = -1.0)
{
  return y + dt * lambda * y;
}

void eulerMethod()
{
  const double y0 = 1.0;
  const double lambda = -1.0;
  const double t_start = 0.0;
  const double t_end = 5.0;
  const double time_stamps[] = {0.01, 0.1, 1.0};

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
      res = eulerRes(y[i], dt);
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

double rk2K1(const double &y, const double &lambda = -1.0)
{
  return lambda * y;
}

double rk2K2(const double &y, const double &dt, const double &k1, const double &lambda = -1.0)
{
  return lambda * (y + dt * k1);
}

double rk2Res(const double &y, const double &dt, const double &k1, const double &k2)
{
  return y + dt / 2.0 * (k1 + k2);
  ;
}

void rk2Method()
{

  const double y0 = 1.0;
  const double lambda = -1.0;
  const double t_start = 0.0;
  const double t_end = 5.0;
  const double time_stamps[] = {0.01, 0.1, 1.0};

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
      k1 = rk2K1(y[i]);
      k2 = rk2K2(y[i], dt, k1);
      res = rk2Res(y[i], dt, k1, k2);

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

double rk4K1(const double &y, const double &lambda = -1.0)
{
  return lambda * y;
}

double rk4K2(const double &y, const double &dt, const double &k1, const double &lambda = -1.0)
{
  return lambda * (y + dt / 2.0 * k1);
}

double rk4K3(const double &y, const double &dt, const double &k2, const double &lambda = -1.0)
{
  return lambda * (y + dt / 2.0 * k2);
}

double rk4K4(const double &y, const double &dt, const double &k3, const double &lambda = -1.0)
{
  return lambda * (y + dt * k3);
}

double rk4Res(const double &y, const double &dt, const std::vector<double> &k)
{
  return y + dt / 6.0 * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);
}

void rk4Method()
{

  const double y0 = 1.0;
  const double lambda = -1.0;
  const double t_start = 0.0;
  const double t_end = 5.0;
  const double time_stamps[] = {0.01, 0.1, 1.0};

  for (const auto &dt : time_stamps)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << dt;
    std::string filename = "rk4" + stream.str() + ".csv";
    clearFile(filename);

    std::string filenameDiffrence = "rk4" + stream.str() + "_diff.csv";
    clearFile(filenameDiffrence);

    std::vector<double> y{};
    y.push_back(1.0);
    const int n = (t_end - t_start) / dt;
    double res{};
    std::vector<double> k(4);
    for (int i = 0; i < n; i++)
    {
      k[0] = rk4K1(y[i]);
      k[1] = rk4K2(y[i], dt, k[0]);
      k[2] = rk4K3(y[i], dt, k[1]);
      k[3] = rk4K4(y[i], dt, k[2]);
      res = rk4Res(y[i], dt, k);

      y.push_back(res);
      saveToFile(filename, static_cast<double>(i) * dt, res);

      saveToFile(filenameDiffrence, static_cast<double>(i) * dt, res - analticValue(static_cast<double>(i) * dt, lambda));
    }
  }
  const double dt = 0.01;
  const int n = (t_end - t_start) / dt;
  clearFile("rk4_analytic.csv");
  for (int i = 0; i < n; i++)
  {
    saveToFile("rk4_analytic.csv", static_cast<double>(i) * dt, analticValue(static_cast<double>(i) * dt, lambda));
  }
}

double voltage(const double &omega, const double &t)
{
  return 10.0 * sin(omega * t);
}

double rrz2ResQ(const double &q, const double &dt, const std::vector<double> KQ)
{
  return q + dt / 6.0 * (KQ[0] + 2 * KQ[1] + 2 * KQ[2] + KQ[4]);
}

double rrz2ResI(const double &i, const double &dt, const std::vector<double> KI)
{
  return i + dt / 6.0 * (KI[0] + 2 * KI[1] + 2 * KI[2] + KI[4]);
}

void RRZ2()
{
  const double dt = 0.0001;
  const double R = 100;
  const double L = 0.1;
  const double C = 0.001;
  const double omega0 = 1.0 / sqrt(L * C);
  const double T0 = (2.0 * M_PI) / omega0;
  const double t_start = 0.0;
  const double t_end = 4.0 * T0;

  const double sources[] = {0.5 * omega0, 0.8 * omega0, 1.0 * omega0, 1.2 * omega0};
  const int n = (t_end - t_start) / dt;

  for (const auto &omegav : sources)
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << omegav;
    std::string filename = "rrz2_" + stream.str() + ".csv";
    clearFile(filename);

    std::vector<double> I{};
    I.push_back(0.0);
    std::vector<double> Q{};
    Q.push_back(0.0);

    std::vector<double> KQ(4), KI(4);
    double resQ{}, resI{};
    for (int i = 0; i < n; i++)
    {
      const double t = static_cast<double>(i) * dt;
      const double v = voltage(omegav, t);
      const double vHalf = voltage(omegav, (static_cast<double>(i) + 0.5) * dt);
      const double vNext = voltage(omegav, (static_cast<double>(i) + 1.0) * dt);

      KQ[0] = I[i];
      KI[0] = (v / L) - (Q[i] / (L * C)) - (R / L * I[i]);

      KQ[1] = I[i] + (dt / 2.0) * KI[0];
      KI[1] = (vHalf / L) - ((Q[i] + dt / 2.0 * KQ[0]) / (L * C)) - ((R / L) * (I[i] + ((dt / 2.0) * KI[0])));

      KQ[2] = I[i] + dt / 2.0 * KI[1];
      KI[2] = (vHalf / L) - ((Q[i] + (dt / 2.0) * KQ[1]) / (L * C)) - ((R / L) * (I[i] + (dt / 2.0) * KI[1]));

      KQ[3] = I[i] + dt * KI[2];
      KI[3] = (vNext / L) - ((Q[i] + (dt * KQ[2])) / (L * C)) - ((R / L) * (I[i] + (dt * KI[2])));

      resQ = rrz2ResQ(Q[i], dt, KQ);
      resI = rrz2ResI(I[i], dt, KI);

      Q.push_back(resQ);
      I.push_back(resI);

      saveToFile(filename, t, resQ, resI);
    }
  }
}

int main()
{
  eulerMethod();
  rk2Method();
  rk4Method();
  RRZ2();
  return 0;
}