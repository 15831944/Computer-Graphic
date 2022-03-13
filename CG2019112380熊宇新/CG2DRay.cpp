#include "pch.h"
#include "CG2DRay.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"


IMPLEMENT_SERIAL(CG2DRay, CG2DRenderable, 1)
CG2DRay ::CG2DRay()
    : CG2DRenderable(CString("CG2DRay ")), mStart(0, 0), mEnd(0, 0) {
  m_Name.Format(_T("射线-%ld"), sID);
}
CG2DRay ::CG2DRay(const Vec2d& s, const Vec2d& e)
    : CG2DRenderable(CString("CG2DRay ")), mStart(s), mEnd(e) {
  m_Name.Format(_T("射线-%ld"), sID);
}
CG2DRay ::~CG2DRay() {}
//序列化
void CG2DRay::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  //绘制线段对象
  Vec2i v1 = camera->WorldtoViewPort(mStart);
  Vec2i v2 = camera->WorldtoViewPort(mEnd);
  if (status() == CGRenderable::statusSelected)  //对象处于选中状态
  {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), RGB(192, 192, 0));  // penColor()
    CPen* pOldPen = dc.SelectObject(&pen);
    int oldMode = dc.SetROP2(R2_XORPEN);
    dc.MoveTo(v1.x(), v1.y());
    dc.LineTo(v2.x(), v2.y());
    dc.SelectObject(pOldPen);
    dc.SetROP2(oldMode);
  } else {
    //测试算法
    int lineAlgrithm = pRC->getView()->LineAlgorithm();
    switch (lineAlgrithm) {
      case 1:
        pRC->MidPointLine(v1, v2, penColor());
        break;
      case 2:
        pRC->BresehamLine(v1, v2, penColor());
        break;
      case 3:
        pRC->DDALine(v1, v2, penColor());
        break;
      case 0:
      default:
        CClientDC dc(pRC->getView());
        CPen pen(penStyle(), penWidth(), penColor());
        CPen* pOldPen = dc.SelectObject(&pen);
        dc.MoveTo(v1.x(), v1.y());
        dc.LineTo(v2.x(), v2.y());
        dc.SelectObject(pOldPen);
        break;
    }
  }
}
void CG2DRay::ComputeBounds() {
  mABox.setNull();
  mABox.addPoint(mStart);
  mABox.addPoint(mEnd);
  setBoundsDirty(false);
}
void CG2DRay::Translate(double tx, double ty)  //平移
{
  //简单变换，不使用矩阵直接运算
  mStart.x() += tx;
  mStart.y() += ty;
  mEnd.x() += tx;
  mEnd.y() += ty;
  setBoundsDirty(true);
}
void CG2DRay::Rotate(double angle,
                     double cx,
                     double cy)  //旋转（逆时针为正，度）
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  mStart = operator*(mStart, mat);
  mEnd = operator*(mEnd, mat);
  setBoundsDirty(true);
}
void CG2DRay::Scale(double sx, double sy)  //缩放
{
  //简单变换，不使用矩阵直接运算
  mStart.x() *= sx;
  mStart.y() *= sy;
  mEnd.x() *= sx;
  mEnd.y() *= sy;
  setBoundsDirty(true);
}
void CG2DRay::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mStart.y() = -mStart.y();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DRay::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mStart.x() = -mStart.x();
  mEnd.x() = -mEnd.x();
  setBoundsDirty(true);
}
void CG2DRay::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mStart.x();
  mStart.x() = mStart.y();
  mStart.y() = t;
  t = mEnd.x();
  mEnd.x() = mEnd.y();
  mEnd.y() = t;
  setBoundsDirty(true);
}
void CG2DRay::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mStart.x();
  mStart.x() = -mStart.y();
  mStart.y() = -t;
  t = mEnd.x();
  mEnd.x() = -mEnd.y();
  mEnd.y() = -t;
  setBoundsDirty(true);
}
void CG2DRay::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mStart.x() = -mStart.x();
  mStart.y() = -mStart.y();
  mEnd.x() = -mEnd.x();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DRay::ShearXAxis(double shx)  //沿X轴错切
{
  //简单变换，不使用矩阵直接运算
  mStart.x() = mStart.x() + shx * mStart.y();
  mEnd.x() = mEnd.x() + shx * mEnd.y();
  setBoundsDirty(true);
}
void CG2DRay::ShearYAxis(double shy)  //沿Y轴错切
{
  //简单变换，不使用矩阵直接运算
  mStart.y() = mStart.y() + shy * mStart.x();
  mEnd.y() = mEnd.y() + shy * mEnd.x();
  setBoundsDirty(true);
}
void CG2DRay::ShearXYAxis(double shx, double shy)  //沿X、Y轴错切
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getShear(shx, shy);
  mStart = operator*(mStart, mat);
  mEnd = operator*(mEnd, mat);
  setBoundsDirty(true);
}
void CG2DRay::Transform(const Mat3d& mat)  //几何变换（左乘给定矩阵）
{
  mStart = operator*(mStart, mat);
  mEnd = operator*(mEnd, mat);
  setBoundsDirty(true);
}