#include <cstdint>
#include <cmath>

template <> class fib_traits<float>
{
  public:
    static const int fib_max;
};

template <> class fib_traits<double>
{
  public:
    static const int fib_max;
};

template <typename T> T fibfloat(T n)
{
  const T v     = static_cast<T>(2.236067977499789696409173668731276235441);
  const T v_inv = static_cast<T>(0.447213595499957939281834733746255247088);

  const T a = std::pow<T>(static_cast<T>(1.0) + v, n);
  const T b = std::pow<T>(static_cast<T>(1.0) - v, n);
  const T pow2_inv = std::pow<T>(static_cast<T>(2.0), -n);

  const T phin_minus_psin = a - b;
  const T factor = v_inv * pow2_inv;

  return phin_minus_psin * factor;
}

template <> float fib(float n)
{
  return fibfloat(n);
}

template <> double fib(double n)
{
  return fibfloat(n);
}
