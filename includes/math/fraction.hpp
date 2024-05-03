#ifndef __TC_MATH_FRACTION_HPP__
#define __TC_MATH_FRACTION_HPP__

#include <numeric>

#include "../defines.hpp"
#include "core.hpp"

namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <typename Number>
concept fractionable = std::integral<Number>;

template <fractionable T> class Fraction {
private:
  T mNumerator;
  T mDenominator;

public:
  Fraction() : mNumerator(0), mDenominator(1) {}
  Fraction(T const &numerator) : mNumerator(numerator), mDenominator(1) {}
  Fraction(T const &numerator, T const &denominator)
      : mNumerator(numerator), mDenominator(denominator) {}
  Fraction(Fraction<T> const &other)
      : mNumerator(other.mNumerator), mDenominator(other.mDenominator) {}
  Fraction(Fraction<T> &&other) noexcept
      : mNumerator(std::move(other.mNumerator)),
        mDenominator(std::move(other.mDenominator)) {}

  T const &GetNumerator() const { return mNumerator; }
  T const &GetDenominator() const { return mDenominator; }

  Fraction<T> &SetNumerator(T const &numerator) {
    mNumerator = numerator;
    return *this;
  }
  Fraction<T> &SetDenominator(T const &denominator) {
    mDenominator = denominator;
    return *this;
  }

  Fraction<T> operator+() const { return *this; }
  Fraction<T> operator-() const {
    return Fraction<T>(-mNumerator, mDenominator);
  }

  Fraction<T> &operator=(T const &value);
  Fraction<T> &operator=(Fraction<T> const &other);
  Fraction<T> &operator=(Fraction<T> &&other) noexcept;

  Fraction<T> &operator+=(Fraction<T> const &other);
  Fraction<T> &operator-=(Fraction<T> const &other);
  Fraction<T> &operator*=(Fraction<T> const &other);
  Fraction<T> &operator/=(Fraction<T> const &other);
  Fraction<T> &operator+=(T const &other);
  Fraction<T> &operator-=(T const &other);
  Fraction<T> &operator*=(T const &other);
  Fraction<T> &operator/=(T const &other);

  operator Float() const {
    return static_cast<Float>(mNumerator) / mDenominator;
  }
  operator Double() const {
    return static_cast<Double>(mNumerator) / mDenominator;
  }
};

