
#include "pch.h"
#include "CGDI2DView.h"
#include "Transform2DClip.h"
Transform2DClip::Transform2DClip(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0) {
  m_nStep = 0;
}
Transform2DClip::~Transform2DClip() {}
int Transform2DClip::GetType()  //��������
{
  return cmd2dClip;
}
int Transform2DClip::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼���ӵ�
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("�������յ�"));
  } else if (m_nStep == 2) {
    //��������
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mStart.x(), mEnd.y()));
    dc.MoveTo(CPoint(mStart.x(), mEnd.y()));
    dc.LineTo (CPoint(mEnd.x(), mEnd.y()));
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mStart.y()));
    dc.MoveTo(CPoint(mEnd.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);

    //�����µ�
    mEnd = pos;

    //��ȡ��Ӧ������
    Vec2d start = mView->ViewPortToWorld(mStart);
    Vec2d end = mView->ViewPortToWorld(mEnd);
    double xl, yb, xr, yt;
    if (start.x() < end.x()) {
      xl = start.x();
      xr = end.x();
    } else {
      xl = end.x();
      xr = start.x();
    }
    if (start.y() < end.y()) {
      yb = start.y();
      yt = end.y();
    } else {
      yb = end.y();
      yt = start.y();
    }
    //��ӵ�����
    mView->Clip(xl, yb, xr, yt);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ�����߶�
    mView->Prompt(_T("��ȡ��ʼλ��"));
  }
  return 0;
}

int Transform2DClip::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("���������"));
  } else if (m_nStep == 1) {
    Pos2i prePos, curPos;
    prePos = mEnd;
    curPos = pos;
    //�����ϴε�
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mStart.x(), prePos.y()));
    dc.MoveTo(CPoint(mStart.x(), prePos.y()));
    dc.LineTo(CPoint(prePos.x(), prePos.y()));
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(prePos.x(), mStart.y()));
    dc.MoveTo(CPoint(prePos.x(), mStart.y()));
    dc.LineTo(CPoint(prePos.x(), prePos.y()));

    //�����µ�
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mStart.x(), curPos.y()));
    dc.MoveTo(CPoint(mStart.x(), curPos.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), mStart.y()));
    dc.MoveTo(CPoint(curPos.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curPos;  //��¼����λ��
  } else {
  }
  return 0;
}
int Transform2DClip::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mStart.x(), mEnd.y()));
    dc.MoveTo(CPoint(mStart.x(), mEnd.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mStart.y()));
    dc.MoveTo(CPoint(mEnd.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}