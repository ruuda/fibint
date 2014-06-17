// fibint -- compute Fibonacci numbers efficiently using finite fields
// Copyright © 2014 Ruud van Asseldonk, licensed under the MIT licence

#include <chrono>
#include <cstring>
#include <iostream>
#include "fibint.h"
#include "fibfloat.h"

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

static_assert(sizeof(float)  == 4, "The `float` type must be 32 bits.");
static_assert(sizeof(double) == 8, "The `double` type must be 64 bits.");

typedef float  f32;
typedef double f64;

// These helpers make bitwise operations on floats a bit more convenient.
template <typename T> struct raw       { typedef T   uint; };
template           <> struct raw<f32>  { typedef u32 uint; };
template           <> struct raw<f64>  { typedef u64 uint; };
template <typename T> union  raw_bytes { T value; typename raw<T>::uint raw; };

template <typename T> void bench()
{
  raw_bytes<T> acc[] = { 0, 0, 0, 0 };

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  auto begin = high_resolution_clock::now();

  // The actual numbers are not very important here, just loop a lot,
  // so it takes a few seconds to complete.
  const int n = (1 << 19) / (fib_traits<T>::fib_max + 1);
  for (int j = 0; j < n; j++)
  {
    for (int i = 0; i <= fib_traits<T>::fib_max; i++)
    {
      // The xor here is also not very important, it is only used to create
      // some data dependencies to avoid optimising it away. It is done on
      // four independent values so that data dependencies will not be the
      // bottleneck.
      raw_bytes<T> f = { fib(static_cast<T>(i)) };
      acc[i % 4].raw ^= f.raw;
    }
    
    // This just creates some data dependencies between loops (because xor is
    // symmetric, so we have to use some operation that does not commute with
    // xor).
    acc[0].raw |= acc[1].raw & acc[3].raw;
    acc[2].raw |= acc[1].raw & acc[3].raw;
  }

  auto end = high_resolution_clock::now();

  auto duration = duration_cast<milliseconds>(end - begin);
  std::cout << duration.count() << std::endl;

  std::cout << "iters: " << n * (fib_traits<T>::fib_max + 1) << std::endl;
  std::cout << "bogus: " << acc[0].raw + acc[1].raw + acc[2].raw + acc[3].raw
            << std::endl;
}

template <typename T> void print()
{
  for (int i = 0; i <= fib_traits<T>::fib_max; i++)
  {
    std::cout << static_cast<u64>(fib(static_cast<T>(i))) << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    if (0 == strcmp(argv[1], "bench"))
    {
      if (0 == strcmp(argv[2], "u8"))  bench<u8>();
      if (0 == strcmp(argv[2], "u16")) bench<u16>();
      if (0 == strcmp(argv[2], "u32")) bench<u32>();
      if (0 == strcmp(argv[2], "u64")) bench<u64>();
      if (0 == strcmp(argv[2], "f32")) bench<f32>();
      if (0 == strcmp(argv[2], "f64")) bench<f64>();
    }

    if (0 == strcmp(argv[1], "print"))
    {
      if (0 == strcmp(argv[2], "u8"))  print<u8>();
      if (0 == strcmp(argv[2], "u16")) print<u16>();
      if (0 == strcmp(argv[2], "u32")) print<u32>();
      if (0 == strcmp(argv[2], "u64")) print<u64>();
      if (0 == strcmp(argv[2], "f32")) print<f32>();
      if (0 == strcmp(argv[2], "f64")) print<f64>();
    }
  }

  return 0;
}
