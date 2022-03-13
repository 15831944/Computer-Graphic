#ifndef _VECTOR4_H_INCLUDED
#define _VECTOR4_H_INCLUDED
#include "Vector3.h"

template <typename T>
class Vector4 {
 public:
  typedef T BaseType;
  typedef T* T_ptr;
  static const int element_count = 4;

  /// Ĭ�Ϲ��캯��
  Vector4() {
    elements[0] = 0;
    elements[1] = 0;
    elements[2] = 0;
    elements[3] = 0;
  }
  /// ��������
  ~Vector4() = default;

  /// ��������
  Vector4(const Vector4& other) {
    elements[0] = other.x();
    elements[1] = other.y();
    elements[2] = other.z();
    elements[3] = other.w();
  }
  /// �������������͵�Vector4����
  template <typename S>
  explicit Vector4(const Vector4<S>& other) {
    x() = (T)other.x();
    y() = (T)other.y();
    z() = (T)other.z();
    w() = (T)other.w();
  }
  /// �����鹹�죨Ҫ������4��Ԫ�أ�
  explicit Vector4(const T_ptr& pval) {
    elements[0] = pval[0];
    elements[1] = pval[1];
    elements[2] = pval[2];
    elements[3] = pval[3];
  }
  /// �����(a, a, a, a)
  explicit Vector4(T val) {
    elements[0] = elements[1] = elements[2] = elements[3] = val;
  }
  /// �����(x, y, z, w)
  explicit Vector4(T x, T y, T z, T w) {
    elements[0] = x;
    elements[1] = y;
    elements[2] = z;
    elements[3] = w;
  }
  /// �������������͵�Vector3����ɣ�x, y, z, 1���������ά�������
  template <typename S>
  explicit Vector4(const Vector3<S>& v) {
    elements[0] = (T)v.x();
    elements[1] = (T)v.y();
    elements[2] = (T)v.z();
    elements[3] = (T)1;
  }
  /// �������������͵�Vector3����ɣ�x, y, z��w��
  template <typename S>
  explicit Vector4(const Vector3<S>& v, T w) {
    elements[0] = (T)v.x();
    elements[1] = (T)v.y();
    elements[2] = (T)v.z();
    elements[3] = w;
  }
  /// �������������͵�Vector2����ɣ�ux, uy, vx, vy��
  template <typename S>
  explicit Vector4(const Vector2<S>& u, const Vector2<S>& v) {
    elements[0] = (T)u.x();
    elements[1] = (T)u.y();
    elements[2] = (T)v.x();
    elements[3] = (T)v.y();
  }

  /// ����Ԫ������ָ��
  T* ptr() { return elements; }
  const T* ptr() const { return elements; }

  /// ����Ԫ�أ���Ϊһ����ά���������
  const T& x() const { return elements[0]; }
  const T& y() const { return elements[1]; }
  const T& z() const { return elements[2]; }
  const T& w() const { return elements[3]; }
  T& x() { return elements[0]; }
  T& y() { return elements[1]; }
  T& z() { return elements[2]; }
  T& w() { return elements[3]; }

  /// ����Ԫ�أ���Ϊ��ͨ����ɫ��RGBA��
  const T& r() const { return elements[0]; }
  const T& g() const { return elements[1]; }
  const T& b() const { return elements[2]; }
  const T& a() const { return elements[3]; }
  T& r() { return elements[0]; }
  T& g() { return elements[1]; }
  T& b() { return elements[2]; }
  T& a() { return elements[3]; }

  /// ����Ԫ�أ���ά����ռ�
  const T& s() const { return elements[0]; }
  const T& t() const { return elements[1]; }
  const T& p() const { return elements[2]; }
  const T& q() const { return elements[3]; }
  T& s() { return elements[0]; }
  T& t() { return elements[1]; }
  T& p() { return elements[2]; }
  T& q() { return elements[3]; }

