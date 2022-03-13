
#include "pch.h"
#include "CGDI2DView.h"
#include "Transform2DClip.h"
Transform2DClip::Transform2DClip(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0) {
  m_nStep = 0;
}
Transform2DClip::~Transform2DClip() {}
int Transform2DClip::GetType()  //命令类型
{
  return cmd2dClip;
}
int Transform2DClip::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录种子点
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("请输入终点"));
  } else if (m_nStep == 2) {
    //擦除最后的
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

    //绘制新的
    mEnd = pos;

    //获取对应的坐标
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
    //添加到场景
    mView->Clip(xl, yb, xr, yt);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //设为0可重写开始绘制线段
    mView->Prompt(_T("获取初始位置"));
  }
  return 0;
}

int Transform2DClip::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入起点"));
  } else if (m_nStep == 1) {
    Pos2i prePos, curPos;
    prePos = mEnd;
    curPos = pos;
    //擦除上次的
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

    //绘制新的
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mStart.x(), curPos.y()));
    dc.MoveTo(CPoint(mStart.x(), curPos.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), mStart.y()));
    dc.MoveTo(CPoint(curPos.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curPos;  //记录最新位置
  } else {
  }
  return 0;
}
int Transform2DClip::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
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
  mView->Prompt(_T("就绪"));
  return 0;
}