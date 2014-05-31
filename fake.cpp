#include <cstdint>
#include <iostream>
#include <cmath>

typedef std::uint64_t u64;

u64 fib(u64 n)
{
  const double sqrt5 = std::sqrt(5.0);
  const double sqrt5inv = 1.0 / sqrt5;

  double a = std::pow(1 + sqrt5, static_cast<double>(n));
  double b = std::pow(1 - sqrt5, static_cast<double>(n));
  double invpow2 = std::pow(2.0, -static_cast<double>(n));

  double phin_minus_psin = a - b;
  double factor = sqrt5inv * invpow2;

  return static_cast<u64>(phin_minus_psin * factor);
}

int main()
{
  for (u64 i = 0; i < 94; i++)
  std::cout << fib(i) << std::endl;
  return 0;
}
