#include "pch.h"
#include "Create2DRay.h"
#include "CG2DRay.h"
#include "CGDI2DView.h"
#include"CG2DLineSegment.h"

Create2DRay::Create2DRay(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
}
Create2DRay::~Create2DRay() {}
int Create2DRay::GetType()  //��������
{
  return cmd2dRay;
}
int Create2DRay::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rect;
  mView->GetClientRect(rect);
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼���
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("�����������յ�"));
  } else if (m_nStep == 2) {
    //���������Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x����仯С����ֱ��
      {
        mEnd.x() = mStart.x();
        mEnd.y() = pos.y();
      } else  // x����仯��ˮƽ��
      {
        mEnd.x() = pos.x();
        mEnd.y() = mStart.y();
      }
    } else {
      if (mStart.x() == pos.x()) {
        if (pos.y() <= mStart.y())
          mEnd.x() = 0;
        else
          mEnd.y() = rect.Height();
      } else {
          //��ȡ����б��
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
          if (pos.x() <= mStart.x())
            mEnd.x() = 0;
          else
            mEnd.x() = rect.Width();
          mEnd.y() = k * mEnd.x() - k * mStart.x() + mStart.y();
      }
    }

    //��ȡ��㡢�յ��Ӧ�ĳ�������
    Vec2d start = mView->ViewPortToWorld(mStart);
    Vec2d end = mView->ViewPortToWorld(mEnd);
    //�����߶β���ӵ�����
    CG2DRay* pLine = new CG2DRay(start, end);    
    pLine->setPenColor(mView->PenColor());  //��̬
    pLine->setPenWidth(mView->PenWidth());
    pLine->setPenStyle(mView->PenStyle());
    mView->addRenderable(pLine);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ�����߶�
    mView->Prompt(_T("�������������"));
  } else {
  }
  return 0;
}
int Create2DRay::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rect;
  mView->GetClientRect(rect);
  if (m_nStep == 0) {
    mView->Prompt(_T("���������ߵ����"));
  } else if (m_nStep == 1) {
    Pos2i prePos, curPos;
    prePos = mEnd;
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x����仯С����ֱ��
      {
        curPos.x() = mStart.x();
        curPos.y() = pos.y();
      } else {
        curPos.x() = pos.x();
        curPos.y() = mStart.y();
      }
    } else {
      if (mStart.x() == pos.x()) {
        if (pos.y() <= mStart.y())
          curPos.y() = 0;
        else
          curPos.y() = rect.Height();
      } else {
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
        if (pos.x() <= mStart.x())
          curPos.x() = 0;
        else
          curPos.x() = rect.Width();
        curPos.y() = k * curPos.x() - k * mStart.x() + mStart.y();
      }
    }
    //�����ϴε���Ƥ��
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(prePos.x(), prePos.y()));
    //�����µ���Ƥ��
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curPos;  //��¼����λ��
  } else {
  }
  return 0;
}
int Create2DRay::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}