#include <cstdint>

template <typename T> class fib_traits { };

template <> class fib_traits<std::uint8_t>
{
  public:
    static const std::uint8_t fib_max   = 13;
    static const std::uint8_t prime     = 239;
    static const std::uint8_t sqrt5     = 31;
    static const std::uint8_t inv_sqrt5 = 54;
};

template <> class fib_traits<std::uint16_t>
{
  public:
    static const std::uint16_t fib_max   = 24;
    static const std::uint16_t prime     = 46381;
    static const std::uint16_t sqrt5     = 22501;
    static const std::uint16_t inv_sqrt5 = 41605;
};

template <> class fib_traits<std::uint32_t>
{
  public:
    static const std::uint32_t fib_max   = 47;
    static const std::uint32_t prime     = 2971215179;
    static const std::uint32_t sqrt5     = 492315461;
    static const std::uint32_t inv_sqrt5 = 692706128;
};

template <> class fib_traits<std::uint64_t>
{
  public:
    static const std::uint64_t fib_max   = 93;
    static const std::uint64_t prime     = 12200160415121876909;
    static const std::uint64_t sqrt5     = 833731445503647576;
    static const std::uint64_t inv_sqrt5 = 2606778372125104897;
};

/* If your platform supports unsigned __int128, you can try this one as well.
template <> class fib_traits<unsigned __int128>
{
  public:
    static const unsigned __int128 fib_max   = 186;
    static const unsigned __int128 prime     = 332825110087067562321196029789634457911;
    static const unsigned __int128 sqrt5     = 10426323296737204245551694426008962215;
    static const unsigned __int128 inv_sqrt5 = 2085264659347440849110338885201792443;
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
