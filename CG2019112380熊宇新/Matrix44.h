#ifndef _MATRIX44_H_INCLUDED
#define _MATRIX44_H_INCLUDED
#include "Matrix33.h"
#include "Vector4.h"

template <typename T>
class Matrix44 {
 public:
  typedef T BaseType;

  //默认构造成单位矩阵
  Matrix44() { setIdentity(); }

  ~Matrix44() = default;

  // 从其他类型的Matrix44矩阵构造
  template <typename S>
  explicit Matrix44(const Matrix44<S>& m) {
    e(0, 0) = (T)m.e(0, 0);
    e(1, 0) = (T)m.e(1, 0);
    e(2, 0) = (T)m.e(2, 0);
    e(3, 0) = (T)m.e(3, 0);
    e(0, 1) = (T)m.e(0, 1);
    e(1, 1) = (T)m.e(1, 1);
    e(2, 1) = (T)m.e(2, 1);
    e(3, 1) = (T)m.e(3, 1);
    e(0, 2) = (T)m.e(0, 2);
    e(1, 2) = (T)m.e(1, 2);
    e(2, 2) = (T)m.e(2, 2);
    e(3, 2) = (T)m.e(3, 2);
    e(0, 3) = (T)m.e(0, 3);
    e(1, 3) = (T)m.e(1, 3);
    e(2, 3) = (T)m.e(2, 3);
    e(3, 3) = (T)m.e(3, 3);
  }

  //拷贝构造
  Matrix44(const Matrix44& other) { operator=(other); }

  //主对角元素指定值构造
  explicit Matrix44(T n) {
    setIdentity();
    e(0, 0) = e(1, 1) = e(2, 2) = e(3, 3) = n;
  }

  //使用16个元素的数组构造（按行）
  explicit Matrix44(T* val) { fillPtr(val); }

  //使用16个元素构造（按行）
  explicit Matrix44(T e00,
                    T e01,
                    T e02,
                    T e03,
                    T e10,
                    T e11,
                    T e12,
                    T e13,
                    T e20,
                    T e21,
                    T e22,
                    T e23,
                    T e30,
                    T e31,
                    T e32,
                    T e33) {
    e(0, 0) = e00;
    e(0, 1) = e01;
    e(0, 2) = e02;
    e(0, 3) = e03;
    e(1, 0) = e10;
    e(1, 1) = e11;
    e(1, 2) = e12;
    e(1, 3) = e13;
    e(2, 0) = e20;
    e(2, 1) = e21;
    e(2, 2) = e22;
    e(2, 3) = e23;
    e(3, 0) = e30;
    e(3, 1) = e31;
    e(3, 2) = e32;
    e(3, 3) = e33;
  }

  //各元素设为指定值
  Matrix44& fill(T val) {
    e(0, 0) = e(1, 0) = e(2, 0) = e(3, 0) = e(0, 1) = e(1, 1) = e(2, 1) =
        e(3, 1) = e(0, 2) = e(1, 2) = e(2, 2) = e(3, 2) = e(0, 3) = e(1, 3) =
            e(2, 3) = e(3, 3) = val;
    return *this;
  }

  //使用16个元素的数组设定各元素值
  Matrix44& fillPtr(T* val) {
    memcpy(ptr(), val, sizeof(T) * 16);
    return *this;
  }

  /// 赋值到另一矩阵
  template <typename S>
  void getValue(Matrix44<S>& m) const {
    m.e(0, 0) = (S)e(0, 0);
    m.e(1, 0) = (S)e(1, 0);
    m.e(2, 0) = (S)e(2, 0);
    m.e(3, 0) = (S)e(3, 0);
    m.e(0, 1) = (S)e(0, 1);
    m.e(1, 1) = (S)e(1, 1);
    m.e(2, 1) = (S)e(2, 1);
    m.e(3, 1) = (S)e(3, 1);
    m.e(0, 2) = (S)e(0, 2);
    m.e(1, 2) = (S)e(1, 2);
    m.e(2, 2) = (S)e(2, 2);
    m.e(3, 2) = (S)e(3, 2);
    m.e(0, 3) = (S)e(0, 3);
    m.e(1, 3) = (S)e(1, 3);
    m.e(2, 3) = (S)e(2, 3);
    m.e(3, 3) = (S)e(3, 3);
  }

  /// 从另一矩阵赋值
  template <typename S>
  Matrix44& setValue(const Matrix44<S>& m) {
    e(0, 0) = (T)m.e(0, 0);
    e(1, 0) = (T)m.e(1, 0);
    e(2, 0) = (T)m.e(2, 0);
    e(3, 0) = (T)m.e(3, 0);
    e(0, 1) = (T)m.e(0, 1);
    e(1, 1) = (T)m.e(1, 1);
    e(2, 1) = (T)m.e(2, 1);
    e(3, 1) = (T)m.e(3, 1);
    e(0, 2) = (T)m.e(0, 2);
    e(1, 2) = (T)m.e(1, 2);
    e(2, 2) = (T)m.e(2, 2);
    e(3, 2) = (T)m.e(3, 2);
    e(0, 3) = (T)m.e(0, 3);
    e(1, 3) = (T)m.e(1, 3);
    e(2, 3) = (T)m.e(2, 3);
    e(3, 3) = (T)m.e(3, 3);
    return *this;
  }

  //返回X向量（第一列，1*3子阵）
  Vector3<T> getX() const {
    return Vector3<T>(eVec[0].x(), eVec[0].y(), eVec[0].z());
  }

  //返回Y向量（第二列，1*3子阵）
  Vector3<T> getY() const {
    return Vector3<T>(eVec[1].x(), eVec[1].y(), eVec[1].z());
  }

  //返回Z向量（第三列，1*3子阵）
  Vector3<T> getZ() const {
    return Vector3<T>(eVec[2].x(), eVec[2].y(), eVec[2].z());
  }

  //返回平移向量（第四列，1*3子阵）
  Vector3<T> getT() const {
    return Vector3<T>(eVec[3].x(), eVec[3].y(), eVec[3].z());
  }

  //设置X向量（第一列，1*3子阵）
  Matrix44& setX(const Vector3<T>& v) {
    eVec[0].x() = v.x();
    eVec[0].y() = v.y();
    eVec[0].z() = v.z();
    return *this;
  }

  //设置Y向量（第二列，1*3子阵）
  Matrix44& setY(const Vector3<T>& v) {
    eVec[1].x() = v.x();
    eVec[1].y() = v.y();
    eVec[1].z() = v.z();
    return *this;
  }

  //设置Z向量（第三列，1*3子阵）
  Matrix44& setZ(const Vector3<T>& v) {
    eVec[2].x() = v.x();
    eVec[2].y() = v.y();
    eVec[2].z() = v.z();
    return *this;
  }

  //设置平移向量（第四列，1*3子阵）
  Matrix44& setT(const Vector3<T>& v) {
    eVec[3].x() = v.x();
    eVec[3].y() = v.y();
    eVec[3].z() = v.z();
    return *this;
  }

