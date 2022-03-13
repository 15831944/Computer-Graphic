#include "pch.h"
#include "Create2DLineSegment.h"
#include "CG2DLineSegment.h"
#include "CGDI2DView.h"

Create2DLineSegment::Create2DLineSegment(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
}
Create2DLineSegment::~Create2DLineSegment() {}
int Create2DLineSegment::GetType()  //命令类型
{
  return cmd2dLineSegment;
}
int Create2DLineSegment::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录起点
  {
    mStart = mEnd = pos;
    mView->Prompt(_T("请输入直线段的终点"));
  } 
  else if (m_nStep == 2) {
    //擦除最后橡皮线
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x方向变化小，垂直线
      {
        mEnd.x() = mStart.x();
        mEnd.y() = pos.y();
      } else  // x方向变化大，水平线
      {
        mEnd.x() = pos.x();
        mEnd.y() = mStart.y();
      }
    } 
    else {
      mEnd = pos;
    }
    //获取起点、终点对应的场景坐标
    Vec2d start = mView->ViewPortToWorld(mStart);
    Vec2d end = mView->ViewPortToWorld(mEnd);
    //创建线段并添加到场景
    CG2DLineSegment* pLine = new CG2DLineSegment(start, end);
    pLine->setPenColor(mView->PenColor());  //多态
    pLine->setPenWidth(mView->PenWidth());
    pLine->setPenStyle(mView->PenStyle());
    mView->addRenderable(pLine);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //设为0可重写开始绘制线段
    mView->Prompt(_T("请输入直线段的起点"));
  } 
  else {

  }
  return 0;
}
int Create2DLineSegment::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入直线段的起点"));
  } else if (m_nStep == 1) {
    Pos2i prePos, curPos;
    prePos = mEnd;
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x方向变化小，垂直线
      {
        curPos.x() = mStart.x();
        curPos.y() = pos.y();
      } else {
        curPos.x() = pos.x();
        curPos.y() = mStart.y();
      }
    } else {
      curPos = pos;
    }
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOT);
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(prePos.x(), prePos.y()));
    //绘制新的橡皮线
    dc.MoveTo(CPoint(mStart.x(), mStart.y()));
    dc.LineTo(CPoint(curPos.x(), curPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curPos;  //记录最新位置
  } else {
  }
  return 0;
}
int Create2DLineSegment::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
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
  mView->Prompt(_T("就绪"));
  return 0;
}