template <fractionable T>
Fraction<T> operator+(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator-(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator*(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator/(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator+(Fraction<T> const &lhs, T const &rhs);
template <fractionable T>
Fraction<T> operator-(Fraction<T> const &lhs, T const &rhs);
template <fractionable T>
Fraction<T> operator*(Fraction<T> const &lhs, T const &rhs);
template <fractionable T>
Fraction<T> operator/(Fraction<T> const &lhs, T const &rhs);
template <fractionable T>
Fraction<T> operator+(T const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator-(T const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator*(T const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Fraction<T> operator/(T const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Bool operator==(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  return lhs.GetNumerator() == rhs.GetNumerator() &&
         lhs.GetDenominator() == rhs.GetDenominator();
}
template <fractionable T>
Bool operator!=(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  return !(lhs == rhs);
}
template <fractionable T>
Bool operator<(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Bool operator>(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Bool operator<=(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Bool operator>=(Fraction<T> const &lhs, Fraction<T> const &rhs);
template <fractionable T>
Bool operator==(Fraction<T> const &lhs, T const &rhs) {
  return lhs.GetDenominator() == 1 && lhs.GetNumerator() == rhs;
}
template <fractionable T>
Bool operator!=(Fraction<T> const &lhs, T const &rhs) {
  return !(lhs == rhs);
}
template <fractionable T> Bool operator<(Fraction<T> const &lhs, T const &rhs) {
  return lhs.GetNumerator() < lhs.GetDenominator() * rhs;
}
template <fractionable T> Bool operator>(Fraction<T> const &lhs, T const &rhs) {
  return lhs.GetNumerator() > lhs.GetDenominator() * rhs;
}
template <fractionable T>
Bool operator<=(Fraction<T> const &lhs, T const &rhs) {
  return lhs.GetNumerator() <= lhs.GetDenominator() * rhs;
}
template <fractionable T>
Bool operator>=(Fraction<T> const &lhs, T const &rhs) {
  return lhs.GetNumerator() >= lhs.GetDenominator() * rhs;
}
template <fractionable T, number U>
Bool operator==(Fraction<T> const &lhs, U const &rhs) {
  return lhs.GetDenominator() == 1 && lhs.GetNumerator() == rhs;
}
template <fractionable T, number U>
Bool operator!=(Fraction<T> const &lhs, U const &rhs) {
  return !(lhs == rhs);
}
template <fractionable T, number U>
Bool operator<(Fraction<T> const &lhs, U const &rhs) {
  return lhs.GetNumerator() < lhs.GetDenominator() * rhs;
}
template <fractionable T, number U>
Bool operator>(Fraction<T> const &lhs, U const &rhs) {
  return lhs.GetNumerator() > lhs.GetDenominator() * rhs;
}
template <fractionable T, number U>
Bool operator<=(Fraction<T> const &lhs, U const &rhs) {
  return lhs.GetNumerator() <= lhs.GetDenominator() * rhs;
}
template <fractionable T, number U>
Bool operator>=(Fraction<T> const &lhs, U const &rhs) {
  return lhs.GetNumerator() >= lhs.GetDenominator() * rhs;
}
} // namespace TerreateCore::Math

// Implementation
namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <fractionable T> Fraction<T> &Fraction<T>::operator=(T const &value) {
  mNumerator = value;
  mDenominator = 1;
  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator=(Fraction<T> const &other) {
  mNumerator = other.mNumerator;
  mDenominator = other.mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator=(Fraction<T> &&other) noexcept {
  mNumerator = other.mNumerator;
  mDenominator = other.mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator+=(Fraction<T> const &other) {
  mNumerator =
      mNumerator * other.mDenominator + other.mNumerator * mDenominator;
  mDenominator *= other.mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator-=(Fraction<T> const &other) {
  mNumerator =
      mNumerator * other.mDenominator - other.mNumerator * mDenominator;
  mDenominator *= other.mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator*=(Fraction<T> const &other) {
  mNumerator *= other.mNumerator;
  mDenominator *= other.mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T>
Fraction<T> &Fraction<T>::operator/=(Fraction<T> const &other) {
  mNumerator *= other.mDenominator;
  mDenominator *= other.mNumerator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T> Fraction<T> &Fraction<T>::operator+=(T const &other) {
  mNumerator += other * mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T> Fraction<T> &Fraction<T>::operator-=(T const &other) {
  mNumerator -= other * mDenominator;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T> Fraction<T> &Fraction<T>::operator*=(T const &other) {
  mNumerator *= other;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T> Fraction<T> &Fraction<T>::operator/=(T const &other) {
  mDenominator *= other;

  if (mDenominator < 0) {
    mNumerator = -mNumerator;
    mDenominator = -mDenominator;
  }

  T gcd = std::gcd(Abs(mNumerator), Abs(mDenominator));
  mNumerator /= gcd;
  mDenominator /= gcd;
  return *this;
}

template <fractionable T>
Fraction<T> operator+(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result += rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator-(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result -= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator*(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result *= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator/(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result /= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator+(Fraction<T> const &lhs, T const &rhs) {
  Fraction<T> result(lhs);
  result += rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator-(Fraction<T> const &lhs, T const &rhs) {
  Fraction<T> result(lhs);
  result -= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator*(Fraction<T> const &lhs, T const &rhs) {
  Fraction<T> result(lhs);
  result *= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator/(Fraction<T> const &lhs, T const &rhs) {
  Fraction<T> result(lhs);
  result /= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator+(T const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result += rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator-(T const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result -= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator*(T const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result *= rhs;
  return result;
}

template <fractionable T>
Fraction<T> operator/(T const &lhs, Fraction<T> const &rhs) {
  Fraction<T> result(lhs);
  result /= rhs;
  return result;
}

template <fractionable T>
Bool operator<(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  T mul = lhs.GetDenominator() * rhs.GetDenominator();
  return lhs.GetNumerator() * mul < rhs.GetNumerator() * mul;
}

template <fractionable T>
Bool operator>(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  T mul = lhs.GetDenominator() * rhs.GetDenominator();
  return lhs.GetNumerator() * mul > rhs.GetNumerator() * mul;
}

template <fractionable T>
Bool operator<=(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  T mul = lhs.GetDenominator() * rhs.GetDenominator();
  return lhs.GetNumerator() * mul <= rhs.GetNumerator() * mul;
}

template <fractionable T>
Bool operator>=(Fraction<T> const &lhs, Fraction<T> const &rhs) {
  T mul = lhs.GetDenominator() * rhs.GetDenominator();
  return lhs.GetNumerator() * mul >= rhs.GetNumerator() * mul;
}

template <fractionable T> Fraction<T> Abs(Fraction<T> const &f) {
  return Fraction<T>(Abs<T>(f.GetNumerator()), Abs<T>(f.GetDenominator()));
}

template <fractionable T> struct MatrixTypeTraits<Fraction<T>> {
  static Str ToString(Fraction<T> const &f) {
    return std::to_string(f.GetNumerator()) + "/" +
           std::to_string(f.GetDenominator());
  }
};
} // namespace TerreateCore::Math

template <TerreateCore::Math::fractionable T>
std::ostream &operator<<(std::ostream &os,
                         TerreateCore::Math::Fraction<T> const &f) {
  os << f.GetNumerator() << "/" << f.GetDenominator();
  return os;
}

#endif // __TC_MATH_FRACTION_HPP__
