// fibint -- compute Fibonacci numbers efficiently using finite fields
// Copyright © 2014 Ruud van Asseldonk, licensed under the MIT licence

#include <cstdint>

template <typename T> struct fib_traits { };

template <> struct fib_traits<std::uint8_t>
{
  static const int fib_max = 13;
  static const std::uint8_t prime     = 0xef;
  static const std::uint8_t sqrt5     = 0x1f;
  static const std::uint8_t sqrt5_inv = 0x36;
};

template <> struct fib_traits<std::uint16_t>
{
  static const int fib_max = 24;
  static const std::uint16_t prime     = 0xb52d;
  static const std::uint16_t sqrt5     = 0x57e5;
  static const std::uint16_t sqrt5_inv = 0xa285;
};

template <> struct fib_traits<std::uint32_t>
{
  static const int fib_max = 47;
  static const std::uint32_t prime     = 0xb119254b;
  static const std::uint32_t sqrt5     = 0x1d582345;
  static const std::uint32_t sqrt5_inv = 0x2949db50;
};

template <> struct fib_traits<std::uint64_t>
{
  static const int fib_max = 93;
  static const std::uint64_t prime     = 0xa94fad42221f27ad;
  static const std::uint64_t sqrt5     = 0x0b92025517515f58;
  static const std::uint64_t sqrt5_inv = 0x242d231e3eb01b01;
};

/* If your platform supports unsigned __int128, you can try this one as well.
template <> struct fib_traits<unsigned __int128>
{
  static const int fib_max = 186;
  static const unsigned __int128 prime     = 0xfa63c8d9fa216a8fc8a7213b33327137;
  static const unsigned __int128 sqrt5     = 0x07d8096d5806fbc95c1b79206a07c4a7;
  static const unsigned __int128 sqrt5_inv = 0x01919b7c44ce325b78d24b6ce2018dbb;
};
*/

template <typename T> T addmod(T a, T b, T m)
{
  if (m - b > a) return a + b;
  else return a + b - m;
}

template <typename T> T submod(T a, T b, T m)
{
  if (a >= b) return a - b;
  else return m - b + a;
}

template <typename T> T mulmod(T a, T b, T m)
{
  T r = 0;

  while (b > 0)
  {
    // My benchmarks show that masking here is significantly faster than a
    // conditional, with GCC 4.9 and Clang 3.4 for a 64-bit integer,
    // on my machine.

    r = addmod(a, r, m) * (b & 1) + r * (1 - (b & 1));
    b >>= 1;
    a = addmod(a, a, m);
  }

  return r;
}

template <typename T> T powmod(T a, T e, T m)
{
  T r = 1;
  
  while (e > 0)
  {
    // My benchmarks show that a conditional here is significantly faster than
    // masking, for a 64-bit integer on my machine, with msvc110, GCC 4.9, and
    // Clang 3.4.

    if (e & 1) r = mulmod(r, a, m);
    e >>= 1;
    a = mulmod(a, a, m);
  }

  return r;
}

template <typename T> T fib(T n)
{
  // Note: it is assumed that n is not larger than fib_traits<T>::prime,
  // otherwise the results are incorrect. Note that this is not a big problem,
  // because fib_traits<T>::fib_max < fib_traits<T>::prime.

  const T p     = fib_traits<T>::prime;
  const T v     = fib_traits<T>::sqrt5;
  const T v_inv = fib_traits<T>::sqrt5_inv;

  const T a        = powmod<T>(1 + v, n, p);
  const T b        = powmod<T>(p + 1 - v, n, p);
  const T pow2_inv = powmod<T>(2, p - 1 - n, p);

  const T diff   = submod(a, b, p);
  const T factor = mulmod(v_inv, pow2_inv, p);

  return mulmod(diff, factor, p);
}