  //左上3*3子阵不变，右下元素为1，最后一行、一列的其他元素设为0
  Matrix44 as3x3() const {
    Matrix44 t = *this;
    t[0][3] = 0;
    t[1][3] = 0;
    t[2][3] = 0;
    t[3][3] = 1;
    t[3][0] = 0;
    t[3][1] = 0;
    t[3][2] = 0;
    return t;
  }

  //返回左上3*3子阵
  Matrix33<T> get3x3() const {
    Matrix33<T> t;
    t.e(0, 0) = e(0, 0);
    t.e(1, 0) = e(1, 0);
    t.e(2, 0) = e(2, 0);
    t.e(0, 1) = e(0, 1);
    t.e(1, 1) = e(1, 1);
    t.e(2, 1) = e(2, 1);
    t.e(0, 2) = e(0, 2);
    t.e(1, 2) = e(1, 2);
    t.e(2, 2) = e(2, 2);
    return t;
  }

  //! This writes only on the upper 3x3 part of the matrix without touching the
  //! last row and column. 设置左上3*3子阵，其他元素不变
  void set3x3(const Matrix33<T>& m) {
    e(0, 0) = m.e(0, 0);
    e(1, 0) = m.e(1, 0);
    e(2, 0) = m.e(2, 0);
    e(0, 1) = m.e(0, 1);
    e(1, 1) = m.e(1, 1);
    e(2, 1) = m.e(2, 1);
    e(0, 2) = m.e(0, 2);
    e(1, 2) = m.e(1, 2);
    e(2, 2) = m.e(2, 2);
  }

  /// 与其他矩阵的差异
  T diff(const Matrix44& other) const {
    T err = 0;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (e(j, i) > other.e(j, i))  // avoid fabs/abs
          err += e(j, i) - other.e(j, i);
        else
          err += other.e(j, i) - e(j, i);
    return err;
  }

  //判断是否相同
  bool operator==(const Matrix44& m) const {
    return memcmp(m.eVec, eVec, sizeof(T) * 4 * 4) == 0;
  }

  //判断是否不等
  bool operator!=(const Matrix44& m) const { return !operator==(m); }

  //赋值
  Matrix44& operator=(const Matrix44& m) {
    memcpy(eVec, m.eVec, sizeof(T) * 16);
    return *this;
  }

  //赋值
  Matrix44& operator=(T val) { return fill(val); }

