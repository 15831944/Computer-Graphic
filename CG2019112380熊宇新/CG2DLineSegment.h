#ifndef _CG2DLINESEGMENT_H_INCLUDED
#define _CG2DLINESEGMENT_H_INCLUDED
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DLineSegment : public CG2DRenderable {
  DECLARE_SERIAL(CG2DLineSegment)
 public:
  CG2DLineSegment();
  CG2DLineSegment(const Vec2d& s, const Vec2d& e);
  virtual ~CG2DLineSegment();
  //���л�
  virtual void Serialize(CArchive& ar);
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
  virtual void ShearXAxis(double shx);               //��X�����
  virtual void ShearYAxis(double shy);               //��Y�����
  virtual void ShearXYAxis(double shx, double shy);  //��X��Y�����
  virtual void Transform(const Mat3d& mat);  //���α任����˸�������

  virtual bool Clip(double xl,
                    double yb,
                    double xr,
                    double yt,
                    CGRenderContext* pRC);  //���βü�����
 public:
  virtual void Render(CGRenderContext* pRC);
  virtual void ComputeBounds();  //�����Χ��

 protected:
  Vec2d mStart, mEnd;
};
#endif  //_CG2DLINESEGMENT_H_INCLUDED