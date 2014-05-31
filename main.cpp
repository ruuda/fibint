#include <cstdint>
#include <iostream>

typedef std::uint64_t u64;

u64 mulmod(u64 a, u64 b, u64 m)
{
  u64 r = 0;
  u64 s = 0;

  while (b > 0)
  {
    s = ((m - r) > a) ? r + a : r + a - m;
    r = (b & 1) * s + (1 - (b & 1)) * r;
    b >>= 1;
    a = ((m - a) > a) ? a + a : a + a - m;
  }

  return r;
}

u64 powmod(u64 a, u64 e, u64 m)
{
  u64 r = 1;
  
  while (e > 0)
  {
    r = (e & 1) * mulmod(r, a, m) + (1 - (e & 1)) * r;
    e >>= 1;
    a = mulmod(a, a, m);
  }

  return r;
}

int main()
{
  u64 a, b, m;
  std::cin >> a;
  std::cin >> b;
  std::cin >> m;
  std::cout << powmod(a, b, m);
  return 0;
}