  //矩阵相加，返回和
  Matrix44 operator+(const Matrix44& m) const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) + m.e(j, i);

    return t;
  }

  //加上一个矩阵
  Matrix44& operator+=(const Matrix44& m) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) += m.e(i, j);
    return *this;
  }

  //矩阵相减，返回差
  Matrix44 operator-(const Matrix44& m) const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) - m.e(j, i);

    return t;
  }

  //减去一个矩阵
  Matrix44& operator-=(const Matrix44& m) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) -= m.e(i, j);
    return *this;
  }

  /// 右剩一矩阵，返回结果矩阵
  Matrix44 operator*(const Matrix44& m) const {
    Matrix44<T> t;
    Matrix44<T>::multiply(t, *this, m);
    return t;
  }

  //右剩矩阵
  Matrix44& operator*=(const Matrix44& m) { return postMultiply(m); }

  //返回各元素相反的矩阵
  Matrix44 operator-() const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = -e(j, i);
    return t;
  }
  const Matrix44& negate() {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) = -(j, i);
    return *this;
  }

  //返回各元素加上指定值的矩阵
  Matrix44 operator+(T d) const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) + d;
    return t;
  }

  //各元素加上指定值
  Matrix44& operator+=(T d) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) += d;
    return *this;
  }

  //返回各元素减去指定值的矩阵
  Matrix44 operator-(T d) const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) - d;
    return t;
  }

  //各元素减去指定值
  Matrix44& operator-=(T d) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) -= d;
    return *this;
  }

  //返回各元素乘以指定值的矩阵
  Matrix44 operator*(T d) const {
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) * d;
    return t;
  }

  //各元素乘以指定值
  Matrix44& operator*=(T d) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) *= d;
    return *this;
  }

  //返回各元素除以指定值的矩阵
  Matrix44 operator/(T d) const {
    d = (T)1 / d;
    Matrix44 t;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        t.e(j, i) = e(j, i) * d;
    return t;
  }

  //各元素除以指定值
  Matrix44& operator/=(T d) {
    d = (T)1 / d;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        e(j, i) *= d;
    return *this;
  }

  //判断是否为单位阵
  bool isIdentity() const {
    Matrix44 i;
    return memcmp(ptr(), i.ptr(), sizeof(T) * 16) == 0;
  }

  //返回首元素指针（左值）
  T* ptr() { return &e(0, 0); }

  //返回首元素指针（右值）
  const T* ptr() const { return &e(0, 0); }

  //转置
  Matrix44& transpose() {
    T tmp;
    for (int i = 0; i < 4; ++i)
      for (int j = i; j < 4; ++j) {
        tmp = e(j, i);
        e(j, i) = e(i, j);
        e(i, j) = tmp;
      }
    return *this;
  }

  //返回对应的转置矩阵（右值）
  Matrix44 getTransposed() const {
    Matrix44 m;
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        m.e(j, i) = e(i, j);
    return m;
  }

  //返回对应的转置矩阵（左值）
  Matrix44& getTransposed(Matrix44& dest) const {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        dest.e(j, i) = e(i, j);
    return dest;
  }

  //是否为空（各元素都为0）
  bool isNull() const {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (e(i, j) != 0)
          return false;
    return true;
  }

  //设置为空（各元素都为0）
  Matrix44& setNull() {
    fill(0);
    return *this;
  }

  //返回一个空矩阵
  static Matrix44& getNull(Matrix44& out) {
    out.fill(0);
    return out;
  }

  //返回一个空矩阵
  static Matrix44 getNull() { return Matrix44().fill(0); }

  //单位化
  Matrix44& setIdentity() {
    static const T I4d[] = {(T)1, (T)0, (T)0, (T)0, (T)0, (T)1, (T)0, (T)0,
                            (T)0, (T)0, (T)1, (T)0, (T)0, (T)0, (T)0, (T)1};
    memcpy(eVec, I4d, sizeof(T) * 16);
    return *this;
  }

  //返回一个单位矩阵
  static Matrix44 getIdentity() { return Matrix44(); }

  //返回一个单位矩阵
  static Matrix44& getIdentity(Matrix44& out) {
    out.setIdentity();
    return out;
  }

  //给定矩阵求逆变换，返回行列式值
  T getInverse(Matrix44& dest) const;

  //求逆矩阵，返回行列式值
  Matrix44 getInverse(T* determinant = nullptr) const {
    Matrix44 tmp;
    T det = getInverse(tmp);
    if (determinant)
      *determinant = det;
    return tmp;
  }

  //求逆，返回行列式值
  Matrix44& invert(T* determinant = nullptr) {
    T det = getInverse(*this);
    if (determinant)
      *determinant = det;
    return *this;
  }
  //求行列式值

  //矩阵相乘：out = p * q （结果矩阵 = 左矩阵 * 右矩阵）
  static Matrix44& multiply(Matrix44& out,
                            const Matrix44& p,
                            const Matrix44& q) {
    assert(out.ptr() != p.ptr() && out.ptr() != q.ptr());

    out.e(0, 0) = q.e(0, 0) * p.e(0, 0) + q.e(1, 0) * p.e(0, 1) +
                  q.e(2, 0) * p.e(0, 2) + q.e(3, 0) * p.e(0, 3);
    out.e(0, 1) = q.e(0, 1) * p.e(0, 0) + q.e(1, 1) * p.e(0, 1) +
                  q.e(2, 1) * p.e(0, 2) + q.e(3, 1) * p.e(0, 3);
    out.e(0, 2) = q.e(0, 2) * p.e(0, 0) + q.e(1, 2) * p.e(0, 1) +
                  q.e(2, 2) * p.e(0, 2) + q.e(3, 2) * p.e(0, 3);
    out.e(0, 3) = q.e(0, 3) * p.e(0, 0) + q.e(1, 3) * p.e(0, 1) +
                  q.e(2, 3) * p.e(0, 2) + q.e(3, 3) * p.e(0, 3);

    out.e(1, 0) = q.e(0, 0) * p.e(1, 0) + q.e(1, 0) * p.e(1, 1) +
                  q.e(2, 0) * p.e(1, 2) + q.e(3, 0) * p.e(1, 3);
    out.e(1, 1) = q.e(0, 1) * p.e(1, 0) + q.e(1, 1) * p.e(1, 1) +
                  q.e(2, 1) * p.e(1, 2) + q.e(3, 1) * p.e(1, 3);
    out.e(1, 2) = q.e(0, 2) * p.e(1, 0) + q.e(1, 2) * p.e(1, 1) +
                  q.e(2, 2) * p.e(1, 2) + q.e(3, 2) * p.e(1, 3);
    out.e(1, 3) = q.e(0, 3) * p.e(1, 0) + q.e(1, 3) * p.e(1, 1) +
                  q.e(2, 3) * p.e(1, 2) + q.e(3, 3) * p.e(1, 3);

    out.e(2, 0) = q.e(0, 0) * p.e(2, 0) + q.e(1, 0) * p.e(2, 1) +
                  q.e(2, 0) * p.e(2, 2) + q.e(3, 0) * p.e(2, 3);
    out.e(2, 1) = q.e(0, 1) * p.e(2, 0) + q.e(1, 1) * p.e(2, 1) +
                  q.e(2, 1) * p.e(2, 2) + q.e(3, 1) * p.e(2, 3);
    out.e(2, 2) = q.e(0, 2) * p.e(2, 0) + q.e(1, 2) * p.e(2, 1) +
                  q.e(2, 2) * p.e(2, 2) + q.e(3, 2) * p.e(2, 3);
    out.e(2, 3) = q.e(0, 3) * p.e(2, 0) + q.e(1, 3) * p.e(2, 1) +
                  q.e(2, 3) * p.e(2, 2) + q.e(3, 3) * p.e(2, 3);

    out.e(3, 0) = q.e(0, 0) * p.e(3, 0) + q.e(1, 0) * p.e(3, 1) +
                  q.e(2, 0) * p.e(3, 2) + q.e(3, 0) * p.e(3, 3);
    out.e(3, 1) = q.e(0, 1) * p.e(3, 0) + q.e(1, 1) * p.e(3, 1) +
                  q.e(2, 1) * p.e(3, 2) + q.e(3, 1) * p.e(3, 3);
    out.e(3, 2) = q.e(0, 2) * p.e(3, 0) + q.e(1, 2) * p.e(3, 1) +
                  q.e(2, 2) * p.e(3, 2) + q.e(3, 2) * p.e(3, 3);
    out.e(3, 3) = q.e(0, 3) * p.e(3, 0) + q.e(1, 3) * p.e(3, 1) +
                  q.e(2, 3) * p.e(3, 2) + q.e(3, 3) * p.e(3, 3);

    return out;
  }

  //右乘一矩阵（当前矩阵 <= 当前矩阵 * m）
  Matrix44& postMultiply(const Matrix44& m) {
    Matrix44<T> t;
    return *this = multiply(t, *this, m);
  }

  //左乘一矩阵（当前矩阵 <= m * 当前矩阵）
  Matrix44& preMultiply(const Matrix44& m) {
    Matrix44<T> t;
    return *this = multiply(t, m, *this);
  }

  //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
  static Matrix44& getRotation(Matrix44& out, T degrees, T x, T y, T z);

  //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
  static Matrix44 getRotation(T degrees, T x, T y, T z) {
    Matrix44 m;
    return getRotation(m, degrees, x, y, z);
  }

  //返回一个绕过原点直线（0，0，0）-（x, y, z）旋转指定角度（度）的旋转矩阵
  static Matrix44 getRotation(T degrees, const Vector3<T>& v) {
    return getRotation(degrees, v.x(), v.y(), v.z());
  }

  //返回一个先绕v2旋转后再绕v1旋转的矩阵
  static Matrix44 getRotation(T degrees1,
                              const Vector3<T>& v1,
                              T degrees2,
                              const Vector3<T>& v2) {
    return getRotation(degrees1, v1.x(), v1.y(), v1.z()) *
           getRotation(degrees2, v2.x(), v2.y(), v2.z());
  }

  //返回一个先绕v3旋转，然后绕v2旋转后再绕v1旋转的矩阵
  static Matrix44 getRotation(T degrees1,
                              const Vector3<T>& v1,
                              T degrees2,
                              const Vector3<T>& v2,
                              T degrees3,
                              const Vector3<T>& v3) {
    return getRotation(degrees1, v1.x(), v1.y(), v1.z()) *
           getRotation(degrees2, v2.x(), v2.y(), v2.z()) *
           getRotation(degrees3, v3.x(), v3.y(), v3.z());
  }

  //绕一过原点直线旋转（当前矩阵被左乘一个旋转矩阵）
  Matrix44& rotate(T degrees, const Vector3<T>& v) {
    return rotate(degrees, v.x(), v.y(), v.z());
  }
  //绕一过原点直线旋转（当前矩阵被左乘一个旋转矩阵）
  Matrix44& rotate(T degrees, T x, T y, T z) {
    return preMultiply(getRotation(degrees, x, y, z));
  }

  //先绕v2旋转后再绕v1旋转
  Matrix44& rotate(T degrees1,
                   const Vector3<T>& v1,
                   T degrees2,
                   const Vector3<T>& v2) {
    return preMultiply(getRotation(degrees1, v1, degrees2, v2));
  }

  //先绕v3旋转，然后绕v2旋转后再绕v1旋转
  Matrix44& rotate(T degrees1,
                   const Vector3<T>& v1,
                   T degrees2,
                   const Vector3<T>& v2,
                   T degrees3,
                   const Vector3<T>& v3) {
    return preMultiply(getRotation(degrees1, v1, degrees2, v2, degrees3, v3));
  }

  //返回一个绕Z轴旋转、再绕Y轴旋转、再绕X轴旋转的矩阵
  static Matrix44 getRotationXYZ(T degX, T degY, T degZ) {
    return getRotation(degX, 1, 0, 0) * getRotation(degY, 0, 1, 0) *
           getRotation(degZ, 0, 0, 1);
  }

  //绕Z轴旋转、再绕Y轴旋转、再绕X轴旋转
  Matrix44& rotateXYZ(T degX, T degY, T degZ) {
    return preMultiply(getRotationXYZ(degX, degY, degZ));
  }

  //返回一个绕X轴旋转、再绕Y轴旋转、再绕Z轴旋转的矩阵
  static Matrix44 getRotationZYX(T degZ, T degY, T degX) {
    return getRotation(degZ, 0, 0, 1) * getRotation(degY, 0, 1, 0) *
           getRotation(degX, 1, 0, 0);
  }

  //绕X轴旋转、再绕Y轴旋转、再绕Z轴旋转
  Matrix44& rotateZYX(T degZ, T degY, T degX) {
    return preMultiply(getRotationZYX(degZ, degY, degX));
  }

  //返回一个从from旋转到to（都是过原点的直线）的矩阵
  static Matrix44& getRotation(Matrix44& out,
                               const Vector3<T>& from,
                               const Vector3<T>& to);

  //返回一个从from旋转到to（都是过原点的直线）的矩阵
  static Matrix44 getRotation(const Vector3<T>& from, const Vector3<T>& to) {
    Matrix44 m;
    return getRotation(m, from, to);
  }

  //从from旋转到to（都是过原点的直线）（当前矩阵左边乘以一个旋转矩阵）
  Matrix44& rotate(const Vector4<T>& from, const Vector4<T>& to) {
    return preMultiply(getRotation(from, to));
  }

  //从from旋转到to（都是过原点的直线）（当前矩阵左边乘以一个旋转矩阵）
  Matrix44& rotate(const Vector3<T>& from, const Vector3<T>& to) {
    return preMultiply(getRotation(from, to));
  }

  //根据平移矢量返回一个平移矩阵（列向量形式）
  static Matrix44& getTranslation(Matrix44& out, const Vector3<T>& v) {
    return getTranslation(out, v.x(), v.y(), v.z());
  }

  //根据平移矢量返回一个平移矩阵（列向量形式）
  static Matrix44 getTranslation(const Vector3<T>& v) {
    Matrix44 m;
    return getTranslation(m, v.x(), v.y(), v.z());
  }

  //根据平移矢量返回一个平移矩阵（列向量形式）
  static Matrix44 getTranslation(T x, T y, T z) {
    Matrix44 m;
    return getTranslation(m, x, y, z);
  }

  //根据平移矢量返回一个平移矩阵（列向量形式，第3列表示平移）
  static Matrix44& getTranslation(Matrix44& out, T x, T y, T z) {
    out.setIdentity();
    out.e(0, 3) = x;
    out.e(1, 3) = y;
    out.e(2, 3) = z;
    return out;
  }

  //平移（根据给定平移矢量）
  Matrix44& translate(T x, T y, T z) {
    return preMultiply(getTranslation(x, y, z));
  }

  //平移（根据给定平移矢量）
  Matrix44& translate(const Vector3<T>& v) {
    return preMultiply(getTranslation(v));
  }

  //根据比例系数返回一个比例变换矩阵
  static Matrix44& getScaling(Matrix44& out, const Vector3<T>& v) {
    return getScaling(out, v.x(), v.y(), v.z());
  }

  //根据比例系数返回一个比例变换矩阵
  static Matrix44 getScaling(const Vector3<T>& v) {
    Matrix44 m;
    return getScaling(m, v.x(), v.y(), v.z());
  }

  //根据比例系数返回一个比例变换矩阵
  static Matrix44 getScaling(T x, T y, T z) {
    Matrix44 m;
    return getScaling(m, x, y, z);
  }

  //根据比例系数返回一个比例变换矩阵
  static Matrix44& getScaling(Matrix44& out, T x, T y, T z) {
    out.setIdentity();
    out.e(0, 0) = x;
    out.e(1, 1) = y;
    out.e(2, 2) = z;
    return out;
  }

  //根据比例系数进行比例变换（左乘一个比例变换矩阵）
  Matrix44& scale(T x, T y, T z) { return preMultiply(getScaling(x, y, z)); }

  //根据比例系数进行比例变换（左乘一个比例变换矩阵）
  Matrix44& scale(const Vector3<T> v) {
    return preMultiply(getScaling(v.x(), v.y(), v.z()));
  }

  //根据观察体参数返回一个透视投影矩阵
  static Matrix44 getPerspective(T fovy, T aspect_ratio, T znear, T zfar);

  //根据观察体参数返回一个透视投影矩阵
  static Matrix44 getFrustum(T pleft,
                             T pright,
                             T pbottom,
                             T ptop,
                             T pnear,
                             T pfar);

  //根据观察体参数返回一个正交投影矩阵
  static Matrix44 getOrtho(T pleft,
                           T pright,
                           T pbottom,
                           T ptop,
                           T pnear,
                           T pfar);

  //根据观察体参数返回一个正交投影矩阵
  static Matrix44 getOrtho2D(T pleft, T pright, T pbottom, T ptop);

  //返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
  static Matrix44 getLookAtModeling(const Vector3<T>& eye,
                                    const Vector3<T>& at,
                                    const Vector3<T>& up);

  //返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
  static Matrix44 getLookAt(const Vector3<T>& eye,
                            const Vector3<T>& at,
                            const Vector3<T>& up);

  //获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
  void getAsLookAtModeling(Vector3<T>& eye,
                           Vector3<T>& at,
                           Vector3<T>& up,
                           Vector3<T>& right) const;

  //获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
  void getAsLookAt(Vector3<T>& eye,
                   Vector3<T>& at,
                   Vector3<T>& up,
                   Vector3<T>& right) const;

  //如果矩阵可以表示为旋转，返回绕Y轴和绕X轴的角度（度）
  //! - -180 <= degrees_y <= 180
  //! - -180 <= degrees_x <= 180 and degrees_x != 90
  void getYXRotationAngles(T& degrees_y, T& degrees_x) const;

  //返回关于XOY平面对称的对称变换矩阵
  static Matrix44 getMirrorXOY() {
    Matrix44 m;
    m.e(2, 2) = (T)-1;
    return m;
  }

  //返回关于YOZ平面对称的对称变换矩阵
  static Matrix44 getMirrorYOZ() {
    Matrix44 m;
    m.e(0, 0) = (T)-1;
    return m;
  }

  //返回关于XOZ平面对称的对称变换矩阵
  static Matrix44 getMirrorXOZ() {
    Matrix44 m;
    m.e(1, 1) = (T)-1;
    return m;
  }

  //关于X轴对称
  static Matrix44 getMirrorXAxis() {
    Matrix44 m;
    m.e(1, 1) = (T)-1;
    m.e(2, 2) = (T)-1;
    return m;
  }

  //关于Y轴对称
  static Matrix44 getMirrorYAxis() {
    Matrix44 m;
    m.e(0, 0) = (T)-1;
    m.e(2, 2) = (T)-1;
    return m;
  }

  //关于Z轴对称
  static Matrix44 getMirrorZAxis() {
    Matrix44 m;
    m.e(0, 0) = (T)-1;
    m.e(1, 1) = (T)-1;
    return m;
  }

  //关于原点对称
  static Matrix44 getMirrorOrigin() {
    Matrix44 m;
    m.e(0, 0) = (T)-1;
    m.e(1, 1) = (T)-1;
    m.e(2, 2) = (T)-1;
    return m;
  }

  //沿X含Y错切
  static Matrix44 getShearXY(T sh) {
    Matrix44 m;
    m.e(0, 1) = sh;
    return m;
  }

  //沿X含Z错切
  static Matrix44 getShearXZ(T sh) {
    Matrix44 m;
    m.e(0, 2) = sh;
    return m;
  }

  //沿Y含X错切
  static Matrix44 getShearYX(T sh) {
    Matrix44 m;
    m.e(1, 0) = sh;
    return m;
  }

  //沿Y含Z错切
  static Matrix44 getShearYZ(T sh) {
    Matrix44 m;
    m.e(1, 2) = sh;
    return m;
  }

  //沿Z含X错切
  static Matrix44 getShearZX(T sh) {
    Matrix44 m;
    m.e(2, 0) = sh;
    return m;
  }

  //沿Z含Y错切
  static Matrix44 getShearZY(T sh) {
    Matrix44 m;
    m.e(2, 1) = sh;
    return m;
  }

  //返回指定行列的元素（右值）
  const T& e(int i, int j) const { return eVec[j][i]; }

  //返回指定行列的元素（左值）
  T& e(int i, int j) { return eVec[j][i]; }

  // abs (this[i][j] - m[i][j]) <= e
  bool equalAbsWithTol(const Matrix44& m, T e) const {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (!equalAbsWithTo((*this)[i][j], m[i][j], e))
          return false;

    return true;
  }
  // abs (this[i] - v[i][j]) <= e * abs (this[i][j])
  bool equalRelWithTol(const Matrix44& m, T e) const {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (!equalRelWithTo((*this)[i][j], m[i][j], e))
          return false;

    return true;
  }

  //返回矩阵维数
  static unsigned int dimensions() { return 4; }

 private:
  const Vector4<T>& operator[](unsigned int i) const {
    assert(i < 4);
    return eVec[i];
  }
  Vector4<T>& operator[](unsigned int i) {
    assert(i < 4);
    return eVec[i];
  }

 protected:
  Vector4<T> eVec[4];  //列向量
};