  /// ����ǰ����Ԫ���γɵ�Vector3
  Vector3<T> xyz() const { return Vector3<T>(x(), y(), z()); }
  Vector3<T> rgb() const { return Vector3<T>(x(), y(), z()); }
  Vector3<T> stp() const { return Vector3<T>(x(), y(), z()); }

  /// ����ǰ����Ԫ���γɵ�Vector2
  Vector2<T> xy() const { return Vector2<T>(x(), y()); }
  Vector2<T> rg() const { return Vector2<T>(x(), y()); }
  Vector2<T> st() const { return Vector2<T>(x(), y()); }

  /// ����������Ԫ��ֵ
  template <typename S>
  void setValue(S a, S b, S c, S d) {
    x() = T(a);
    y() = T(b);
    z() = T(c);
    w() = T(d);
  }
  template <typename S>
  void setValue(const Vector4<S>& other) {
    x() = T(other.x());
    y() = T(other.y());
    z() = T(other.z());
    w() = T(other.w());
  }
  /// ����ȡ��Ԫ�ص�ֵ
  template <typename S>
  void getValue(S& a, S& b, S& c, S& d) const {
    a = S(x());
    b = S(y());
    c = S(z());
    d = S(w());
  }
  template <typename S>
  void getValue(Vector4<S>& other) const {
    other.x() = S(x());
    other.y() = S(y());
    other.z() = S(z());
    other.w() = S(w());
  }

  /// ��Ԫ���������
  Vector4 operator+(const Vector4& other) const {
    return Vector4(x() + other.x(), y() + other.y(), z() + other.z(),
                   w() + other.w());
  }
  Vector4 operator-(const Vector4& other) const {
    return Vector4(x() - other.x(), y() - other.y(), z() - other.z(),
                   w() - other.w());
  }
  Vector4 operator*(const Vector4& other) const {
    return Vector4(x() * other.x(), y() * other.y(), z() * other.z(),
                   w() * other.w());
  }
  Vector4 operator/(const Vector4& other) const {
    return Vector4(x() / other.x(), y() / other.y(), z() / other.z(),
                   w() / other.w());
  }

  T dot(const Vector4& other) const {
    return x() * other.x() + y() * other.y() + z() * other.z() +
           w() * other.w();
  }
  T operator^(const Vector4& other) const { return dot(other); }

  Vector4 operator+(T val) const {
    return Vector4(x() + val, y() + val, z() + val, w() + val);
  }
  Vector4 operator-(T val) const {
    return Vector4(x() - val, y() - val, z() - val, w() - val);
  }
  Vector4 operator*(T val) const {
    return Vector4(x() * val, y() * val, z() * val, w() * val);
  }
  Vector4 operator/(T val) const {
    return Vector4(x() / val, y() / val, z() / val, w() / val);
  }
  Vector4 operator-() const { return Vector4(-x(), -y(), -z(), -w()); }

  Vector4& negate() {
    x() = -x();
    y() = -y();
    z() = -z();
    w() = -w();
    return *this;
  }

  Vector4& operator+=(const Vector4& other) {
    x() += other.x();
    y() += other.y();
    z() += other.z();
    w() += other.w();
    //*this = *this + other;
    return *this;
  }
  Vector4& operator-=(const Vector4& other) {
    x() -= other.x();
    y() -= other.y();
    z() -= other.z();
    w() -= other.w();
    //*this = *this - other;
    return *this;
  }
  Vector4& operator*=(const Vector4& other) {
    x() *= other.x();
    y() *= other.y();
    z() *= other.z();
    w() *= other.w();
    //*this = *this * other;
    return *this;
  }
  Vector4& operator/=(const Vector4& other) {
    x() /= other.x();
    y() /= other.y();
    z() /= other.z();
    w() /= other.w();
    //*this = *this / other;
    return *this;
  }
  Vector4& operator+=(T val) {
    x() += val;
    y() += val;
    z() += val;
    w() += val;
    //*this = *this + val;
    return *this;
  }
  Vector4& operator-=(T val) {
    x() -= val;
    y() -= val;
    z() -= val;
    w() -= val;
    //*this = *this - val;
    return *this;
  }
  Vector4& operator*=(T val) {
    x() *= val;
    y() *= val;
    z() *= val;
    w() *= val;
    //*this = *this * val;
    return *this;
  }
  Vector4& operator/=(T val) {
    x() /= val;
    y() /= val;
    z() /= val;
    w() /= val;
    //*this = *this / val;
    return *this;
  }

