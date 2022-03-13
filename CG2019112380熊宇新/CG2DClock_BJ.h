#ifndef _CG2DCLOCK_H_INCLUDED
#define _CG2DCLOCK_H_INCLUDED
#pragma once
#include "CG2DRenderable.h"
class CG2DClock_BJ : public CG2DRenderable {
  DECLARE_SERIAL(CG2DClock_BJ)
 public:
  CG2DClock_BJ();
  CG2DClock_BJ(const Vec2d& mStart,
                   const Vec2d& mEnd,
                   const Vec2d& mDis10);
  virtual ~CG2DClock_BJ();
  //序列化
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

  virtual ABox2d& BoundingABox();  // AABB包围盒，可用于设置
  virtual void ComputeBounds();    //计算包围盒
  virtual void Translate(double tx, double ty);  //平移
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //旋转（逆时针为正，度）
  virtual void Scale(double sx, double sy);  //缩放
  virtual void MirrorXAxis();    //关于X轴对称（二维、三维）
  virtual void MirrorYAxis();    //关于Y轴对称（二维、三维）
  virtual void MirrorYeqPosX();  //关于y=x对称（二维、三维）
  virtual void MirrorYeNegPX();  //关于y=-x对称（二维、三维）
  virtual void MirrorOrigin();   //关于原点对称（二维、三维）
  virtual void Mirror(Vec2d& v1, Vec2d& v2);
  virtual void ShearXAxis(double shx);               //沿X轴错切
  virtual void ShearYAxis(double shy);               //沿Y轴错切
  virtual void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切
  virtual void Transform(const Mat3d& mat);  //几何变换（左乘给定矩阵）

  virtual bool Picked(const Vec2d& p, double radius);  //是否拾取到

 protected:
  Vec2d mStart, mEnd, mCenter;
  Vec2d cStart, cEnd, cCenter;
  Vec2d cDis10;
  Vec2d cRect1, cRect2, cRect3, cRect4;
  Vec2d mRect1, mRect2, mRect3, mRect4;
  Vec2d cFenceLU, cFenceLD, cFenceRU, cFenceRD;
  Vec2d mFenceLU, mFenceLD, mFenceRU, mFenceRD;
  Vec2d cClock1, cClock2, cClock3;
  Vec2d mClock1, mClock2, mClock3;
  double cdis10;
  double cXRadius, cYRadius, cRadius;
  double mXRadius, mYRadius, mRadius;
  Vec2d cOutScale[60], mOutScale[60];
  Vec2d cInScale[60], mInScale[60];
};

#endif  //_CG2DCLOCK_H_INCLUDE