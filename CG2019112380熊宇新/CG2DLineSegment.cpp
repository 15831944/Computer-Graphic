#include "pch.h"
#include "CG2DLineSegment.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"


IMPLEMENT_SERIAL(CG2DLineSegment, CG2DRenderable, 1)
CG2DLineSegment::CG2DLineSegment()
    : CG2DRenderable(CString("CG2DLineSegment")), mStart(0, 0), mEnd(0, 0) {

}
CG2DLineSegment::CG2DLineSegment(const Vec2d& s, const Vec2d& e)
    : CG2DRenderable(CString("CG2DLineSegment")), mStart(s), mEnd(e) {
  m_Name.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::~CG2DLineSegment() {
}
//���л�
void CG2DLineSegment::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
  } else {
    ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
  }
}
void CG2DLineSegment::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //������������Ƿ������
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  //�����߶ζ���
  Vec2i v1 = camera->WorldtoViewPort(mStart);
  Vec2i v2 = camera->WorldtoViewPort(mEnd);
  if (status() == CGRenderable::statusSelected)  //������ѡ��״̬
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
    //�����㷨
    int lineAlgrithm = pRC->getView()->LineAlgorithm();
    if (lineAlgrithm == 0) {
      CClientDC dc(pRC->getView());
      CPen pen(penStyle(), penWidth(), penColor());
      CPen* pOldPen = dc.SelectObject(&pen);
      dc.MoveTo(v1.x(), v1.y());
      dc.LineTo(v2.x(), v2.y());
      dc.SelectObject(pOldPen);
    } else if (lineAlgrithm == 1)
      pRC->DDALine(v1, v2, penColor());
    else if (lineAlgrithm == 2)
      pRC->MidPointLine(v1, v2, penColor());
    else
      pRC->BresehamLine(v1, v2, penColor());
  }
}
void CG2DLineSegment::ComputeBounds()  //�����Χ��
{
  mABox.addPoint(mStart);
  mABox.addPoint(mEnd);
  setBoundsDirty(false);
}
//ͼ�ζ���ļ��α任
void CG2DLineSegment::Translate(double tx, double ty)  //ƽ��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() += tx;
  mStart.y() += ty;
  mEnd.x() += tx;
  mEnd.y() += ty;
  setBoundsDirty(true);
}
void CG2DLineSegment::Rotate(double angle, double cx,double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  //ʹ�ñ任����ʵ��
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
void CG2DLineSegment::Scale(double sx, double sy)  //����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() *= sx;
  mStart.y() *= sy;
  mEnd.x() *= sx;
  mEnd.y() *= sy;
  setBoundsDirty(true);
}
void CG2DLineSegment::MirrorXAxis()  //����X��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.y() = -mStart.y();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYAxis()  //����Y��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = -mStart.x();
  mEnd.x() = -mEnd.x();
  setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYeqPosX()  //����y=x�Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  double t = mStart.x();
  mStart.x() = mStart.y();
  mStart.y() = t;
  t = mEnd.x();
  mEnd.x() = mEnd.y();
  mEnd.y() = t;
  setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYeNegPX()  //����y=-x�Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  double t = mStart.x();
  mStart.x() = -mStart.y();
  mStart.y() = -t;
  t = mEnd.x();
  mEnd.x() = -mEnd.y();
  mEnd.y() = -t;
  setBoundsDirty(true);
}
void CG2DLineSegment::MirrorOrigin()  //����ԭ��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = -mStart.x();
  mStart.y() = -mStart.y();
  mEnd.x() = -mEnd.x();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DLineSegment::ShearXAxis(double shx)  //��X�����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = mStart.x() + shx * mStart.y();
  mEnd.x() = mEnd.x() + shx * mEnd.y();
  setBoundsDirty(true);
}
void CG2DLineSegment::ShearYAxis(double shy)  //��Y�����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.y() = mStart.y() + shy * mStart.x();
  mEnd.y() = mEnd.y() + shy * mEnd.x();
  setBoundsDirty(true);
}
void CG2DLineSegment::ShearXYAxis(double shx, double shy)  //��X��Y�����
{
  //ʹ�ñ任����ʵ��
  Mat3d mat = Mat3d::getShear(shx, shy);
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
void CG2DLineSegment::Transform(const Mat3d& mat)  //���α任����˸�������
{
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
//��ά�ü�����
bool CG2DLineSegment::Clip(double xl,
                           double yb,
                           double xr,
                           double yt,
                           CGRenderContext* pRC) {
  if (pRC == nullptr)
    return false;
  Vec2d s, e;
  bool result =
      pRC->CohenSutherlandLineClip(xl, yb, xr, yt, mStart, mEnd, s, e);
  if (result) {
    mStart = s;
    mEnd = e;
  }
  return result;
}