  Vector4& operator=(const Vector4& other) {
    if (this != &other) {
      x() = other.x();
      y() = other.y();
      z() = other.z();
      w() = other.w();
    }
    return *this;
  }
  Vector4& operator=(T val) {
    x() = y() = z() = w() = val;
    return *this;
  }

  template <typename S>
  bool operator==(const Vector4<S>& other) const {
    return x() == other.x() && y() == other.y() && z() == other.z() &&
           w() == other.w();
  }
  template <typename S>
  bool operator!=(const Vector4<S>& other) const {
    return !operator==(other);
  }
  template <typename S>
  bool operator<(const Vector4<S>& other) const {
    if (x() != other.x())
      return x() < other.x();
    else if (y() != other.y())
      return y() < other.y();
    else if (z() != other.z())
      return z() < other.z();
    else
      return w() < other.w();
  }

  bool equalWithTolerance(const Vector4& other, T e) const {
    for (int i = 0; i < 4; i++)
      if ((((*this)[i] > other[i]) ? (*this)[i] - other[i]
                                   : other[i] - (*this)[i]) > e)
        return false;

    return true;
  }

  T length() const {
    return (T)::sqrt(x() * x() + y() * y() + z() * z() + w() * w());
  }
  T lengthSquared() const {
    return x() * x() + y() * y() + z() * z() + w() * w();
  }
  T lengthTiny() const {
    T absX = (x() >= T(0)) ? x() : -x();
    T absY = (y() >= T(0)) ? y() : -y();
    T absZ = (z() >= T(0)) ? z() : -z();
    T absW = (w() >= T(0)) ? w() : -w();

    T max = absX;

    if (max < absY)
      max = absY;

    if (max < absZ)
      max = absZ;

    if (max < absW)
      max = absW;

    if (max == T(0))
      return T(0);

    absX /= max;
    absY /= max;
    absZ /= max;
    absW /= max;

    return max *
           std::sqrt(absX * absX + absY * absY + absZ * absZ + absW * absW);
  }

  bool isNull() const { return !x() && !y() && !z() && !w(); }
  const Vector4& normalize(T* len = nullptr, bool* success = nullptr) {
    T l = length();
    if (len)
      *len = l;
    if (l) {
      x() /= l;
      y() /= l;
      z() /= l;
      w() /= l;
      if (success)
        *success = true;
      //*this *= (T)(1.0/l);//1.0/l���������
    } else {
      if (success)
        *success = false;
    }
    return *this;
  }
  Vector4 normalized(T* len = nullptr, bool* success = nullptr) const {
    T l = length();
    if (len)
      *len = l;
    if (l) {
      if (success)
        *success = true;
      return Vector4(x() / l, y() / l, z() / l, w() / l);
    } else {
      if (success)
        *success = false;
      return Vector4(T(0));
    }
  }

  const T& operator[](unsigned i) const { return elements[i]; }
  T& operator[](unsigned i) { return elements[i]; }

  /// Ԫ�ظ���
  constexpr static unsigned int dimensions() { return 4; }

  /// ��������ֵ��ͨ���Ǹ�ֵ��
  constexpr static T baseTypeLowest() {
    return std::numeric_limits<T>::lowest();
  }
  /// �������ֵ��ͨ������ֵ��
  constexpr static T baseTypeMax() { return std::numeric_limits<T>::max(); }
  /// ������Сֵ��ͨ���Ǹ�ֵ��
  constexpr static T baseTypeSmallest() {
    return std::numeric_limits<T>::min();
  }
  /// ����Сֵe�� 1+e != 1
  constexpr static T baseTypeEpsilon() {
    return std::numeric_limits<T>::epsilon();
  }

