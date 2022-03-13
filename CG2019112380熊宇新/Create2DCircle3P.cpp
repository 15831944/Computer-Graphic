#include "pch.h"
#include <cmath>
#include "CG2DCircle.h"
#include "CGDI2DView.h"
#include "Create2DCircle3P.h"


Create2DCircle3P::Create2DCircle3P(CGView* pview /* = nullptr*/)
    : UIEventListener(pview),
      mCenter(0, 0),
      Upperleft(0, 0),
      Lowerright(0, 0),
      mStart(0, 0),
      mMiddle(0, 0),
      mEnd(0, 0) {
  m_nStep = 0;
  Radius = 0;
}
Create2DCircle3P::~Create2DCircle3P() {}
int Create2DCircle3P::GetType()  //命令类型
{
  return cmd2dCricle3PCircum;
}
int Create2DCircle3P::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;  //每次单击鼠标左键时操作步骤计数加一

  if (m_nStep == 1)  //第一次单击鼠标左键，记录第一个点
  {
    mStart = mMiddle = mEnd = pos;
    mView->Prompt(_T("请继续输入圆上的一点"));
  } else if (m_nStep == 2) {
    mMiddle = pos;
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mMiddle.x(), mMiddle.y());
    dc.SelectObject(pOldPen);
    mView->Prompt(_T("请继续输入圆上的另一个点"));

  } else if (m_nStep == 3) {
    mEnd = pos;
    Pos2i mStartTomMiddle, mMiddleTomEnd, middle1, middle2;
    mStartTomMiddle.x() = mMiddle.x() - mStart.x();
    mStartTomMiddle.y() = mMiddle.y() - mStart.y();
    mMiddleTomEnd.x() = mEnd.x() - mMiddle.x();
    mMiddleTomEnd.y() = mEnd.y() - mMiddle.y();
    middle1.x() = (mMiddle.x() + mStart.x()) / 2;
    middle1.y() = (mMiddle.y() + mStart.y()) / 2;
    middle2.x() = (mMiddle.x() + mEnd.x()) / 2;
    middle2.y() = (mMiddle.y() + mEnd.y()) / 2;
    int a1, b1, c1, a2, b2, c2;
    a1 = mStartTomMiddle.x();
    b1 = mStartTomMiddle.y();
    c1 = -1 * (middle1.x() * a1 + middle1.y() * b1);

    a2 = mMiddleTomEnd.x();
    b2 = mMiddleTomEnd.y();
    c2 = -1 * (middle2.x() * a2 + middle2.y() * b2);
    if (a1 * b2 == b1 * a2)  //两直线平行
    {
      flag = -1;
    } else {
      flag = 0;
      mCenter.x() = (int)(c1 * b2 - b1 * c2) / (b1 * a2 - a1 * b2);
      mCenter.y() = (int)(a1 * c2 - c1 * a2) / (b1 * a2 - a1 * b2);
    }
    //擦除最后橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    CBrush *pOldBrush, *pBrush = nullptr;
    if (!mView->UseBrush()) {
      pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
    } else if (mView->BrushIndex() != -1) {
      pBrush = new CBrush(mView->BrushIndex(), mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    } else {
      pBrush = new CBrush(mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    }
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mMiddle.x(), mMiddle.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    dc.LineTo(mStart.x(), mStart.y());
    if (flag != -1) {
      Radius = sqrt((mCenter.x() - mStart.x()) * (mCenter.x() - mStart.x()) +
                    (mCenter.y() - mStart.y()) * (mCenter.y() - mStart.y()));
      dc.Ellipse(
          mCenter.x() - (int)(Radius + 0.5), mCenter.y() - (int)(Radius + 0.5),
          mCenter.x() + (int)(Radius + 0.5), mCenter.y() + (int)(Radius + 0.5));
    }
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
    //获取圆心对应的场景坐标
    Vec2d Center = mView->ViewPortToWorld(mCenter);
    //创建圆并添加到场景
    CG2DCircle* pCircle = new CG2DCircle(Center, Radius);
    pCircle->setPenColor(mView->PenColor());  //多态
    pCircle->setPenWidth(mView->PenWidth());
    pCircle->setPenStyle(mView->PenStyle());
    pCircle->setBrushUse(mView->UseBrush());
    pCircle->setBrushColor(mView->BrushColor());
    pCircle->setBrushIndex(mView->BrushIndex());
    mView->addRenderable(pCircle);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //设为0可重写开始绘制圆
    flag = -1;
    mView->Prompt(_T("请输入圆上的一点"));
  }
  return 0;
}
int Create2DCircle3P::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入圆上的一点"));
  } else if (m_nStep == 1) {
    Pos2i preMiddle = mMiddle;
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(preMiddle.x(), preMiddle.y());
    //绘制新的橡皮线
    mMiddle = pos;
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mMiddle.x(), mMiddle.y());
    dc.SelectObject(pOldPen);
  } else if (m_nStep == 2) {
    Pos2i preEnd = mEnd;
    Pos2i preCenter = mCenter;
    double preRadius = Radius;
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    CBrush *pOldBrush, *pBrush = nullptr;
    if (!mView->UseBrush()) {
      pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
    } else if (mView->BrushIndex() != -1) {
      pBrush = new CBrush(mView->BrushIndex(), mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    } else {
      pBrush = new CBrush(mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    }
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(preEnd.x(), preEnd.y());
    dc.MoveTo(mMiddle.x(), mMiddle.y());
    dc.LineTo(preEnd.x(), preEnd.y());
    if (flag != -1)
      dc.Ellipse(preCenter.x() - (int)(preRadius + 0.5),
                 preCenter.y() - (int)(preRadius + 0.5),
                 preCenter.x() + (int)(preRadius + 0.5),
                 preCenter.y() + (int)(preRadius + 0.5));
    //绘制新的橡皮线
    mEnd = pos;
    Pos2i mStartTomMiddle, mMiddleTomEnd, middle1, middle2;
    mStartTomMiddle.x() = mMiddle.x() - mStart.x();
    mStartTomMiddle.y() = mMiddle.y() - mStart.y();
    mMiddleTomEnd.x() = mEnd.x() - mMiddle.x();
    mMiddleTomEnd.y() = mEnd.y() - mMiddle.y();
    middle1.x() = (mMiddle.x() + mStart.x()) / 2;
    middle1.y() = (mMiddle.y() + mStart.y()) / 2;
    middle2.x() = (mMiddle.x() + mEnd.x()) / 2;
    middle2.y() = (mMiddle.y() + mEnd.y()) / 2;
    int a1, b1, c1, a2, b2, c2;
    a1 = mStartTomMiddle.x();
    b1 = mStartTomMiddle.y();
    c1 = -1 * (middle1.x() * a1 + middle1.y() * b1);

    a2 = mMiddleTomEnd.x();
    b2 = mMiddleTomEnd.y();
    c2 = -1 * (middle2.x() * a2 + middle2.y() * b2);
    if (a1 * b2 == b1 * a2)  //两直线平行
    {
      flag = -1;
    } else {
      flag = 0;
      mCenter.x() = (int)(c1 * b2 - b1 * c2) / (b1 * a2 - a1 * b2);
      mCenter.y() = (int)(a1 * c2 - c1 * a2) / (b1 * a2 - a1 * b2);
    }
    if (flag != -1) {
      Radius = sqrt((mCenter.x() - mStart.x()) * (mCenter.x() - mStart.x()) +
                    (mCenter.y() - mStart.y()) * (mCenter.y() - mStart.y()));
      dc.Ellipse(
          mCenter.x() - (int)(Radius + 0.5), mCenter.y() - (int)(Radius + 0.5),
          mCenter.x() + (int)(Radius + 0.5), mCenter.y() + (int)(Radius + 0.5));
    } else {
    }
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    dc.MoveTo(mMiddle.x(), mMiddle.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
  } else {
  }
  return 0;
}
int Create2DCircle3P::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1) {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mMiddle.x(), mMiddle.y());
    mView->Invalidate();
    mView->UpdateWindow();
    dc.SelectObject(pOldPen);
  }
  if (m_nStep == 2)  //如果已经单击左键一次，则结束操作前删除橡皮线
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    CBrush *pOldBrush, *pBrush = nullptr;
    if (!mView->UseBrush()) {
      pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
    } else if (mView->BrushIndex() != -1) {
      pBrush = new CBrush(mView->BrushIndex(), mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    } else {
      pBrush = new CBrush(mView->BrushColor());
      pOldBrush = dc.SelectObject(pBrush);
    }
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(mStart.x(), mStart.y());
    dc.LineTo(mMiddle.x(), mMiddle.y());
    dc.LineTo(mEnd.x(), mEnd.y());
    dc.LineTo(mStart.x(), mStart.y());
    if (flag != -1) {
      Radius = sqrt((mCenter.x() - mStart.x()) * (mCenter.x() - mStart.x()) +
                    (mCenter.y() - mStart.y()) * (mCenter.y() - mStart.y()));
      dc.Ellipse(
          mCenter.x() - (int)(Radius + 0.5), mCenter.y() - (int)(Radius + 0.5),
          mCenter.x() + (int)(Radius + 0.5), mCenter.y() + (int)(Radius + 0.5));
    }
    mView->Invalidate();
    mView->UpdateWindow();
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
  }
  m_nStep = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}
