#include "pch.h"
#include "Create2DLine.h"
#include "CG2DLine.h"
#include "CGDI2DView.h"

Create2DLine::Create2DLine(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
}
Create2DLine::~Create2DLine() {}
int Create2DLine::GetType()  //命令类型
{
  return cmd2dLine;
}
int Create2DLine::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录起点
  {
    mStart = mEnd = mTemp = pos;
    mView->Prompt(_T("请输入直线的终点"));
  } else if (m_nStep == 2) {
    //擦除最后橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(mTemp.x(), mTemp.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x方向变化小，垂直线
      {
        mTemp.x() = mStart.x();
        mEnd.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          mTemp.y() = rectDlg.Height();
          mEnd.y() = 0;
        } else {
          mTemp.y() = 0;
          mEnd.y() = rectDlg.Height();
        }
      } else  // x方向变化大，水平线
      {
        mTemp.y() = mStart.y();
        mEnd.y() = mStart.y();
        if (pos.x() <= mStart.x()) {
          mTemp.x() = rectDlg.Width();
          mEnd.x() = 0;
        } else {
          mTemp.x() = 0;
          mEnd.x() = rectDlg.Width();
        }
      }
    } else {
      if (mStart.x() == pos.x()) {
        mTemp.x() = mStart.x();
        mEnd.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          mTemp.y() = rectDlg.Height();
          mEnd.y() = 0;
        } else {
          mTemp.y() = 0;
          mEnd.y() = rectDlg.Height();
        }
      } else {
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
        if (pos.x() <= mStart.x()) {
          mEnd.x() = 0;
          mTemp.x() = rectDlg.Width();

        } else {
          mEnd.x() = rectDlg.Width();
          mTemp.x() = 0;
        }
        mTemp.y() = k * mTemp.x() - k * mStart.x() + mStart.y();
        mEnd.y() = k * mEnd.x() - k * mStart.x() + mStart.y();
      }
    }
    //获取起点、终点对应的场景坐标
    Vec2d start = mView->ViewPortToWorld(mTemp);
    Vec2d end = mView->ViewPortToWorld(mEnd);
    //创建线段并添加到场景
    CG2DLine* pLine = new CG2DLine(start, end);
    pLine->setPenColor(mView->PenColor());  //多态
    pLine->setPenWidth(mView->PenWidth());
    pLine->setPenStyle(mView->PenStyle());
    mView->addRenderable(pLine);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //设为0可重写开始绘制线段
    mView->Prompt(_T("请输入直线的起点"));
  } else {
  }
  return 0;
}
int Create2DLine::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入直线的起点"));
  } else if (m_nStep == 1) {
    Pos2i preEndPos, curEndPos, preTempPos, curTempPos;
    preTempPos = mTemp;
    preEndPos = mEnd;
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x方向变化小，垂直线
      {
        curTempPos.x() = mStart.x();
        curEndPos.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          curTempPos.y() = rectDlg.Height();
          curEndPos.y() = 0;
        } else {
          curTempPos.y() = 0;
          curEndPos.y() = rectDlg.Height();
        }
      } else  //水平线
      {
        curTempPos.y() = mStart.y();
        curEndPos.y() = mStart.y();
        if (pos.x() <= mStart.x()) {
          curTempPos.x() = rectDlg.Width();
          curEndPos.x() = 0;
        } else {
          curTempPos.x() = 0;
          curEndPos.x() = rectDlg.Width();
        }
      }
    } else {
      if (mStart.x() == pos.x()) {
        curTempPos.x() = mStart.x();
        curEndPos.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          curTempPos.y() = rectDlg.Height();
          curEndPos.y() = 0;
        } else {
          curTempPos.y() = 0;
          curEndPos.y() = rectDlg.Height();
        }
      } else {
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
        if (pos.x() <= mStart.x()) {
          curEndPos.x() = 0;
          curTempPos.x() = rectDlg.Width();

        } else {
          curEndPos.x() = rectDlg.Width();
          curTempPos.x() = 0;
        }
        curTempPos.y() = k * curTempPos.x() - k * mStart.x() + mStart.y();
        curEndPos.y() = k * curEndPos.x() - k * mStart.x() + mStart.y();
      }
    }
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(preTempPos.x(), preTempPos.y()));
    dc.LineTo(CPoint(preEndPos.x(), preEndPos.y()));
    //绘制新的橡皮线
    dc.MoveTo(CPoint(curTempPos.x(), curTempPos.y()));
    dc.LineTo(CPoint(curEndPos.x(), curEndPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curEndPos;  //记录最新位置
    mTemp = curTempPos;
  } else {
  }
  return 0;
}
int Create2DLine::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(mTemp.x(), mTemp.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}