 protected:
  T elements[element_count];
};

template <typename T>
inline const Vector4<T> operator*(T val, const Vector4<T>& v) {
  return v * val;
}

typedef Vector4<int> Vec4i;
typedef Vector4<float> Vec4f;
typedef Vector4<double> Vec4d;

typedef Vec4d Vec4;

inline float dot(const Vec4i& v1, const Vec4i& v2) {
  return (float)(v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() +
                 v1.w() * v2.w());
}
inline float dot(const Vec4f& v1, const Vec4f& v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w();
}
inline double dot(const Vec4d& v1, const Vec4d& v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w();
}

inline Vec4f min(const Vec4f& a, const Vec4f& b) {
  return Vec4f(a.x() < b.x() ? a.x() : b.x(), a.y() < b.y() ? a.y() : b.y(),
               a.z() < b.z() ? a.z() : b.z(), a.w() < b.w() ? a.w() : b.w());
}
inline Vec4f min(const Vec4f& a, float b) {
  return Vec4f(a.x() < b ? a.x() : b, a.y() < b ? a.y() : b,
               a.z() < b ? a.z() : b, a.w() < b ? a.w() : b);
}
inline Vec4d min(const Vec4d& a, const Vec4d& b) {
  return Vec4d(a.x() < b.x() ? a.x() : b.x(), a.y() < b.y() ? a.y() : b.y(),
               a.z() < b.z() ? a.z() : b.z(), a.w() < b.w() ? a.w() : b.w());
}
inline Vec4d min(const Vec4d& a, double b) {
  return Vec4d(a.x() < b ? a.x() : b, a.y() < b ? a.y() : b,
               a.z() < b ? a.z() : b, a.w() < b ? a.w() : b);
}
inline Vec4i min(const Vec4i& a, const Vec4i& b) {
  return Vec4i(a.x() < b.x() ? a.x() : b.x(), a.y() < b.y() ? a.y() : b.y(),
               a.z() < b.z() ? a.z() : b.z(), a.w() < b.w() ? a.w() : b.w());
}
inline Vec4i min(const Vec4i& a, int b) {
  return Vec4i(a.x() < b ? a.x() : b, a.y() < b ? a.y() : b,
               a.z() < b ? a.z() : b, a.w() < b ? a.w() : b);
}

inline Vec4f max(const Vec4f& a, const Vec4f& b) {
  return Vec4f(a.x() > b.x() ? a.x() : b.x(), a.y() > b.y() ? a.y() : b.y(),
               a.z() > b.z() ? a.z() : b.z(), a.w() > b.w() ? a.w() : b.w());
}
inline Vec4f max(const Vec4f& a, float b) {
  return Vec4f(a.x() > b ? a.x() : b, a.y() > b ? a.y() : b,
               a.z() > b ? a.z() : b, a.w() > b ? a.w() : b);
}
inline Vec4d max(const Vec4d& a, const Vec4d& b) {
  return Vec4d(a.x() > b.x() ? a.x() : b.x(), a.y() > b.y() ? a.y() : b.y(),
               a.z() > b.z() ? a.z() : b.z(), a.w() > b.w() ? a.w() : b.w());
}
inline Vec4d max(const Vec4d& a, double b) {
  return Vec4d(a.x() > b ? a.x() : b, a.y() > b ? a.y() : b,
               a.z() > b ? a.z() : b, a.w() > b ? a.w() : b);
}
inline Vec4i max(const Vec4i& a, const Vec4i& b) {
  return Vec4i(a.x() > b.x() ? a.x() : b.x(), a.y() > b.y() ? a.y() : b.y(),
               a.z() > b.z() ? a.z() : b.z(), a.w() > b.w() ? a.w() : b.w());
}
inline Vec4i max(const Vec4i& a, int b) {
  return Vec4i(a.x() > b ? a.x() : b, a.y() > b ? a.y() : b,
               a.z() > b ? a.z() : b, a.w() > b ? a.w() : b);
}

