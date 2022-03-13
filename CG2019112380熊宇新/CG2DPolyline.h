#ifndef _CG2DPOLYLINE_H_INCLUDED
#define _CG2DPOLYLINE_H_INCLUDED
#pragma once
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DPolyline : public CG2DRenderable {
  DECLARE_SERIAL(CG2DPolyline)
 public:
  CG2DPolyline();
  CG2DPolyline(Vec2d* ArrayPoint, int m_PolyCount);
  virtual ~CG2DPolyline();
  //���л�
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  virtual void ComputeBounds();  //�����Χ��

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
  Vec2d ArrayPoint[255];
  int m_PolyCount;
};

#endif  //_CG2DPOLYLINE_H_INCLUDED