#include <cstdint>
#include <cstring>
#include <iostream>
#include <chrono>

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

  const T a = powmod<T>(1 + sqrt5, n, prime);
  const T b = powmod<T>(prime + 1 - sqrt5, n, prime);
  const T invpow2 = powmod<T>(2, prime - 1 - n, prime);

  const T phin_minus_psin = (a > b) ? a - b : (prime - b) + a;
  const T factor = mulmod(sqrt5inv, invpow2, prime);

  return mulmod(phin_minus_psin, factor, prime);
}

template <typename T> void bench()
{
  T acc[] = { 0, 0, 0, 0 };

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  auto begin = high_resolution_clock::now();

  // The actual numbers are not very important here, just loop a lot,
  // so it takes a few seconds to complete.
  for (int j = 0; j < 4096 * 64 / (fib_traits<T>::fib_max + 1); j++)
  {
    for (T i = 0; i <= fib_traits<T>::fib_max; i++)
    {
      // The xor here is also not very important, it is only used to create
      // some data dependencies to avoid optimising it away. It is done on
      // four independent values so that data dependencies will not be the
      // bottleneck.
      acc[i % 4] ^= fib(i);
    }
    
    // This just creates some data dependencies between loops (because xor is
    // symmetric, so we have to use some operation that does not commute with
    // xor.)
    acc[0] |= acc[1] & acc[3];
    acc[2] |= acc[1] & acc[3];
  }

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(end - begin);
  std::cout << duration.count() << std::endl;

  std::cout << acc[0] + acc[1] + acc[2] + acc[3] << std::endl;
}

template <typename T> void print()
{
  for (T i = 0; i <= fib_traits<T>::fib_max; i++)
  {
    std::cout << fib(i) << std::endl;
  }
}

template <> void print<u8>()
{
  for (u8 i = 0; i <= fib_traits<u8>::fib_max; i++)
  {
    std::cout << static_cast<int>(fib<u8>(i)) << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    if (0 == strcmp(argv[1], "bench"))
    {
      if (0 == strcmp(argv[2], "8"))  bench<u8>();
      if (0 == strcmp(argv[2], "16")) bench<u16>();
      if (0 == strcmp(argv[2], "32")) bench<u32>();
      if (0 == strcmp(argv[2], "64")) bench<u64>();
    }

    if (0 == strcmp(argv[1], "print"))
    {
      if (0 == strcmp(argv[2], "8"))  print<u8>();
      if (0 == strcmp(argv[2], "16")) print<u16>();
      if (0 == strcmp(argv[2], "32")) print<u32>();
      if (0 == strcmp(argv[2], "64")) print<u64>();
    }
  }

  return 0;
}