//返回两矩阵的积（p * q）
template <typename T>
inline Matrix44<T> operator*(const Matrix44<T>& p, const Matrix44<T>& q);

//返回值与矩阵的和（T + q），q的各元素加上指定值。
template <typename T>
inline Matrix44<T> operator+(T d, const Matrix44<T>& m);

//返回值与矩阵的积（T * q），q的各元素乘以指定值。
template <typename T>
inline Matrix44<T> operator*(T d, const Matrix44<T>& m);

//! 给定矩阵右边右乘一个Vector4列向量，返回结果列向量Vector4
template <typename T>
inline Vector4<T> operator*(const Matrix44<T>& m, const Vector4<T>& v);

//! 给定矩阵右边右乘一个Vector3列向量（假定w=1），返回结果列向量Vector3
template <typename T>
inline Vector3<T> operator*(const Matrix44<T>& m, const Vector3<T>& v);

//! 给定矩阵右边右乘一个Vector2列向量（假定z = 0, w=1），返回结果列向量Vector2
template <typename T>
inline Vector2<T> operator*(const Matrix44<T>& m, const Vector2<T>& v);

//! 行向量右边乘一个矩阵，返回结果行向量（左值）
template <typename T, typename S>
inline Vector4<T>& operator*=(Vector4<T>& v, const Matrix44<S>& m);

