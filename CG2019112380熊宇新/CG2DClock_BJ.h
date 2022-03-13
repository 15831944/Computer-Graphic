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
  //���л�
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

  virtual ABox2d& BoundingABox();  // AABB��Χ�У�����������
  virtual void ComputeBounds();    //�����Χ��
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
  virtual void Mirror(Vec2d& v1, Vec2d& v2);
  virtual void ShearXAxis(double shx);               //��X�����
  virtual void ShearYAxis(double shy);               //��Y�����
  virtual void ShearXYAxis(double shx, double shy);  //��X��Y�����
  virtual void Transform(const Mat3d& mat);  //���α任����˸�������

  virtual bool Picked(const Vec2d& p, double radius);  //�Ƿ�ʰȡ��

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