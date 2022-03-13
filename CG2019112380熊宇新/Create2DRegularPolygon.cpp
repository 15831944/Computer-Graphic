#include "pch.h"
#include "Create2DRegularPolygon.h"
#include "CG2DPolygon.h"
#include "CGDI2DView.h"
#include "cmath"


Create2DRegularPolygon::Create2DRegularPolygon(CGView* pview /* = nullptr*/)
    : UIEventListener(pview) {
  m_nStep = 0;
  m_PolyCount = 0;
  mCenter = {0, 0};  //正多边形中间的点
  angle = 0;
  flag = 0;
}
Create2DRegularPolygon::~Create2DRegularPolygon() {}
int Create2DRegularPolygon::GetType()  //命令类型
{
  return cmd2dRegularPolygon;
}
int Create2DRegularPolygon::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录中间的点
  {
    mCenter.x = pos.x();
    mCenter.y = pos.y();
    for (int i = 0; i < m_PolyCount; ++i) {
      m_ArrayPoint[i].x = 0;
      m_ArrayPoint[i].y = 0;
    }
    m_PolyCount = mView->RegularEdges();
    angle = 2 * dPi / m_PolyCount;
    mView->Prompt(_T("请继续输入正多边形中的点"));
  } else {
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
    //擦除最后的橡皮线
    if (m_PolyCount > 1)  //点超过1个时，画折线
      dc.Polygon(m_ArrayPoint, m_PolyCount);
    Vec2i ArrayTemp[255];
    for (int i = 0; i < m_PolyCount; ++i) {
      ArrayTemp[i].x() = m_ArrayPoint[i].x;
      ArrayTemp[i].y() = m_ArrayPoint[i].y;
    }
    Vec2d ArrayPoint[255];
    for (int i = 0; i < m_PolyCount; ++i)
      ArrayPoint[i] = mView->ViewPortToWorld(ArrayTemp[i]);
    //创建折线并添加到场景
    CG2DPolygon* pPolygon = new CG2DPolygon(ArrayPoint, m_PolyCount);
    pPolygon->setPenColor(mView->PenColor());  //多态
    pPolygon->setPenWidth(mView->PenWidth());
    pPolygon->setPenStyle(mView->PenStyle());
    pPolygon->setBrushUse(mView->UseBrush());
    pPolygon->setBrushColor(mView->BrushColor());
    pPolygon->setBrushIndex(mView->BrushIndex());
    mView->addRenderable(pPolygon);
    mView->Invalidate();
    mView->UpdateWindow();
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    m_nStep = 0;
    m_PolyCount = 0;
    angle = 0;
    flag = 0;
    mView->Prompt(_T("请输入正多边形的起点"));
  }
  return 0;
}
int Create2DRegularPolygon::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1) {
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
    dc.SetROP2(R2_NOTXORPEN);  //逆转当前屏幕颜色来画线的绘图方式
    //擦除上次的橡皮线
    if (flag != 0)
      dc.Polygon(m_ArrayPoint, m_PolyCount);
    else
      flag = 1;
    //绘制新的橡皮线
    m_ArrayPoint[0].x = pos.x();
    m_ArrayPoint[0].y = pos.y();
    double prex = m_ArrayPoint[0].x;
    double prey = m_ArrayPoint[0].y;
    for (int i = 1; i < m_PolyCount; ++i) {
      double tempx, tempy;
      tempx = (prex - mCenter.x) * cos(angle) -
              (prey - mCenter.y) * sin(angle) + mCenter.x;
      tempy = (prex - mCenter.x) * sin(angle) +
              (prey - mCenter.y) * cos(angle) + mCenter.y;
      m_ArrayPoint[i].x = (int)(tempx + 0.5);
      m_ArrayPoint[i].y = (int)(tempy + 0.5);
      prex = tempx;
      prey = tempy;
    }
    dc.Polygon(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    mView->Prompt(_T("请输入正多边形的中点"));
  } else {
  }
  return 0;
}

int Create2DRegularPolygon::Cancel() {
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
    dc.SetROP2(R2_NOTXORPEN);  //逆转当前屏幕颜色来画线的绘图方式
    //擦除上次的橡皮线
    dc.Polygon(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
  }
  m_nStep = 0;
  m_PolyCount = 0;
  angle = 0;
  flag = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}
