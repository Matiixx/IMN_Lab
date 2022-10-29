#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

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

double calcF(const double &u_p, const double &alfa, const double &beta)
{
  return alfa * u_p - beta * (u_p * u_p);
}

void picard()
{
  const double beta = 0.001;
  const double N = 500.0;
  const double gamma = 0.1;
  const double t_max = 100.0;
  const double dt = 0.1;
  const double TOL = 10e-6;
  const int mi = 20;
  const double alfa = beta * N - gamma;
  const int iter = t_max / dt;

  std::string filename = "picard.dat";
  clearFile(filename);

  std::vector<double> picard_array{};

  picard_array.push_back(1.0);
  double t{}, u_prev{}, u_next{};
  int curr_mi{};
  for (int i = 1; i <= iter; i++)
  {
    t = i * dt;
    u_prev = picard_array[i - 1];
    u_next = 0.0;
    curr_mi = 0;

    while (std::abs(u_next - u_prev) >= TOL && curr_mi <= mi)
    {
      if (curr_mi != 0)
        u_prev = u_next;
      u_next = picard_array[i - 1] + (dt / 2.0) * (calcF(picard_array[i - 1], alfa, beta) + calcF(u_prev, alfa, beta));
      curr_mi++;
    }
    picard_array.push_back(u_next);
    saveToFile(filename, t, u_next, N - u_next);
  }
}

void newton()
{
  const double beta = 0.001;
  const double N = 500.0;
  const double gamma = 0.1;
  const double t_max = 100.0;
  const double dt = 0.1;
  const double TOL = 10e-6;
  const int mi = 20;
  const double alfa = beta * N - gamma;
  const int iter = t_max / dt;

  std::string filename = "newton.dat";
  clearFile(filename);

  std::vector<double> newton_array{};
  newton_array.push_back(1.0);

  double u_prev{}, u_next{}, t{};
  int curr_mi{};
  for (int i = 1; i < iter; i++)
  {
    t = i * dt;
    u_prev = newton_array[i - 1];
    u_next = 0.0;
    curr_mi = 0;
    while (std::abs(u_next - u_prev) >= TOL && curr_mi <= mi)
    {
      if (curr_mi != 0)
        u_prev = u_next;
      u_next = u_prev - (u_prev - newton_array[i - 1] - dt / 2.0 * (calcF(newton_array[i - 1], alfa, beta) + calcF(u_prev, alfa, beta))) /
                            (1 - dt / 2.0 * (alfa - 2.0 * beta * u_prev));
      curr_mi++;
    }
    newton_array.push_back(u_next);
    saveToFile(filename, t, u_next, N - u_next);
  }
}

double calcF1(const double &U1, const double &U2, const double &u, const double (*a)[2], const double &alfa, const double &beta, const double &dt)
{
  return U1 - u - dt * (a[0][0] * calcF(U1, alfa, beta) + a[0][1] * calcF(U2, alfa, beta));
}

double calcF2(const double &U1, const double &U2, const double &u, const double (*a)[2], const double &alfa, const double &beta, const double &dt)
{
  return U2 - u - dt * (a[1][0] * calcF(U1, alfa, beta) + a[1][1] * calcF(U2, alfa, beta));
}

double calcDeltaU1(const double &f1, const double &f2, const double (*m)[2])
{
  return (f2 * m[0][1] - f1 * m[1][1]) / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
}

double calcDeltaU2(const double &f1, const double &f2, const double (*m)[2])
{
  return (f1 * m[1][0] - f2 * m[0][0]) / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
}

double calcM(const int &i, const int &j, const double &U, const double (*a)[2], const double &dt, const double &alfa, const double &beta)
{
  return (i == j ? 1.0 : 0.0) - dt * a[i][j] * (alfa - 2.0 * beta * U);
}

void rk2()
{
  const double beta = 0.001;
  const double N = 500.0;
  const double gamma = 0.1;
  const double t_max = 100.0;
  const double dt = 0.1;
  const double TOL = 10e-6;
  const int mi = 20;
  const double alfa = beta * N - gamma;
  const int iter = t_max / dt;

  const double a[2][2] = {
      {0.25, 0.25 - sqrt(3) / 6.0},
      {0.25 + sqrt(3) / 6.0, 0.25}};
  const double b[2] = {0.5, 0.5};
  const double c[2] = {a[0][1], a[1][0]};

  std::string filename = "rk2.dat";
  clearFile(filename);

  std::vector<double> rk2_array{};
  rk2_array.push_back(1.0);

  std::vector<double> U1{};
  std::vector<double> U2{};

  int curr_mi{};

  double delta_u1{}, delta_u2{}, f1{}, f2{}, m[2][2], u_next{}, t{};

  for (int i = 1; i <= iter; i++)
  {
    t = dt * i;
    U1.clear();
    U2.clear();
    U1.push_back(rk2_array[i - 1]);
    U2.push_back(rk2_array[i - 1]);
    curr_mi = 0;

    while (U1[curr_mi] >= TOL && U2[curr_mi] >= TOL && curr_mi <= mi)
    {
      m[0][0] = calcM(0, 0, U1[curr_mi], a, dt, alfa, beta);
      m[0][1] = calcM(0, 1, U2[curr_mi], a, dt, alfa, beta);
      m[1][0] = calcM(1, 0, U1[curr_mi], a, dt, alfa, beta);
      m[1][1] = calcM(1, 1, U2[curr_mi], a, dt, alfa, beta);

      f1 = calcF1(U1[curr_mi], U2[curr_mi], rk2_array[i - 1], a, alfa, beta, dt);
      f2 = calcF2(U1[curr_mi], U2[curr_mi], rk2_array[i - 1], a, alfa, beta, dt);

      delta_u1 = calcDeltaU1(f1, f2, m);
      delta_u2 = calcDeltaU2(f1, f2, m);

      U1.push_back(U1[curr_mi] + delta_u1);
      U2.push_back(U2[curr_mi] + delta_u2);

      curr_mi++;
    }
    u_next = rk2_array[i - 1] + dt * (b[0] * calcF(U1[static_cast<int>(c[0] * dt)], alfa, beta) +
                                      b[1] * calcF(U2[static_cast<int>(c[1] * dt)], alfa, beta));
    rk2_array.push_back(u_next);
    saveToFile(filename, t, u_next, N - u_next);
  }
}

int main()
{
  picard();
  newton();
  rk2();

  return 0;
}