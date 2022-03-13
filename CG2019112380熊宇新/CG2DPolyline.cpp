#include "pch.h"
#include "CG2DPolyline.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"


IMPLEMENT_SERIAL(CG2DPolyline, CG2DRenderable, 1)
CG2DPolyline::CG2DPolyline() : CG2DRenderable(CString("CG2DPolyline")) {
  m_PolyCount = 0;
  for (int i = 0; i < 255; ++i) {
    ArrayPoint[i].x() = 0;
    ArrayPoint[i].y() = 0;
  }
}
CG2DPolyline::CG2DPolyline(Vec2d* ArrayPoint, int m_PolyCount)
    : CG2DRenderable(CString("CG2DPolyline")) {
  this->m_PolyCount = m_PolyCount;
  for (int i = 0; i < this->m_PolyCount; ++i) {
    this->ArrayPoint[i].x() = ArrayPoint[i].x();
    this->ArrayPoint[i].y() = ArrayPoint[i].y();
  }
  m_Name.Format(_T("����-%ld"), sID);
}
CG2DPolyline::~CG2DPolyline() {}
//���л�
void CG2DPolyline::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    for (int i = 0; i < m_PolyCount; ++i)
      ar << ArrayPoint[i].x() << ArrayPoint[i].y();
  } else {
    for (int i = 0; i < m_PolyCount; ++i)
      ar >> ArrayPoint[i].x() >> ArrayPoint[i].y();
  }
}
void CG2DPolyline::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //������������Ƿ������
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;

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
  int Choice = pRC->getView()->LineAlgorithm();
  if (status() == CGRenderable::statusSelected)  //������ѡ��״̬
  {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), RGB(192, 192, 0));  // penColor()
    CPen* pOldPen = dc.SelectObject(&pen);
    int oldMode = dc.SetROP2(R2_XORPEN);
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    dc.SetROP2(oldMode);
  } else {
    dc.Polyline(m_ArrayPoint, m_PolyCount);
  }
  dc.SelectObject(pOldPen);
}

void CG2DPolyline::ComputeBounds()  //�����Χ��
{
  mABox.setNull();  //�����
  for (int i = 0; i < m_PolyCount; ++i)
    mABox.addPoint(ArrayPoint[i]);
  setBoundsDirty(false);
}
//ͼ�ζ���ļ��α任
void CG2DPolyline::Translate(double tx, double ty)  //ƽ��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() += tx;
    ArrayPoint[i].y() += ty;
  }
  setBoundsDirty(true);
}
void CG2DPolyline::Rotate(double angle,
                          double cx,
                          double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  //ʹ�ñ任����ʵ��
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  for (int i = 0; i < m_PolyCount; ++i) {
    Vec3d Point = Vec3d(ArrayPoint[i]);
    Point = operator*(mat, Point);
    ArrayPoint[i] = Point.xy();
  }
  setBoundsDirty(true);
}
void CG2DPolyline::Scale(double sx, double sy)  //����
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() *= sx;
    ArrayPoint[i].y() *= sy;
  }
  setBoundsDirty(true);
}
void CG2DPolyline::MirrorXAxis()  //����X��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].y() = -ArrayPoint[i].y();
  }
  setBoundsDirty(true);
}
void CG2DPolyline::MirrorYAxis()  //����Y��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() = -ArrayPoint[i].x();
  }
  setBoundsDirty(true);
}
void CG2DPolyline::MirrorYeqPosX()  //����y=x�Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    double t = ArrayPoint[i].x();
    ArrayPoint[i].x() = ArrayPoint[i].y();
    ArrayPoint[i].y() = t;
  }
  setBoundsDirty(true);
}
void CG2DPolyline::MirrorYeNegPX()  //����y=-x�Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    double t = ArrayPoint[i].x();
    ArrayPoint[i].x() = -ArrayPoint[i].y();
    ArrayPoint[i].y() = -t;
  }
  setBoundsDirty(true);
}
void CG2DPolyline::MirrorOrigin()  //����ԭ��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  for (int i = 0; i < m_PolyCount; ++i) {
    ArrayPoint[i].x() = -ArrayPoint[i].x();
    ArrayPoint[i].y() = -ArrayPoint[i].y();
  }
  setBoundsDirty(true);
}
void CG2DPolyline::Transform(const Mat3d& mat)  //���α任����˸�������
{
  for (int i = 0; i < m_PolyCount; ++i) {
    Vec3d point = (Vec3d)ArrayPoint[i];
    point = operator*(mat, point);
    ArrayPoint[i] = point.xy();
  }
  setBoundsDirty(true);
}
