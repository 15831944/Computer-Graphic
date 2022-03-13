#include "pch.h"
#include <cmath>
#include "CG2DCircle.h"
#include "CGDI2DView.h"
#include "Create2DCircleCR.h"

Create2DCircleCR::Create2DCircleCR(
    CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mCenter(0, 0), Upperleft(0, 0), Lowerright(0, 0) {
  m_nStep = 0;
  Radius = 0;
}
Create2DCircleCR::~Create2DCircleCR() {}
int Create2DCircleCR::GetType()  //命令类型
{
  return cmd2dCircleCenterRadius;
}
int Create2DCircleCR::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;  //每次单击鼠标左键时操作步骤计数加一

  if (m_nStep == 1)  //第一次单击鼠标左键，记录圆心
  {
    mCenter = Upperleft = Lowerright = pos;
    mView->Prompt(_T("请输入圆上的一点"));
  } else if (m_nStep == 2) {
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
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
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
    mView->Prompt(_T("请输入圆心"));
  } else {
  }
  return 0;
}
int Create2DCircleCR::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入圆心"));
  } else if (m_nStep == 1) {
    Pos2i preupperleft, prelowerright;
    preupperleft = Upperleft;
    prelowerright = Lowerright;
    //擦除上次的橡皮线
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
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
    dc.Ellipse(preupperleft.x(), preupperleft.y(), prelowerright.x(),
               prelowerright.y());
    //绘制新的橡皮线
    Radius = sqrt((pos.x() - mCenter.x()) * (pos.x() - mCenter.x()) +
                  (pos.y() - mCenter.y()) * (pos.y() - mCenter.y()));
    Upperleft.x() = mCenter.x() - int(Radius + 0.5);
    Upperleft.y() = mCenter.y() - int(Radius + 0.5);
    Lowerright.x() = mCenter.x() + int(Radius + 0.5);
    Lowerright.y() = mCenter.y() + int(Radius + 0.5);
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
  } else {
  }
  return 0;
}
int Create2DCircleCR::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
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
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
  }
  m_nStep = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}