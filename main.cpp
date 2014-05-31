#include <cstdint>
#include <iostream>

typedef std::uint64_t u64;

u64 mulmod(u64 a, u64 b, u64 m)
{
  u64 r = 0;
  u64 s = 0;
  a %= m;
  b %= m;

  while (b > 0)
  {
    s = ((m - r) > a) ? r + a : r + a - m;
    r = (b & 1) * s + (1 - (b & 1)) * r;
    b >>= 1;
    a = ((m - a) > a) ? a + a : a + a - m;
  }

  return r;
}

int main()
{
  u64 a, b, m;
  std::cin >> a;
  std::cin >> b;
  std::cin >> m;
  std::cout << mulmod(a, b, m);
  return 0;
}
