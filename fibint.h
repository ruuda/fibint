#include <cstdint>

template <typename T> class fib_traits { };

template <> class fib_traits<std::uint8_t>
{
  public:
    static const std::uint8_t fib_max   = 0x0d;
    static const std::uint8_t prime     = 0xef;
    static const std::uint8_t sqrt5     = 0x1f;
    static const std::uint8_t sqrt5_inv = 0x36;
};

template <> class fib_traits<std::uint16_t>
{
  public:
    static const std::uint16_t fib_max   = 0x18;
    static const std::uint16_t prime     = 0xb52d;
    static const std::uint16_t sqrt5     = 0x57e5;
    static const std::uint16_t sqrt5_inv = 0xa285;
};

template <> class fib_traits<std::uint32_t>
{
  public:
    static const std::uint32_t fib_max   = 0x2f;
    static const std::uint32_t prime     = 0xb119254b;
    static const std::uint32_t sqrt5     = 0x1d582345;
    static const std::uint32_t sqrt5_inv = 0x2949db50;
};

template <> class fib_traits<std::uint64_t>
{
  public:
    static const std::uint64_t fib_max   = 0x5d;
    static const std::uint64_t prime     = 0xa94fad42221f27ad;
    static const std::uint64_t sqrt5     = 0x0b92025517515f58;
    static const std::uint64_t sqrt5_inv = 0x242d231e3eb01b01;
};

/* If your platform supports unsigned __int128, you can try this one as well.
template <> class fib_traits<unsigned __int128>
{
  public:
    static const unsigned __int128 fib_max   = 0xba;
    static const unsigned __int128 prime     = 0xfa63c8d9fa216a8fc8a7213b33327137;
    static const unsigned __int128 sqrt5     = 0x07d8096d5806fbc95c1b79206a07c4a7;
    static const unsigned __int128 inv_sqrt5 = 0x01919b7c44ce325b78d24b6ce2018dbb;
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
  const T p     = fib_traits<T>::prime;
  const T v     = fib_traits<T>::sqrt5;
  const T v_inv = fib_traits<T>::sqrt5_inv;

  const T a = powmod<T>(1 + v, n, p);
  const T b = powmod<T>(p + 1 - v, n, p);
  const T pow2_inv = powmod<T>(2, p - 1 - n, p);

  const T phin_minus_psin = (a > b) ? a - b : (p - b) + a;
  const T factor = mulmod(v_inv, pow2_inv, p);

  return mulmod(phin_minus_psin, factor, p);
}
