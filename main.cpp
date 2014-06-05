#include <cstdint>
#include <iostream>

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

template <typename T> class fib_traits { };

template <> class fib_traits<u8>
{
  public:
    static const u8 fib_max   = 13;
    static const u8 prime     = 239;
    static const u8 sqrt5     = 31;
    static const u8 inv_sqrt5 = 54;
};

template <> class fib_traits<u16>
{
  public:
    static const u16 fib_max   = 24;
    static const u16 prime     = 46381;
    static const u16 sqrt5     = 22501;
    static const u16 inv_sqrt5 = 41605;
};

template <> class fib_traits<u32>
{
  public:
    static const u32 fib_max   = 47;
    static const u32 prime     = 2971215179;
    static const u32 sqrt5     = 492315461;
    static const u32 inv_sqrt5 = 692706128;
};

template <> class fib_traits<u64>
{
  public:
    static const u64 fib_max   = 93;
    static const u64 prime     = 12200160415121876909;
    static const u64 sqrt5     = 833731445503647576;
    static const u64 inv_sqrt5 = 2606778372125104897;
};

/* If your platform supports unsigned __int128, you can try this one as well.
template <> class fib_traits<u128>
{
  public:
    static const u128 fib_max   = 186;
    static const u128 prime     = 332825110087067562321196029789634457911;
    static const u128 sqrt5     = 10426323296737204245551694426008962215;
    static const u128 inv_sqrt5 = 2085264659347440849110338885201792443;
};
*/

template <typename T> T mulmod(T a, T b, T m)
{
  T r = 0;
  T s = 0;

  while (b > 0)
  {
    s = ((m - r) > a) ? r + a : r + a - m;
    r = (b & 1) * s + (1 - (b & 1)) * r;
    b >>= 1;
    a = ((m - a) > a) ? a + a : a + a - m;
  }

  return r;
}

template <typename T> T powmod(T a, T e, T m)
{
  T r = 1;
  
  while (e > 0)
  {
    r = (e & 1) * mulmod(r, a, m) + (1 - (e & 1)) * r;
    e >>= 1;
    a = mulmod(a, a, m);
  }

  return r;
}

template <typename T> T fib(T n)
{
  const T prime = fib_traits<T>::prime;
  const T sqrt5 = fib_traits<T>::sqrt5;
  const T sqrt5inv = fib_traits<T>::inv_sqrt5;

  u64 a = powmod(1 + sqrt5, n, prime);
  u64 b = powmod(prime + 1 - sqrt5, n, prime);
  u64 invpow2 = powmod<T>(2, prime - 1 - n, prime);

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
