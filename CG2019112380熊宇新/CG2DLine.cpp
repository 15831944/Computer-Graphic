#include "pch.h"
#include "CG2DLine.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"

IMPLEMENT_SERIAL(CG2DLine, CG2DRenderable, 1)
CG2DLine::CG2DLine()
    : CG2DRenderable(CString("CG2DLine")), mStart(0, 0), mEnd(0, 0) {
  m_Name.Format(_T("ֱ��-%ld"), sID);
}
CG2DLine::CG2DLine(const Vec2d& s, const Vec2d& e)
    : CG2DRenderable(CString("CG2DLine")), mStart(s), mEnd(e) {
  m_Name.Format(_T("ֱ��-%ld"), sID);
}
CG2DLine::~CG2DLine() {}
//���л�
void CG2DLine::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
  } else {
    ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
  }
}
void CG2DLine::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  CGView* mView = pRC->getView();
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  //������������Ƿ������
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
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

void CG2DLine::ComputeBounds() {
  mABox.setNull();
  mABox.addPoint(mStart);
  mABox.addPoint(mEnd);
  setBoundsDirty(false);
}
void CG2DLine::Translate(double tx, double ty)  //ƽ��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() += tx;
  mStart.y() += ty;
  mEnd.x() += tx;
  mEnd.y() += ty;
  setBoundsDirty(true);
}
void CG2DLine::Rotate(double angle,
                      double cx,
                      double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  //ʹ�ñ任����ʵ��
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
void CG2DLine::Scale(double sx, double sy)  //����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() *= sx;
  mStart.y() *= sy;
  mEnd.x() *= sx;
  mEnd.y() *= sy;
  setBoundsDirty(true);
}
void CG2DLine::MirrorXAxis()  //����X��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.y() = -mStart.y();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DLine::MirrorYAxis()  //����Y��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = -mStart.x();
  mEnd.x() = -mEnd.x();
  setBoundsDirty(true);
}
void CG2DLine::MirrorYeqPosX()  //����y=x�Գƣ���ά����ά��
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
void CG2DLine::MirrorYeNegPX()  //����y=-x�Գƣ���ά����ά��
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
void CG2DLine::MirrorOrigin()  //����ԭ��Գƣ���ά����ά��
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = -mStart.x();
  mStart.y() = -mStart.y();
  mEnd.x() = -mEnd.x();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}
void CG2DLine::ShearXAxis(double shx)  //��X�����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.x() = mStart.x() + shx * mStart.y();
  mEnd.x() = mEnd.x() + shx * mEnd.y();
  setBoundsDirty(true);
}
void CG2DLine::ShearYAxis(double shy)  //��Y�����
{
  //�򵥱任����ʹ�þ���ֱ������
  mStart.y() = mStart.y() + shy * mStart.x();
  mEnd.y() = mEnd.y() + shy * mEnd.x();
  setBoundsDirty(true);
}
void CG2DLine::ShearXYAxis(double shx, double shy)  //��X��Y�����
{
  //ʹ�ñ任����ʵ��
  Mat3d mat = Mat3d::getShear(shx, shy);
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
void CG2DLine::Transform(const Mat3d& mat)  //���α任����˸�������
{
  mStart = operator*(mat, mStart);
  mEnd = operator*(mat, mEnd);
  setBoundsDirty(true);
}
