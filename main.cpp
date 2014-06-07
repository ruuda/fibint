#include <cstring>
#include <iostream>
#include <chrono>
#include "fibint.h"

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

template <typename T> void bench()
{
  T acc[] = { 0, 0, 0, 0 };

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  auto begin = high_resolution_clock::now();

  // The actual numbers are not very important here, just loop a lot,
  // so it takes a few seconds to complete.
  const int n = 4096 * 64 / (fib_traits<T>::fib_max + 1);
  for (int j = 0; j < n; j++)
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

  std::cout << "iters: " << n * (fib_traits<T>::fib_max + 1)  << std::endl;
  std::cout << "bogus: " << acc[0] + acc[1] + acc[2] + acc[3] << std::endl;
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