inline Vec4f clamp(const Vec4f& x, float minval, float maxval) {
  return min(max(x, minval), maxval);
}
inline Vec4f clamp(const Vec4f& x, const Vec4f& minval, const Vec4f& maxval) {
  return min(max(x, minval), maxval);
}
inline Vec4d clamp(const Vec4d& x, double minval, double maxval) {
  return min(max(x, minval), maxval);
}
inline Vec4d clamp(const Vec4d& x, const Vec4d& minval, const Vec4d& maxval) {
  return min(max(x, minval), maxval);
}
inline Vec4i clamp(const Vec4i& x, int minval, int maxval) {
  return min(max(x, minval), maxval);
}
inline Vec4i clamp(const Vec4i& x, const Vec4i& minval, const Vec4i& maxval) {
  return min(max(x, minval), maxval);
}

// template <typename T> std::ostream& operator<< (std::ostream& s, const
// Vector4<T>& v);
template <typename T>
inline T project(const T& s, const T& t);
template <typename T>
inline T orthogonal(const T& s, const T& t);
template <typename T>
inline T reflect(const T& s, const T& t);
template <typename T>
T closestVertex(const T& v0, const T& v1, const T& v2, const T& p);

// template <typename T> std::ostream& operator<< (std::ostream& s, const
// Vector4<T>& v)
//{
//    return s << '(' << v.x() << ' ' << v.y() << ' ' << v.z() << ' ' << v.w()
//    << ')';
//}

/// ���º���������V��һ�����������Ǳ���
/// ������t��s (���ͣ�`Vector2`, `Vector3`,
/// `Vector4`)�ϵ�ͶӰ��ֻ���ڸ������͵�����`Vec2f`, `Vec3d`�ȡ� �磺Vec2d v, s,
/// t; v = project(s, t)
template <typename V>
inline V project(const V& s, const V& t) {
  V sNormalized = s.normalized();
  return sNormalized * (sNormalized ^ t);
}

/// ��ֱ������S��������S��T (���ͣ�`Vector2`, `Vector3`,
/// `Vector4`)ͬƽ���������ֻ���ڸ������͵�����`Vec2f`, `Vec3d`�ȡ� �磺Vec2d
/// v, s, t; v = orthogonal(s, t)
template <typename V>
inline V orthogonal(const V& s, const V& t) {
  return t - project(s, t);
}

/// ������S������ƽ�棨������T(���ͣ�`Vector2`, `Vector3`,
/// `Vector4`)�������������ֻ���ڸ������͵�����`Vec2f`, `Vec3d`�ȡ� �磺Vec2d
/// v, s, t; v = reflect(s, t)
template <typename V>
inline V reflect(const V& s, const V& t) {
  return s - typename V::BaseType(2) * (s - project(t, s));
}

/// �����P(���ͣ�`Vector2`, `Vector3`, `Vector4`)��������������εĶ���(v0, v1,
/// v2) �磺Vec2d v, v0, v1, v2, P; v = closestVertex(v0, v1, v2, P)
template <typename V>
V closestVertex(const V& v0, const V& v1, const V& v2, const V& p) {
  V nearest = v0;
  typename V::BaseType neardot = (v0 - p).length2();
  typename V::BaseType tmp = (v1 - p).length2();

  if (tmp < neardot) {
    neardot = tmp;
    nearest = v1;
  }

  tmp = (v2 - p).length2();

  if (tmp < neardot) {
    neardot = tmp;
    nearest = v2;
  }

  return nearest;
}

#endif  //_VECTOR4_H_INCLUDED