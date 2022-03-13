
#include "CG2DRenderable.h"
#include "Vector2.h"
class CG2DRay : public CG2DRenderable {
  DECLARE_SERIAL(CG2DRay)
 public:
  CG2DRay();
  CG2DRay(const Vec2d& s, const Vec2d& e);
  virtual ~CG2DRay();

  //序列化
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
  virtual void ShearXAxis(double shx);               //沿X轴错切
  virtual void ShearYAxis(double shy);               //沿Y轴错切
  virtual void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切
  virtual void Transform(const Mat3d& mat);  //几何变换（左乘给定矩阵）
 protected:
  Vec2d mStart, mEnd;
};