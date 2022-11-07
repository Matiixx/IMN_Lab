#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

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

struct result
{
  double xn1, vn1;
};

const double TOL[] = {1e-2, 1e-5};
const double alfa = 5;

inline double f(const double &a) { return a; }
inline double g(const double &a, const double &b) { return alfa * (1 - a * a) * b - a; }

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

int main()
{
  auto [x, y] = metodaTrapezow(1, 2, 3, 12);
  std::cout << x << " " << y << "\n";
  return 0;
}