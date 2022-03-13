#include "pch.h"
#include "Create2DPolygon.h"
#include "CG2DPolygon.h"
#include "CGDI2DView.h"


Create2DPolygon::Create2DPolygon(CGView* pview /* = nullptr*/)
    : UIEventListener(pview) {
  m_nStep = 0;
  m_ptPolyFirst = {0, 0};  //折线中最后一个点
  m_ptPolyLast = {0, 0};   //折线中最后一个点
  m_PointOld = {0, 0};     //橡皮线中的最后一个点
  m_PolyCount = 0;
}
Create2DPolygon::~Create2DPolygon() {}
int Create2DPolygon::GetType()  //命令类型
{
  return cmd2dPolygon;
}
int Create2DPolygon::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //每次单击鼠标左键时操作步骤计数加一
  if (m_nStep == 1)  //第一次单击鼠标左键，记录起点
  {
    m_ptPolyFirst.x = pos.x();
    m_ptPolyFirst.y = pos.y();
    m_ArrayPoint[m_PolyCount].x = pos.x();
    m_ArrayPoint[m_PolyCount++].y = pos.y();
    m_ptPolyLast.x = pos.x();
    m_ptPolyLast.y = pos.y();
    m_PointOld.x = pos.x();
    m_PointOld.y = pos.y();
    mView->Prompt(_T("请继续输入多边形中的点"));
  } else {
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - m_ptPolyLast.x) <=
          abs(pos.y() - m_ptPolyLast.y))  // x方向变化小，垂直线
      {
        m_ArrayPoint[m_PolyCount].x = m_ArrayPoint[m_PolyCount - 1].x;
        m_ArrayPoint[m_PolyCount].y = pos.y();
        m_ptPolyLast.x = m_ArrayPoint[m_PolyCount].x;
        m_ptPolyLast.y = m_ArrayPoint[m_PolyCount].y;
        m_PointOld.x = m_ArrayPoint[m_PolyCount].x;
        m_PointOld.y = m_ArrayPoint[m_PolyCount].y;
        m_PolyCount++;
      } else  // x方向变化大，水平线
      {
        m_ArrayPoint[m_PolyCount].x = pos.x();
        m_ArrayPoint[m_PolyCount].y = m_ArrayPoint[m_PolyCount - 1].y;
        m_ptPolyLast.x = m_ArrayPoint[m_PolyCount].x;
        m_ptPolyLast.y = m_ArrayPoint[m_PolyCount].y;
        m_PointOld.x = m_ArrayPoint[m_PolyCount].x;
        m_PointOld.y = m_ArrayPoint[m_PolyCount].y;
        m_PolyCount++;
      }
    } else {
      m_ArrayPoint[m_PolyCount].x = pos.x();
      m_ArrayPoint[m_PolyCount++].y = pos.y();
      m_ptPolyLast.x = pos.x();
      m_ptPolyLast.y = pos.y();
      m_PointOld.x = pos.x();
      m_PointOld.y = pos.y();
    }
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    if (m_PolyCount > 1)  //点超过1个时，画折线
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    mView->Prompt(_T("请继续输入多边形中的点"));
  }
  return 0;
}
int Create2DPolygon::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("请输入多边形的起点"));
  } else {
    Pos2i curPos;
    //判断是否按下SHIFT键，绘制水平线或垂直线
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - m_ptPolyLast.x) <=
          abs(pos.y() - m_ptPolyLast.y))  // x方向变化小，垂直线
      {
        curPos.x() = m_ptPolyLast.x;
        curPos.y() = pos.y();
      } else {
        curPos.x() = pos.x();
        curPos.y() = m_ptPolyLast.y;
      }
    } else {
      curPos = pos;
    }
    mView->Prompt(_T("请继续输入多边形中的点"));
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);  //逆转当前屏幕颜色来画线的绘图方式
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);  
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(CPoint(curPos.x(), curPos.y()));  //绘制当前的临时线
    m_PointOld.x = curPos.x();
    m_PointOld.y = curPos.y();
  }
  return 0;
}

int Create2DPolygon::OnRButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep >= 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);
    if (m_PolyCount > 1)  //点超过1个时，画折线
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    //获取折线中各点的场景坐标
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
  }
  m_nStep = 0;
  m_PolyCount = 0;
  mView->Prompt(_T("请输入多边形的起点"));
}

int Create2DPolygon::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep >= 1)  //如果已经单击左键一次，则结束操作前删除橡皮线
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);
    if (m_PolyCount > 1)  //点超过1个时，画折线
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  m_PolyCount = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}
