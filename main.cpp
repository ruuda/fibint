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

u64 fib(u64 n)
{
  const u64 prime = 12200160415121876909;
  const u64 sqrt5 = 833731445503647576;
  const u64 sqrt5inv = 2606778372125104897;

  n %= prime; // It overflows long before this happens, has no real use ...

  u64 a = powmod(1 + sqrt5, n, prime);
  u64 b = powmod(prime + 1 - sqrt5, n, prime);
  u64 invpow2 = powmod(2, prime - 1 - n, prime);

  u64 phin_minus_psin = (a > b) ? a - b : (prime - b) + a;
  u64 factor = mulmod(sqrt5inv, invpow2, prime);

  return mulmod(phin_minus_psin, factor, prime);
}

int main()
{
  for (u64 i = 0; i < 94; i++)
  std::cout << fib(i) << std::endl;
  return 0;
}
