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
  //���л�
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  virtual void ComputeBounds();
  virtual void Translate(double tx, double ty);  //ƽ��
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //��ת����ʱ��Ϊ�����ȣ�
  virtual void Scale(double sx, double sy);  //����
  virtual void MirrorXAxis();    //����X��Գƣ���ά����ά��
  virtual void MirrorYAxis();    //����Y��Գƣ���ά����ά��
  virtual void MirrorYeqPosX();  //����y=x�Գƣ���ά����ά��
  virtual void MirrorYeNegPX();  //����y=-x�Գƣ���ά����ά��
  virtual void MirrorOrigin();   //����ԭ��Գƣ���ά����ά��
 protected:
  Vec2d mCenter;
  double mRadius;
  double mXRadius;
  double mYRadius;
};
#endif  //_CG2DCIRCLE_H_INCLUDED
