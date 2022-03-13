
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DRay : public CG2DRenderable {
  DECLARE_SERIAL(CG2DRay)
 public:
  CG2DRay();
  CG2DRay(const Vec2d& s, const Vec2d& e);
  virtual ~CG2DRay();

  //���л�
  virtual void Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
      ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
    } else {
      ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
    }
  }

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
  virtual void ShearXAxis(double shx);               //��X�����
  virtual void ShearYAxis(double shy);               //��Y�����
  virtual void ShearXYAxis(double shx, double shy);  //��X��Y�����
  virtual void Transform(const Mat3d& mat);  //���α任����˸�������
 protected:
  Vec2d mStart, mEnd;
};