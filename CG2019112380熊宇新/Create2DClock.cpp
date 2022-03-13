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
int Create2DClock::GetType()  //命令类型
{
  return cmd2dClock;
}
int Create2DClock::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录起点
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("请输入摆钟的终点"));
  } else if (m_nStep == 2) {
    //擦除最后橡皮线
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
      //画钟摆
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

      //画钟摆
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
    //获取起点、终点对应的场景坐标
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
    //创建时钟并添加到场景
    CG2DClock_BJ* pClock = new CG2DClock_BJ(start, end, Dis10);
    pClock->setPenColor(mView->PenColor());  //多态
    pClock->setPenWidth(mView->PenWidth());
    pClock->setPenStyle(mView->PenStyle());
    pClock->setTimeChose(mView->TimeChose());
    mView->addRenderable(pClock);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //设为0可重写开始绘制线段
    mView->Prompt(_T("请输入摆钟的起点"));
  } else {
  }
  return 0;
}
int Create2DClock::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入摆钟的起点"));
  } else if (m_nStep == 1) {
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 2, mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
    if (abs(mStart.x() - mEnd.x()) > 20)
      if (mStart.x() <= mEnd.x()) {
        dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                   mEnd.y() - 10);
        //外框
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //画钟摆
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

        //画钟摆
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
    //绘制新的橡皮线
    mEnd.x() = pos.x();
    mEnd.y() = mStart.y() + mEnd.x() - mStart.x();
    dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
    if (abs(mStart.x() - mEnd.x()) > 20)
      if (mStart.x() <= mEnd.x()) {
        dc.Ellipse(mStart.x() + 10, mStart.y() + 10, mEnd.x() - 10,
                   mEnd.y() - 10);
        //外框
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //画钟摆
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
        //画钟摆
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
  if (m_nStep == 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
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
        //外框
        dc.Rectangle(mStart.x() + 10, mEnd.y(), mEnd.x() - 10,
                     mEnd.y() + abs(mStart.y() - mEnd.y()));
        //画钟摆
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
        //画钟摆
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
  mView->Prompt(_T("就绪"));
  return 0;
}