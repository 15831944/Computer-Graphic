#include "pch.h"
#include "CGDI2DView.h"
#include "CG2DPolygon.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"


IMPLEMENT_SERIAL(CG2DPolygon, CG2DRenderable, 1)
CG2DPolygon::CG2DPolygon() : CG2DRenderable(CString("CG2DPolygon")) {
  m_PolyCount = 0;
  for (int i = 0; i < 255; ++i) {
    ArrayPoint[i].x() = 0;
    ArrayPoint[i].y() = 0;
  }
  m_Name.Format(_T("任意多边形-%ld"), sID);
}
CG2DPolygon::CG2DPolygon(Vec2d* ArrayPoint, int m_PolyCount)
    : CG2DRenderable(CString("CG2DPolygon")) {
  this->m_PolyCount = m_PolyCount;
  for (int i = 0; i < this->m_PolyCount; ++i) {
    this->ArrayPoint[i].x() = ArrayPoint[i].x();
    this->ArrayPoint[i].y() = ArrayPoint[i].y();
  }
  m_Name.Format(_T("任意多边形-%ld"), sID);
}
CG2DPolygon::~CG2DPolygon() {}
//序列化
void CG2DPolygon::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    for (int i = 0; i < m_PolyCount; ++i)
      ar << ArrayPoint[i].x() << ArrayPoint[i].y();
  } else {
    for (int i = 0; i < m_PolyCount; ++i)
      ar >> ArrayPoint[i].x() >> ArrayPoint[i].y();
  }
}
void CG2DPolygon::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  //绘制线段对象
  CPoint m_ArrayPoint[255];
  for (int i = 0; i < m_PolyCount; ++i) {
    m_ArrayPoint[i].x = camera->WorldtoViewPort(ArrayPoint[i]).x();
    m_ArrayPoint[i].y = camera->WorldtoViewPort(ArrayPoint[i]).y();
  }
  Vec2i Array_Point[255];
  for (int i = 0; i < m_PolyCount; ++i) {
    Array_Point[i].x() = m_ArrayPoint[i].x;
    Array_Point[i].y() = m_ArrayPoint[i].y;
  }
  CClientDC dc(pRC->getView());
  CPen pen(penStyle(), penWidth(), penColor());
  CPen* pOldPen = dc.SelectObject(&pen);

  CBrush *pOldBrush, *pBrush = nullptr;
  if (!brushUse()) {
    pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
  } else if (brushIndex() != -1) {
    pBrush = new CBrush(brushIndex(), brushColor());
    pOldBrush = dc.SelectObject(pBrush);
  } else {
    pBrush = new CBrush(brushColor());
    pOldBrush = dc.SelectObject(pBrush);
  }
  if (status() == CGRenderable::statusSelected)  //对象处于选中状态
  {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), RGB(192, 192, 0));  // penColor()
    CPen* pOldPen = dc.SelectObject(&pen);
    int oldMode = dc.SetROP2(R2_XORPEN);
    CBrush *pOldBrush, *pBrush = nullptr;
    if (!brushUse()) {
      pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
    } else if (brushIndex() != -1) {
      pBrush = new CBrush(brushIndex(), brushColor());
      pOldBrush = dc.SelectObject(pBrush);
    } else {
      pBrush = new CBrush(brushColor());
      pOldBrush = dc.SelectObject(pBrush);
    }
      dc.Polygon(m_ArrayPoint, m_PolyCount);
    if (pBrush)
      delete pBrush;
    dc.SelectObject(pOldPen);
    dc.SetROP2(oldMode);
    dc.SelectObject(pOldBrush);
  } else {
          dc.Polygon(m_ArrayPoint, m_PolyCount);
  }
  if (pBrush)
    delete pBrush;
  dc.SelectObject(pOldPen);
  dc.SelectObject(pOldBrush);
}

void CG2DPolygon::ComputeBounds()  //计算包围盒
{
  mABox.setNull();  //先清空
  for (int i = 0; i < m_PolyCount; ++i)
    mABox.addPoint(ArrayPoint[i]);
  setBoundsDirty(false);
}
//图形对象的几何变换
void CG2DPolygon::Translate(double tx, double ty)  //平移
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() += tx;
    ArrayPoint[i].y() += ty;
  }
  setBoundsDirty(true);
}
void CG2DPolygon::Rotate(double angle,
                         double cx,
                         double cy)  //旋转（逆时针为正，度）
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  for (int i = 0; i < m_PolyCount; ++i) {
    Vec3d Point = Vec3d(ArrayPoint[i]);
    Point = operator*(mat, Point);
    ArrayPoint[i] = Point.xy();
  }
  setBoundsDirty(true);
}
void CG2DPolygon::Scale(double sx, double sy)  //缩放
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() *= sx;
    ArrayPoint[i].y() *= sy;
  }
  setBoundsDirty(true);
}
void CG2DPolygon::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].y() = -ArrayPoint[i].y();
  }
  setBoundsDirty(true);
}
void CG2DPolygon::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() = -ArrayPoint[i].x();
  }
  setBoundsDirty(true);
}
void CG2DPolygon::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    double t = ArrayPoint[i].x();
    ArrayPoint[i].x() = ArrayPoint[i].y();
    ArrayPoint[i].y() = t;
  }
  setBoundsDirty(true);
}
void CG2DPolygon::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    double t = ArrayPoint[i].x();
    ArrayPoint[i].x() = -ArrayPoint[i].y();
    ArrayPoint[i].y() = -t;
  }
  setBoundsDirty(true);
}
void CG2DPolygon::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() = -ArrayPoint[i].x();
    ArrayPoint[i].y() = -ArrayPoint[i].y();
  }
  setBoundsDirty(true);
}

void CG2DPolygon::Transform(const Mat3d& mat)  //几何变换（左乘给定矩阵）
{
  for (int i = 0; i < m_PolyCount; ++i) {
    Vec3d point = (Vec3d)ArrayPoint[i];
    point = operator*(mat, point);
    ArrayPoint[i] = point.xy();
  }
  setBoundsDirty(true);
}