//! 行向量右边乘一个矩阵，返回结果行向量（右值）
template <typename T, typename S>
inline Vector4<T> operator*(const Vector4<T>& v, const Matrix44<S>& m);

//! 行向量Vector3（用作Vector4，w =
//! 1）右乘一个矩阵，返回结果行向量Vector3（左值）
template <typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix44<S>& m);

//! 行向量Vector3（用作Vector4，w =
//! 1）右乘一个矩阵，返回结果行向量Vector3（右值）
template <typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix44<S>& m);

//! 行向量Vector2（用作Vector4，z = 0，w =
//! 1）右乘一个矩阵，返回结果行向量Vector2（右值）
template <typename T>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix44<T>& m);

//返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
template <typename T>
Matrix44<T> Matrix44<T>::getLookAtModeling(const Vector3<T>& eye,
                                           const Vector3<T>& at,
                                           const Vector3<T>& up);

//返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
template <typename T>
Matrix44<T> Matrix44<T>::getLookAt(const Vector3<T>& eye,
                                   const Vector3<T>& at,
                                   const Vector3<T>& up);

//获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
template <typename T>
void Matrix44<T>::getAsLookAtModeling(Vector3<T>& eye,
                                      Vector3<T>& at,
                                      Vector3<T>& up,
                                      Vector3<T>& right) const;

//获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
template <typename T>
void Matrix44<T>::getAsLookAt(Vector3<T>& eye,
                              Vector3<T>& at,
                              Vector3<T>& up,
                              Vector3<T>& right) const;

//根据观察体参数返回一个透视投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getPerspective(T fovy,
                                        T aspect_ratio,
                                        T znear,
                                        T zfar);

//根据观察体参数返回一个透视投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getFrustum(T left,
                                    T right,
                                    T bottom,
                                    T top,
                                    T pnear,
                                    T pfar);

//根据观察体参数返回一个正交投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getOrtho(T left,
                                  T right,
                                  T bottom,
                                  T top,
                                  T pnear,
                                  T pfar);

//根据观察体参数返回一个正交投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getOrtho2D(T left, T right, T bottom, T top);

//返回一个绕过原点的直线旋转的矩阵
template <typename T>
Matrix44<T>& Matrix44<T>::getRotation(Matrix44<T>& out,
                                      T degrees,
                                      T x,
                                      T y,
                                      T z);

//给定矩阵求逆变换，返回行列式值
template <typename T>
T Matrix44<T>::getInverse(Matrix44<T>& dest) const;

//返回一个从from旋转到to（都是过原点的直线）的矩阵
template <typename T>
Matrix44<T>& Matrix44<T>::getRotation(Matrix44<T>& out,
                                      const Vector3<T>& from,
                                      const Vector3<T>& to);

//! 如果矩阵可以表示为旋转，返回绕Y轴和绕X轴的角度（度）
//! - -180 <= degrees_y <= 180
//! - -180 <= degrees_x <= 180 and degrees_x != 90
template <typename T>
void Matrix44<T>::getYXRotationAngles(T& degrees_y, T& degrees_x) const;

//具体实现

//返回两矩阵的积（p * q）
template <typename T>
inline Matrix44<T> operator*(const Matrix44<T>& p, const Matrix44<T>& q) {
  Matrix44<T> t;
  Matrix44<T>::multiply(t, p, q);
  return t;
}

//返回值与矩阵的和（T + q），q的各元素加上指定值。
template <typename T>
inline Matrix44<T> operator+(T d, const Matrix44<T>& m) {
  return m + d;
}

//返回值与矩阵的积（T * q），q的各元素乘以指定值。
template <typename T>
inline Matrix44<T> operator*(T d, const Matrix44<T>& m) {
  return m * d;
}

