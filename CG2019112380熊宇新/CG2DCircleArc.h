#ifndef _CG2DCIRCLEARC_H_INCLUDED
#define _CG2DCIRCLEARC_H_INCLUDED
#pragma once
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DCircleArc : public CG2DRenderable {
  DECLARE_SERIAL(CG2DCircleArc)
 public:
  CG2DCircleArc();
  CG2DCircleArc(const Vec2d& mCenter,
                const Vec2d& mStart,
                const Vec2d& mEnd,
                bool d);
  virtual ~CG2DCircleArc();
  //序列化
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  virtual void ComputeBounds();
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
  virtual void Transform(const Mat3d& mat);  //几何变换（左乘给定矩阵）
 protected:
  Vec2d mCenter;
  Vec2d mStart;
  Vec2d mEnd;
  double mRadius;
  double XRadius;
  double YRadius;
  bool direction;

};
#endif  //_CG2DCIRCLEARC_H_INCLUDED
