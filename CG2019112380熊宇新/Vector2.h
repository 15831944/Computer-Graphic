#ifndef _VECTOR2_H_INCLUDED
#define _VECTOR2_H_INCLUDED
#include <assert.h>
#include <stddef.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>  //用到std中的vector，定义数组用
const double dPi =
    3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093845;
const double dDEG_TO_RAD = dPi / 180.0;
const double dRAD_TO_DEG = 180.0 / dPi;
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef dot
#undef dot
#endif
#ifdef cross
#undef cross
#endif
template <typename T>
class Vector2 {
 public:

  typedef T BaseType;
  typedef T* T_ptr;
  static const int element_count = 2;
  Vector2() {
    elements[0] = 0;
    elements[1] = 0;
  }
  ~Vector2() = default;
  Vector2(T val1, T val2) {
    elements[0] = val1;
    elements[1] = val2;
  }
  Vector2(const Vector2& other) {
    elements[0] = other.x();
    elements[1] = other.y();
  }
  template <typename S>
  explicit Vector2(const Vector2<S>& other) {
    elements[0] = T(other.x());
    elements[1] = T(other.y());
  }
  explicit Vector2(T val) {
    elements[0] = val;
    elements[1] = val;
  }
  explicit Vector2(const T_ptr& pval) {
    elements[0] = pval[0];
    elements[1] = pval[1];
  }
  constexpr static unsigned int dimensions() { return element_count; }
  const T x() const { return elements[0]; }
  const T y() const { return elements[1]; }
  T& x() { return elements[0]; }
  T& y() { return elements[1]; }
  const T* ptr() const { return elements; }
  T* ptr() { return elements; }
  //运算符重载
  Vector2 operator+(const Vector2& other) const {
    return Vector2(x() + other.x(), y() + other.y());
  }
  Vector2 operator-(const Vector2& other) const {
    return Vector2(x() - other.x(), y() - other.y());
  }
  Vector2 operator*(const Vector2& other) const {
    return Vector2(x() * other.x(), y() * other.y());
  }
  Vector2 operator/(const Vector2& other) const {
    return Vector2(x() / other.x(), y() / other.y());
  }
  Vector2 operator+(T val) const { return Vector2(x() + val, y() + val); }
  Vector2 operator-(T val) const { return Vector2(x() - val, y() - val); }
  Vector2 operator*(T val) const { return Vector2(x() * val, y() * val); }
  Vector2 operator/(T val) const { return Vector2(x() / val, y() / val); }
  Vector2 operator-() const { return Vector2(-x(), -y()); }
  

	Vector2& negate() {
    x() = -x();
    y() = -y();
    return *this;
  }
  Vector2& operator+=(const Vector2& other) {
    x() += other.x();
    y() += other.y();
    return *this;
  }
  Vector2& operator-=(const Vector2& other) {
    x() -= other.x();
    y() -= other.y();
    return *this;
  }
  Vector2& operator*=(const Vector2& other) {
    x() *= other.x();
    y() *= other.y();
    return *this;
  }
  Vector2& operator/=(const Vector2& other) {
    x() /= other.x();
    y() /= other.y();
    return *this;
  }
  Vector2& operator+=(T val) {
    x() += val;
    y() += val;
    return *this;
  }
  Vector2& operator-=(T val) {
    x() -= val;
    y() -= val;
    return *this;
  }
  Vector2& operator*=(T val) {
    x() *= val;
    y() *= val;
    return *this;
  }
  Vector2& operator/=(T val) {
    x() /= val;
    y() /= val;
    return *this;
  }
  
  Vector2& operator=(const Vector2& other) {
    if (this != &other) {
      x() = other.x();
      y() = other.y();
    }
    return *this;
  }
  Vector2& operator=(T val) {
    x() = y() = val;
    return *this;
  }
  template <typename S>
  bool operator==(const Vector2<S>& other) const {
    return x() == other.x() && y() == other.y();
  }
  template <typename S>
  bool operator!=(const Vector2<S>& other) const {
    return !operator==(other);
  }
  template <typename S>
  bool operator<(const Vector2<S>& other) const {
    if (x() != other.x())
      return x() < other.x();
    else
      return y() < other.y();
  }
  bool equalWithTolerance(const Vector2& other, T e) const {
    for (int i = 0; i < 2; i++)
      if ((((*this)[i] > other[i]) ? (*this)[i] - other[i]
                                   : other[i] - (*this)[i]) > e)
        return false;
    return true;
  }
  T dot(const Vector2& other) const {
    return x() * other.x() + y() * other.y();
  }
  T cross(const Vector2& other) const {
    return x() * other.y() - y() * other.x();
  }
  T length() const { return ::sqrt(x() * x() + y() * y()); }
  T lengthSquared() const { return x() * x() + y() * y(); }
  bool isNull() const { return !x() && !y(); }
  Vector2& normalize(T* len = nullptr, bool* success = nullptr) {
    T leng = length();
    if (len)
      *len = leng;
    if (leng) {
      x() /= leng;
      y() /= leng;
      if (success)
        *success = true;
    } else {
      if (success)
        *success = false;
    }
    return *this;
  }
  Vector2 normalized(T* len = nullptr, bool* success = nullptr) const {
    T leng = length();
    if (len)
      *len = leng;
    if (leng) {
      if (success)
        *success = true;
      return Vector2(x() / leng, y() / leng);
    } else {
      if (success)
        *success = false;
      return Vector2(T(0));
    }
  }
  T& operator[](unsigned i) { return elements[i]; }
  constexpr const T& operator[](unsigned i) const { return elements[i]; }

 protected:
  T elements[element_count];
};
/*
template<typename T>
inline const Vector2<T> operator*(T val, const Vector2<T>& v)
{
return v * val;
}
*/
typedef Vector2<int> Vec2i;
typedef Vector2<double> Vec2d;
typedef Vec2d Vec2;
typedef Vector2<int> Pos2i;
typedef Vector2<double> Pos2d;
typedef Pos2d Pos2;
typedef std::vector<Vec2i> Vec2iArry;
typedef std::vector<Vec2d> Vec2dArry;
typedef std::vector<Pos2i> Pos2iArry;
typedef std::vector<Pos2d> Pos2dArry;
#endif  //_VECTOR2_H_INCLUDED