//! 给定矩阵右边右乘一个Vector4列向量，返回结果列向量Vector4
template <typename T>
inline Vector4<T> operator*(const Matrix44<T>& m, const Vector4<T>& v) {
  return Vector4<T>(v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2) +
                        v.w() * m.e(0, 3),
                    v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2) +
                        v.w() * m.e(1, 3),
                    v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2) +
                        v.w() * m.e(2, 3),
                    v.x() * m.e(3, 0) + v.y() * m.e(3, 1) + v.z() * m.e(3, 2) +
                        v.w() * m.e(3, 3));
}

//! 给定矩阵右边右乘一个Vector3列向量（假定w=1），返回结果列向量Vector3
template <typename T>
inline Vector3<T> operator*(const Matrix44<T>& m, const Vector3<T>& v) {
  return Vector3<T>(v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + v.z() * m.e(0, 2) +
                        /*1**/ m.e(0, 3),
                    v.x() * m.e(1, 0) + v.y() * m.e(1, 1) + v.z() * m.e(1, 2) +
                        /*1**/ m.e(1, 3),
                    v.x() * m.e(2, 0) + v.y() * m.e(2, 1) + v.z() * m.e(2, 2) +
                        /*1**/ m.e(2, 3));
}

//! 给定矩阵右边右乘一个Vector2列向量（假定z = 0, w=1），返回结果列向量Vector2
template <typename T>
inline Vector2<T> operator*(const Matrix44<T>& m, const Vector2<T>& v) {
  return Vector2<T>(
      v.x() * m.e(0, 0) + v.y() * m.e(0, 1) + /*0*m.e(0,2) +*/ /*1**/ m.e(0, 3),
      v.x() * m.e(1, 0) + v.y() * m.e(1, 1) +
          /*0*m.e(1,2) +*/ /*1**/ m.e(1, 3));
}

//! 行向量右边乘一个矩阵，返回结果行向量（左值）
template <typename T, typename S>
inline Vector4<T>& operator*=(Vector4<T>& v, const Matrix44<S>& m) {
  T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) +
          v.w() * m.e(3, 0));
  T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) +
          v.w() * m.e(3, 1));
  T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) +
          v.w() * m.e(3, 2));
  T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) +
          v.w() * m.e(3, 3));
  v.x() = x;
  v.y() = y;
  v.z() = z;
  v.w() = w;
  return v;
}

//! 行向量右边乘一个矩阵，返回结果行向量（右值）
template <typename T, typename S>
inline Vector4<T> operator*(const Vector4<T>& v, const Matrix44<S>& m) {
  return Vector4<T>(T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) +
                      v.z() * m.e(2, 0) + v.w() * m.e(3, 0)),
                    T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) +
                      v.z() * m.e(2, 1) + v.w() * m.e(3, 1)),
                    T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) +
                      v.z() * m.e(2, 2) + v.w() * m.e(3, 2)),
                    T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) +
                      v.z() * m.e(2, 3) + v.w() * m.e(3, 3)));
}

//! 行向量Vector3（用作Vector4，w =
//! 1）右乘一个矩阵，返回结果行向量Vector3（左值）
template <typename T, typename S>
inline Vector3<T>& operator*=(Vector3<T>& v, const Matrix44<S>& m) {
  T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) +
          /*1**/ m.e(3, 0));
  T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) +
          /*1**/ m.e(3, 1));
  T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) +
          /*1**/ m.e(3, 2));
  T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) +
          /*1**/ m.e(3, 3));

  v.x() = x;  // v.x() = x / w;
  v.y() = y;  // v.y() = y / w;
  v.z() = z;  // v.z() = z / w;

  return v;
}

//! 行向量Vector3（用作Vector4，w =
//! 1）右乘一个矩阵，返回结果行向量Vector3（右值）
template <typename T, typename S>
inline Vector3<T> operator*(const Vector3<T>& v, const Matrix44<S>& m) {
  T x = T(v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + v.z() * m.e(2, 0) +
          /*1**/ m.e(3, 0));
  T y = T(v.x() * m.e(0, 1) + v.y() * m.e(1, 1) + v.z() * m.e(2, 1) +
          /*1**/ m.e(3, 1));
  T z = T(v.x() * m.e(0, 2) + v.y() * m.e(1, 2) + v.z() * m.e(2, 2) +
          /*1**/ m.e(3, 2));
  T w = T(v.x() * m.e(0, 3) + v.y() * m.e(1, 3) + v.z() * m.e(2, 3) +
          /*1**/ m.e(3, 3));

  return Vector3<T>(x, y, z);
  // return Vector3<T>(x / w, y / w, z / w);
}

//! 行向量Vector2（用作Vector4，z = 0，w =
//! 1）右乘一个矩阵，返回结果行向量Vector2（右值）
template <typename T>
inline Vector2<T> operator*(const Vector2<T>& v, const Matrix44<T>& m) {
  return Vector2<T>(
      v.x() * m.e(0, 0) + v.y() * m.e(1, 0) + /*0*m.e(2,0) +*/ /*1**/ m.e(3, 0),
      v.x() * m.e(0, 1) + v.y() * m.e(1, 1) +
          /*0*m.e(2,1) +*/ /*1**/ m.e(3, 1));
}

//返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
template <typename T>
Matrix44<T> Matrix44<T>::getLookAtModeling(const Vector3<T>& eye,
                                           const Vector3<T>& at,
                                           const Vector3<T>& up) {
  Vector3<T> zaxis = (eye - at).normalize();
  Vector3<T> xaxis = cross(up, zaxis).normalize();
  Vector3<T> yaxis = cross(zaxis, xaxis);

  // look at modeling
  T la_modeling[] = {
      xaxis.x(), xaxis.y(), xaxis.z(), 0, yaxis.x(), yaxis.y(), yaxis.z(), 0,
      zaxis.x(), zaxis.y(), zaxis.z(), 0, eye.x(),   eye.y(),   eye.z(),   1};

  return Matrix44<T>(la_modeling);
}

//返回一个观察变换矩阵（根据相机参数：位置、参考点、向上方向）
template <typename T>
Matrix44<T> Matrix44<T>::getLookAt(const Vector3<T>& eye,
                                   const Vector3<T>& at,
                                   const Vector3<T>& up) {
  Vector3<T> zaxis = (eye - at).normalize();
  Vector3<T> xaxis = cross(up, zaxis).normalize();
  Vector3<T> yaxis = cross(zaxis, xaxis);

  // look at view
  T la_view[] = {xaxis.x(),        yaxis.x(),        zaxis.x(),        0,
                 xaxis.y(),        yaxis.y(),        zaxis.y(),        0,
                 xaxis.z(),        yaxis.z(),        zaxis.z(),        0,
                 -dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1};

  return Matrix44<T>(la_view);
}

//获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
template <typename T>
void Matrix44<T>::getAsLookAtModeling(Vector3<T>& eye,
                                      Vector3<T>& at,
                                      Vector3<T>& up,
                                      Vector3<T>& right) const {
  eye = getT();

  at = -getZ();
  // look.normalize();

  up = getY();
  // up.normalize();

  right = getX();
  // right.normalize();
}

