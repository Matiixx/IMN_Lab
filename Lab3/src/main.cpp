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

void saveToFile(const std::string &f, const double &a, const double &b, const double &c, const double &d)
{
  std::fstream file;
  file.open(f, std::ios::app);
  file << a << " " << b << " " << c << " " << d << "\n";
  file.close();
}

struct result
{
  double xn1, vn1;
};

const double TOL[] = {1e-2, 1e-5};
const double alfa = 5;

inline double f(const double &a) { return a; }
inline double g(const double &a, const double &b) { return alfa * (1 - a * a) * b - a; }

template <typename T>
T max(const T &a, const T &b)
{
  if (a > b)
    return a;
  return b;
}

result metodaTrapezow(const double &xn, const double &vn, const double &dt, const double &alfa)
{
  double xn1 = xn;
  double vn1 = vn;
  double F{}, G{}, dx{}, dv{};
  double a[2][2];
  a[0][0] = 1;
  a[0][1] = -dt / 2.0;

  while (true)
  {
    F = xn1 - xn - dt / 2.0 * (f(vn) + f(vn1));
    G = vn1 - vn - dt / 2.0 * (g(xn, vn) + g(xn1, vn1));

    a[1][0] = -dt / 2.0 * (-2 * alfa * xn1 * vn1 - 1);
    a[1][1] = 1 - dt / 2.0 * alfa * (1 - xn1 * xn1);

    dx = (-F * a[1][1] + G * a[0][1]) / (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
    dv = (-G * a[0][0] + F * a[1][0]) / (a[0][0] * a[1][1] - a[0][1] * a[1][0]);

    xn1 += dx;
    vn1 += dv;

    if (fabs(dx) < 1e-10 && fabs(dv) < 1e-10)
      break;
  }

  return {xn1, vn1};
}

result metodaRK2(const double &xn, const double &vn, const double &dt, const double &alfa)
{
  double k1x = f(vn);
  double k1v = g(xn, vn);

  double k2x = f(vn + dt * k1v);
  double k2v = g(xn + dt * k1x, vn + dt * k1v);

  return {xn + dt / 2.0 * (k1x + k2x), vn + dt / 2.0 * (k1v + k2v)};
}

struct method
{
  result (*fun)(const double &, const double &, const double &, const double &);
  std::string name;
  result operator()(const double &xn, const double &vn, const double &dt, const double &alfa)
  {
    return fun(xn, vn, dt, alfa);
  }
};

method methodArray[] = {
    {metodaTrapezow, "metoda_trapezow"},
    {metodaRK2, "metoda_rk2"}};

void kkc(method schemat_numeryczny, const double &tol)
{
  double t = 0,
         x0 = 0.01,
         v0 = 0,
         dt0 = 1,
         S = 0.75,
         tmax = 40,
         p = 2.0,
         xn = x0,
         vn = v0,
         dt = dt0,
         Ex{},
         Ev{};

  std::stringstream ss;
  ss << schemat_numeryczny.name << "_" << tol << ".dat";

  const std::string filename = ss.str();

  clearFile(filename);
  do
  {
    auto [x2n1, v2n1] = schemat_numeryczny(xn, vn, dt, alfa);
    auto [x2n2, v2n2] = schemat_numeryczny(x2n1, v2n1, dt, alfa);

    auto [x1n2, v1n2] = schemat_numeryczny(xn, vn, 2 * dt, alfa);

    Ex = (x2n2 - x1n2) / (pow(2, p) - 1);
    Ev = (v2n2 - v1n2) / (pow(2, p) - 1);

    if (max(fabs(Ex), fabs(Ev)) < tol)
    {
      t += 2 * dt;
      xn = x2n2;
      vn = v2n2;
      saveToFile(filename, t, dt, xn, vn);
    }
    dt *= pow((S * tol) / max(fabs(Ex), fabs(Ev)), 1 / (p + 1));

  } while (t < tmax);
}

int main()
{
  kkc(methodArray[0], TOL[0]);
  kkc(methodArray[0], TOL[1]);
  kkc(methodArray[1], TOL[0]);
  kkc(methodArray[1], TOL[1]);
  return 0;
}