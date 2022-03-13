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
  virtual void Transform(const Mat3d& mat);  //���α任����˸�������
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