//获取当前作为观察矩阵的观察参数（相机位置、参考点、向上方向、X轴方向（向右方向））
template <typename T>
void Matrix44<T>::getAsLookAt(Vector3<T>& eye,
                              Vector3<T>& at,
                              Vector3<T>& up,
                              Vector3<T>& right) const {
  Matrix44<T> m = *this;
  m.invert();
  m.getAsLookAtModeling(eye, at, up, right);
}

//根据观察体参数返回一个透视投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getPerspective(T fovy,
                                        T aspect_ratio,
                                        T znear,
                                        T zfar) {
  Matrix44<T> m;

  T rads = (fovy / ((T)2)) * (T)dDEG_TO_RAD;
  T dz = zfar - znear;
  T sa = sin(rads);
  if ((dz == 0) || (sa == 0) || (aspect_ratio == 0))
    return m * 0;
  T ctan = cos(rads) / sa;

  m.e(0, 0) = (T)(ctan / aspect_ratio);
  m.e(1, 1) = (T)(ctan);
  m.e(2, 2) = (T)(-(zfar + znear) / dz);
  m.e(3, 2) = -((T)1);
  m.e(2, 3) = (T)(-((T)2) * znear * zfar / dz);
  m.e(3, 3) = 0;

  return m;
}

//根据观察体参数返回一个透视投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getFrustum(T left,
                                    T right,
                                    T bottom,
                                    T top,
                                    T pnear,
                                    T pfar) {
  Matrix44<T> m;

  if (pnear <= 0 || pfar <= 0 || pnear == pfar || left == right ||
      top == bottom)
    return m * 0;

  T x = (((T)2) * pnear) / (right - left);
  T y = (((T)2) * pnear) / (top - bottom);
  T a = (right + left) / (right - left);
  T b = (top + bottom) / (top - bottom);
  T c = -(pfar + pnear) / (pfar - pnear);
  T d = -(((T)2) * pfar * pnear) / (pfar - pnear);

  m.e(0, 0) = x;
  m.e(0, 1) = 0;
  m.e(0, 2) = a;
  m.e(0, 3) = 0;
  m.e(1, 0) = 0;
  m.e(1, 1) = y;
  m.e(1, 2) = b;
  m.e(1, 3) = 0;
  m.e(2, 0) = 0;
  m.e(2, 1) = 0;
  m.e(2, 2) = c;
  m.e(2, 3) = d;
  m.e(3, 0) = 0;
  m.e(3, 1) = 0;
  m.e(3, 2) = -((T)1);
  m.e(3, 3) = 0;

  return m;
}

//根据观察体参数返回一个正交投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getOrtho(T left,
                                  T right,
                                  T bottom,
                                  T top,
                                  T pnear,
                                  T pfar) {
  Matrix44<T> m;

  m.e(0, 0) = ((T)2) / (right - left);
  m.e(0, 1) = 0;
  m.e(0, 2) = 0;
  m.e(0, 3) = -(right + left) / (right - left);

  m.e(1, 0) = 0;
  m.e(1, 1) = ((T)2) / (top - bottom);
  m.e(1, 2) = 0;
  m.e(1, 3) = -(top + bottom) / (top - bottom);

  m.e(2, 0) = 0;
  m.e(2, 1) = 0;
  m.e(2, 2) = -((T)2) / (pfar - pnear);
  m.e(2, 3) = -(pfar + pnear) / (pfar - pnear);

  m.e(3, 0) = 0;
  m.e(3, 1) = 0;
  m.e(3, 2) = 0;
  m.e(3, 3) = ((T)1);

  return m;
}

//根据观察体参数返回一个正交投影矩阵
template <typename T>
Matrix44<T> Matrix44<T>::getOrtho2D(T left, T right, T bottom, T top) {
  return getOrtho(left, right, bottom, top, -1, +1);
}

//返回一个绕过原点的直线旋转的矩阵
template <typename T>
Matrix44<T>& Matrix44<T>::getRotation(Matrix44<T>& out,
                                      T degrees,
                                      T x,
                                      T y,
                                      T z) {
  out.setIdentity();

  if (degrees == 0 || (x == 0 && y == 0 && z == 0))
    return out;

  degrees = T(degrees * dDEG_TO_RAD);

  T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;

  s = (T)sin(degrees);
  c = (T)cos(degrees);

  // simple cases
  if (x == 0) {
    if (y == 0) {
      if (z != 0) {
        // rotate only around z-axis
        out.e(0, 0) = (T)c;
        out.e(1, 1) = (T)c;
        if (z < 0) {
          out.e(1, 0) = -(T)s;
          out.e(0, 1) = (T)s;
        } else {
          out.e(1, 0) = (T)s;
          out.e(0, 1) = -(T)s;
        }
        return out;
      }
    } else if (z == 0) {
      // rotate only around y-axis
      out.e(0, 0) = (T)c;
      out.e(2, 2) = (T)c;
      if (y < 0) {
        out.e(2, 0) = (T)s;
        out.e(0, 2) = -(T)s;
      } else {
        out.e(2, 0) = -(T)s;
        out.e(0, 2) = (T)s;
      }
      return out;
    }
  } else if (y == 0) {
    if (z == 0) {
      // rotate only around x-axis
      out.e(1, 1) = (T)c;
      out.e(2, 2) = (T)c;
      if (x < 0) {
        out.e(2, 1) = -(T)s;
        out.e(1, 2) = (T)s;
      } else {
        out.e(2, 1) = (T)s;
        out.e(1, 2) = -(T)s;
      }
      return out;
    }
  }

  // Beginning of general axisa to matrix conversion
  T dot = x * x + y * y + z * z;

  if (dot > (T)((T)1.0001) || dot < (T)0.99999) {
    T mag = (T)sqrt(dot);
    x /= mag;
    y /= mag;
    z /= mag;
  }

  xx = x * x;
  yy = y * y;
  zz = z * z;
  xy = x * y;
  yz = y * z;
  zx = z * x;
  xs = x * s;
  ys = y * s;
  zs = z * s;
  one_c = ((T)1) - c;

  out.e(0, 0) = (T)((one_c * xx) + c);
  out.e(1, 0) = (T)((one_c * xy) + zs);
  out.e(2, 0) = (T)((one_c * zx) - ys);
  out.e(0, 1) = (T)((one_c * xy) - zs);
  out.e(1, 1) = (T)((one_c * yy) + c);
  out.e(2, 1) = (T)((one_c * yz) + xs);
  out.e(0, 2) = (T)((one_c * zx) + ys);
  out.e(1, 2) = (T)((one_c * yz) - xs);
  out.e(2, 2) = (T)((one_c * zz) + c);
  return out;
}

