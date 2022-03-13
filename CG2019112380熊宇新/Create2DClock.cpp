#include "pch.h"
#include "Create2DClock.h"
#include <algorithm>
#include "CG2DClock_BJ.h"
#include "CGDI2DView.h"

Create2DClock::Create2DClock(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
}
Create2DClock::~Create2DClock() {}
int Create2DClock::GetType()  //��������
{
  return cmd2dClock;
}
int Create2DClock::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼���
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("��������ӵ��յ�"));
  } else if (m_nStep == 2) {
    //���������Ƥ��
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 2, mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    if (mStart.x() <= mEnd.x())
    {
      dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                 mEnd.y() - 10);
      dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                   mEnd.y() + abs(mStart.y() - mEnd.y()));
      //���Ӱ�
      dc.MoveTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()), mEnd.y());
      dc.LineTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()));
      dc.Ellipse(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                     0.1 * abs(mStart.x() - mEnd.x()),
                 mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                 mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                     0.1 * abs(mStart.x() - mEnd.x()),
                 mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                     0.2 * abs(mStart.y() - mEnd.y()));
    } 
    else {
      dc.Ellipse(mStart.x() - 10, mStart.y() - 10, mEnd.x() + 10,
                 mEnd.y() + 10);
      dc.Rectangle(mEnd.x() + 10, mStart.y(), mStart.x() - 10,
                   mEnd.y() + abs(mStart.y() - mEnd.y()));

      //���Ӱ�
      dc.MoveTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()), mStart.y());
      dc.LineTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()));
      dc.Ellipse(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                     0.1 * abs(mStart.x() - mEnd.x()),
                 mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                 mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                     0.1 * abs(mStart.x() - mEnd.x()),
                 mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                     0.2 * abs(mStart.y() - mEnd.y()));
      }
    //��ȡ��㡢�յ��Ӧ�ĳ�������
    Vec2d start, end;
    if (mStart.x() <= mEnd.x()) {
      start = mView->ViewPortToWorld(mStart);
      end = mView->ViewPortToWorld(mEnd);
    } else {
      start = mView->ViewPortToWorld(mEnd);
      end = mView->ViewPortToWorld(mStart);
    }
    Vec2i mDis10;
    if (mStart.x() <= mEnd.x()) {
      mDis10.x() = mStart.x() + 10;
      mDis10.y() = mStart.y();
    } else {
      mDis10.x() = mEnd.x() + 10;
      mDis10.y() = mEnd.y();
    }
    Vec2d Dis10 = mView->ViewPortToWorld(mDis10);
    //����ʱ�Ӳ���ӵ�����
    CG2DClock_BJ* pClock = new CG2DClock_BJ(start, end, Dis10);
    pClock->setPenColor(mView->PenColor());  //��̬
    pClock->setPenWidth(mView->PenWidth());
    pClock->setPenStyle(mView->PenStyle());
    pClock->setTimeChose(mView->TimeChose());
    mView->addRenderable(pClock);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ�����߶�
    mView->Prompt(_T("��������ӵ����"));
  } else {
  }
  return 0;
}
int Create2DClock::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("��������ӵ����"));
  } else if (m_nStep == 1) {
    //�����ϴε���Ƥ��
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 2, mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
    if (abs(mStart.x() - mEnd.x()) > 20)
      if (mStart.x() <= mEnd.x()) {
        dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                   mEnd.y() - 10);
        //���
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //���Ӱ�
        dc.MoveTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()), mEnd.y());
        dc.LineTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()));
        dc.Ellipse(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                   mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                       0.2 * abs(mStart.y() - mEnd.y()));
      } else {
        dc.Ellipse(mStart.x() - 10, mStart.y() - 10, mEnd.x() + 10,
                   mEnd.y() + 10);
        dc.Rectangle(mEnd.x() + 10, mStart.y(), mStart.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));

        //���Ӱ�
        dc.MoveTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()), mStart.y());
        dc.LineTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()));
        dc.Ellipse(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                   mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                       0.2 * abs(mStart.y() - mEnd.y()));
      }
    //�����µ���Ƥ��
    mEnd.x() = pos.x();
    mEnd.y() = mStart.y() + mEnd.x() - mStart.x();
    dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
    if (abs(mStart.x() - mEnd.x()) > 20)
      if (mStart.x() <= mEnd.x()) {
        dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                   mEnd.y() - 10);
        //���
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //���Ӱ�
        dc.MoveTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()), mEnd.y());
        dc.LineTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()));
        dc.Ellipse(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                   mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                       0.2 * abs(mStart.y() - mEnd.y()));
      } else {
        dc.Ellipse(mStart.x() - 10, mStart.y() - 10, mEnd.x() + 10,
                   mEnd.y() + 10);
        dc.Rectangle(mEnd.x() + 10, mStart.y(), mStart.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //���Ӱ�
        dc.MoveTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()), mStart.y());
        dc.LineTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()));
        dc.Ellipse(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()),
                   mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.y() - mEnd.y()) +
                       0.2 * abs(mStart.y() - mEnd.y()));
      }
    dc.SelectObject(pOldPen);
  } else {
  }
  return 0;
}
int Create2DClock::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 2, mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
    if (abs(mStart.x() - mEnd.x()) > 20)
      if (mStart.x() <= mEnd.x()) {
        dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                   mEnd.y() - 10);
        //���
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //���Ӱ�
        dc.MoveTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()), mEnd.y());
        dc.LineTo(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mEnd.y() + 0.7 * abs(mStart.x() - mEnd.x()));
        dc.Ellipse(mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.x() - mEnd.x()),
                   mStart.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mEnd.y() + 0.7 * abs(mStart.x() - mEnd.x()) +
                       0.2 * abs(mStart.x() - mEnd.x()));
      } else {
        dc.Ellipse(mStart.x() - 10, mStart.y() - 10, mEnd.x() + 10,
                   mEnd.y() + 10);
        dc.Rectangle(mEnd.x() + 10, mStart.y(), mStart.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //���Ӱ�
        dc.MoveTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()), mStart.y());
        dc.LineTo(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()),
                  mStart.y() + 0.7 * abs(mStart.x() - mEnd.x()));
        dc.Ellipse(mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) -
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.x() - mEnd.x()),
                   mEnd.x() + 0.5 * abs(mStart.x() - mEnd.x()) +
                       0.1 * abs(mStart.x() - mEnd.x()),
                   mStart.y() + 0.7 * abs(mStart.x() - mEnd.x()) +
                       0.2 * abs(mStart.x() - mEnd.x()));
      }
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}