#include "pch.h"
#include "Create2DCircle3PArc.h"
#include <cmath>
#include "CG2DCircleArc.h"
#include "CGDI2DView.h"

Create2DCircle3PArc::Create2DCircle3PArc(CGView* pview /* = nullptr*/)
    : UIEventListener(pview),
      mCenter(0, 0),
      Upperleft(0, 0),
      Lowerright(0, 0),
      mStart(0, 0),
      mEnd(0, 0) {
  m_nStep = 0;
  Radius = 0;
}
Create2DCircle3PArc::~Create2DCircle3PArc() {}
int Create2DCircle3PArc::GetType()  //��������
{
  return cmd2dCircle3PArc;
}
int Create2DCircle3PArc::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼Բ��
  {
    mStart = mEnd = mCenter = Upperleft = Lowerright = pos;
    mView->Prompt(_T("������Բ����һ���˵�"));
  } else if (m_nStep == 2) {
    mStart = mEnd = pos;
    Radius = sqrt((mStart.x() - mCenter.x()) * (mStart.x() - mCenter.x()) +
                  (mStart.y() - mCenter.y()) * (mStart.y() - mCenter.y()));
    Upperleft.x() = mCenter.x() - (int)(Radius + 0.5);
    Upperleft.y() = mCenter.y() - (int)(Radius + 0.5);
    Lowerright.x() = mCenter.x() + (int)(Radius + 0.5);
    Lowerright.y() = mCenter.y() + (int)(Radius + 0.5);
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mStart.x(), mStart.y());
    dc.SelectObject(pOldPen);
    mView->Prompt(_T("������Բ������һ���˵�"));
  } else if (m_nStep == 3) {
    //���������Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mStart.x(), mStart.y());
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    dc.SetArcDirection(AD_COUNTERCLOCKWISE);
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.SelectObject(pOldPen);
    //��ȡԲ�Ķ�Ӧ�ĳ�������
    Vec2d Center = mView->ViewPortToWorld(mCenter);
    Vec2d Start = mView->ViewPortToWorld(mStart);
    Vec2d End = mView->ViewPortToWorld(mEnd);
    //����Բ������ӵ�����
    CG2DCircleArc* pCircle = new CG2DCircleArc(Center, Start, End, false);
    pCircle->setPenColor(mView->PenColor());  //��̬
    pCircle->setPenWidth(mView->PenWidth());
    pCircle->setPenStyle(mView->PenStyle());
    mView->addRenderable(pCircle);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ����Բ��
    mView->Prompt(_T("������Բ��"));
  } else {
  }
  return 0;
}
int Create2DCircle3PArc::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("������Բ��"));
  } else if (m_nStep == 1) {
    Pos2i prestart;
    prestart = mStart;
    //�����ϴε���Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(prestart.x(), prestart.y());
    //�����µ���Ƥ��
    mStart = pos;
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mStart.x(), mStart.y());
    dc.SelectObject(pOldPen);
  } else if (m_nStep == 2) {
    //�����ϴε���Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    //�����µ���Ƥ��
    mEnd = pos;
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mEnd.x(), mEnd.y());
  } else {
  }
  return 0;
}
int Create2DCircle3PArc::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1) {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mStart.x(), mStart.y());
    mView->Invalidate();
    mView->UpdateWindow();
    dc.SelectObject(pOldPen);
  }
  if (m_nStep == 2)  //����Ѿ�������������ˣ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.SetArcDirection(AD_CLOCKWISE);
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.MoveTo(mCenter.x(), mCenter.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    mView->Invalidate();
    mView->UpdateWindow();
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}