//给定矩阵求逆变换，返回行列式值
template <typename T>
T Matrix44<T>::getInverse(Matrix44<T>& dest) const {
  const T* in = ptr();
  T* out = dest.ptr();

  // | 0 | 4 | 8  | 12 |
  // | 1 | 5 | 9  | 13 |
  // | 2 | 6 | 10 | 14 |
  // | 3 | 7 | 11 | 15 |

  // | a | b | c | d |
  // | e | f | g | h |
  // | i | l | m | n |
  // | o | p | q | r |

  const T a = in[0];
  const T b = in[4];
  const T c = in[8];
  const T d = in[12];
  const T e = in[1];
  const T f = in[5];
  const T g = in[9];
  const T h = in[13];
  const T i = in[2];
  const T l = in[6];
  const T m = in[10];
  const T n = in[14];
  const T o = in[3];
  const T p = in[7];
  const T q = in[11];
  const T r = in[15];

  // 3x3 determinant:
  //
  //   [ a b c ]
  //   [ d e f ] = aei - ahf + dhc - dbi + gbf - gec = (aei + dhc + gbf) - (ahf
  //   + dbi + gec) [ g h i ]

  const T mr = m * r;
  const T gn = g * n;
  const T el = e * l;
  const T ip = i * p;
  const T mo = m * o;
  const T hl = h * l;
  const T mp = m * p;
  const T nq = n * q;
  const T gl = g * l;
  const T no = n * o;
  const T gi = g * i;
  const T np = n * p;
  const T fi = f * i;
  const T rc = r * c;
  const T be = b * e;
  const T af = a * f;
  const T de = d * e;
  const T df = d * f;
  const T ch = c * h;
  const T qh = q * h;

  // | f | g | h |
  // | l | m | n |
  // | p | q | r |
  T Ca = +((f * mr + gn * p + hl * q) - (h * mp + nq * f + r * gl));

  // | e | g | h |
  // | i | m | n |
  // | o | q | r |
  T Cb = -((e * mr + gn * o + i * qh) - (h * mo + gi * r + nq * e));

  // | e | f | h |
  // | i | l | n |
  // | o | p | r |
  T Cc = +((el * r + ip * h + f * no) - (hl * o + np * e + fi * r));

  // | e | f | g |
  // | i | l | m |
  // | o | p | q |
  T Cd = -((el * q + f * mo + g * ip) - (gl * o + mp * e + q * fi));

  T det = a * Ca + b * Cb + c * Cc + d * Cd;

  // singular matrix
  if (det == 0)
    return det;

  // | b | c | d |
  // | l | m | n |
  // | p | q | r |
  T Ce = -((b * mr + c * np + d * l * q) - (d * mp + nq * b + rc * l));

  // | a | c | d |
  // | i | m | n |
  // | o | q | r |
  T Cf = +((a * mr + c * no + d * i * q) - (d * mo + nq * a + rc * i));

  // | a | b | d |
  // | i | l | n |
  // | o | p | r |
  T Cg = -((a * l * r + b * no + d * ip) - (d * l * o + np * a + r * b * i));

  // | a | b | c |
  // | i | l | m |
  // | o | p | q |
  T Ch = +((a * l * q + b * mo + c * ip) - (c * l * o + mp * a + q * b * i));

  // | b | c | d |
  // | f | g | h |
  // | p | q | r |
  T Ci = +((b * g * r + ch * p + df * q) - (d * g * p + q * h * b + rc * f));

  // | a | c | d |
  // | e | g | h |
  // | o | q | r |
  T Cl = -((a * g * r + ch * o + de * q) - (d * g * o + qh * a + rc * e));

  // | a | b | d |
  // | e | f | h |
  // | o | p | r |
  T Cm = +((af * r + b * h * o + de * p) - (df * o + h * p * a + r * be));

  // | a | b | c |
  // | e | f | g |
  // | o | p | q |
  T Cn = -((af * q + b * g * o + c * e * p) - (c * f * o + g * p * a + q * be));

  // | b | c | d |
  // | f | g | h |
  // | l | m | n |
  T Co = -((b * gn + c * hl + df * m) - (d * gl + h * m * b + n * c * f));

  // | a | c | d |
  // | e | g | h |
  // | i | m | n |
  T Cp = +((a * gn + ch * i + de * m) - (d * gi + h * m * a + n * c * e));

  // | a | b | d |
  // | e | f | h |
  // | i | l | n |
  T Cq = -((af * n + b * h * i + d * el) - (d * fi + hl * a + n * be));

  // | a | b | c |
  // | e | f | g |
  // | i | l | m |
  T Cr = +((af * m + b * gi + c * el) - (c * fi + gl * a + m * be));

#if 0
    T det2 = e * Ce + f * Cf + g * Cg + h * Ch;
    T det3 = i * Ci + l * Cl + m * Cm + n * Cn;
    T det4 = o * Co + p * Cp + q * Cq + r * Cr;
    assert(fabs(det - det1) < 0.0001);
    assert(fabs(det - det3) < 0.0001);
    assert(fabs(det - det4) < 0.0001);
#endif

  T inv_det = 1 / det;

  out[0] = inv_det * Ca;
  out[1] = inv_det * Cb;
  out[2] = inv_det * Cc;
  out[3] = inv_det * Cd;
  out[4] = inv_det * Ce;
  out[5] = inv_det * Cf;
  out[6] = inv_det * Cg;
  out[7] = inv_det * Ch;
  out[8] = inv_det * Ci;
  out[9] = inv_det * Cl;
  out[10] = inv_det * Cm;
  out[11] = inv_det * Cn;
  out[12] = inv_det * Co;
  out[13] = inv_det * Cp;
  out[14] = inv_det * Cq;
  out[15] = inv_det * Cr;

  return det;
}

//返回一个从from旋转到to（都是过原点的直线）的矩阵
template <typename T>
Matrix44<T>& Matrix44<T>::getRotation(Matrix44<T>& out,
                                      const Vector3<T>& from,
                                      const Vector3<T>& to) {
  Vector3<T> a, b;
  a = from;
  b = to;
  a.normalize();
  b.normalize();
  T cosa = dot(a, b);
  cosa = clamp(cosa, -((T)1), +((T)1));
  Vector3<T> axis, n2;
  axis = cross(a, b);
  axis.normalize();
  T alpha = acos(cosa);
  return getRotation(out, alpha * (T)dRAD_TO_DEG, axis.x(), axis.y(), axis.z());
}

//! 如果矩阵可以表示为旋转，返回绕Y轴和绕X轴的角度（度）
//! - -180 <= degrees_y <= 180
//! - -180 <= degrees_x <= 180 and degrees_x != 90
template <typename T>
void Matrix44<T>::getYXRotationAngles(T& degrees_y, T& degrees_x) const {
  Vector3<T> vx = getX();
  Vector3<T> vy = getY();
  Vector3<T> vz = getZ();

  vx.normalize();
  vy.normalize();
  vz.normalize();

  T kx = dot(vy, Vector3<T>(0, 1, 0));
  kx = clamp(kx, -((T)1), +((T)1));
  degrees_x = acos(kx) * (T)dRAD_TO_DEG;
  if (dot(vz, Vector3<T>(0, 1, 0)) > 0)
    degrees_x = -degrees_x;

  T ky = dot(vx, Vector3<T>(1, 0, 0));
  ky = clamp(ky, -((T)1), +((T)1));
  degrees_y = acos(ky) * (T)dRAD_TO_DEG;
  if (dot(vz, Vector3<T>(1, 0, 0)) < 0)
    degrees_y = -degrees_y;
  if (fabs(degrees_x) > (T)90)
    degrees_y = -degrees_y;
}

typedef Matrix44<int> Mat4i;
typedef Matrix44<float> Mat4f;
typedef Matrix44<double> Mat4d;

typedef Mat4d Mat4;

#endif  //_MATRIX44_H_INCLUDED