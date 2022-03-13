#include "pch.h"
#include "CG2DCircle.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"
#include "Vector2.h"

IMPLEMENT_SERIAL(CG2DCircle, CG2DRenderable, 1)
CG2DCircle::CG2DCircle()
    : CG2DRenderable(CString("CG2DCircle")), mCenter(0, 0) {
  mRadius = 0;
  m_Name.Format(_T("圆-%ld"), sID);
  mXRadius = 0;
  mYRadius = 0;
}
CG2DCircle::CG2DCircle(const Vec2d& Center, double r)
    : CG2DRenderable(CString("CG2DCircle")), mCenter(Center) {
  mRadius = r;
  mXRadius = r;
  mYRadius = r;
  m_Name.Format(_T("圆-%ld"), sID);
}
CG2DCircle::~CG2DCircle() {}
//序列化
void CG2DCircle::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mCenter.x() << mCenter.y() << mRadius;
  } else {
    ar >> mCenter.x() >> mCenter.y() >> mRadius;
  }
}
CBrush* mSetBrush(CClientDC* pDC, CG2DRenderable* pR, CBrush* pBrush) {
  if (!pR->brushUse())
    return (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
  else if (pR->brushIndex() != -1) {
    pBrush = new CBrush();
    pBrush->CreateHatchBrush(pR->brushIndex(), pR->brushColor());
    return (CBrush*)pDC->SelectObject(pBrush);
  } else {
    pBrush = new CBrush();
    pBrush->CreateSolidBrush(pR->brushColor());
    return (CBrush*)pDC->SelectObject(pBrush);
  }
}
void CG2DCircle::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  //绘制圆对象(如果视口与窗口的长、宽比例不- -致，则应按椭圆绘制)
  Vec2i center = camera->WorldtoViewPort(mCenter);
  double R = camera->LengthWorldtoViewPort(mRadius) + 0.5;
  if (status() == CGRenderable::statusSelected)  //对象处于选中状态
  {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), RGB(192, 192, 0));  // penColor()
    CBrush *brush = nullptr, *poldbrush;
    if (brushUse())
      poldbrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
    else if (brushIndex() != -1) {
      brush = new CBrush();
      brush->CreateHatchBrush(brushIndex(), RGB(240, 240, 0));
      poldbrush = (CBrush*)dc.SelectObject(brush);
    } else {
      brush = new CBrush();
      brush->CreateSolidBrush(RGB(255, 140, 0));
      poldbrush = (CBrush*)dc.SelectObject(brush);
    }
    CPen* poldPen = dc.SelectObject(&pen);
    dc.Ellipse(center.x() - R, center.y() - R, center.x() + R, center.y() + R);
    dc.SelectObject(poldPen);
    dc.SelectObject(poldbrush);
    if (brush)
      delete brush;
    pen.DeleteObject();
  }
  else {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), penColor());
    CPen* poldPen = dc.SelectObject(&pen);
    CBrush *poldBrush, *pBrush = nullptr;
    poldBrush = mSetBrush(&dc, this, pBrush);
    dc.Ellipse(center.x() - R, center.y() - R, center.x() + R, center.y() + R);
    dc.SelectObject(poldPen);
    dc.SelectObject(poldBrush);
    if (pBrush)
      delete pBrush;
    pen.DeleteObject();
  }
}




void CG2DCircle::ComputeBounds() {
  mABox.setNull();
  mABox.addPoint(mCenter, mRadius);
  setBoundsDirty(false);
}
void CG2DCircle::Translate(double tx, double ty)  //平移
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() += tx;
  mCenter.y() += ty;
  setBoundsDirty(true);
}
 void CG2DCircle::Rotate(double angle,double cx,double cy)
 //旋转（逆时针为正，度）
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  Vec3d Center = Vec3d(mCenter);
  Center = operator*(mat, Center);
  mCenter = Center.xy();
  setBoundsDirty(true);
}
void CG2DCircle::Scale(double sx, double sy)  //缩放
{
  //简单变换，不使用矩阵直接运算
  mXRadius *= sx;
  mYRadius *= sy;
  mCenter.x() *= sx;
  mCenter.y() *= sy;
  setBoundsDirty(true);
}
void CG2DCircle::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.y() = -mCenter.y();
  setBoundsDirty(true);
}
void CG2DCircle::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() = -mCenter.x();
  setBoundsDirty(true);
}
void CG2DCircle::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mCenter.x();
  mCenter.x() = -mCenter.y();
  mCenter.y() = -t;
  setBoundsDirty(true);
}
void CG2DCircle::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mCenter.x();
  mCenter.x() = -mCenter.y();
  mCenter.y() = -t;
  setBoundsDirty(true);
}
void CG2DCircle::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() = -mCenter.x();
  mCenter.y() = -mCenter.y();
  setBoundsDirty(true);
}