#ifndef _CG2DCIRCLE_H_INCLUDED
#define _CG2DCIRCLE_H_INCLUDED
#pragma once
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DCircle : public CG2DRenderable {
  DECLARE_SERIAL(CG2DCircle)
 public:
  CG2DCircle();
  CG2DCircle(const Vec2d& Center, double r);
  virtual ~CG2DCircle();
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
 protected:
  Vec2d mCenter;
  double mRadius;
  double mXRadius;
  double mYRadius;
};
#endif  //_CG2DCIRCLE_H_INCLUDED
