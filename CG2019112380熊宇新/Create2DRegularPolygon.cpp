#include "pch.h"
#include "Create2DRegularPolygon.h"
#include "CG2DPolygon.h"
#include "CGDI2DView.h"
#include "cmath"


Create2DRegularPolygon::Create2DRegularPolygon(CGView* pview /* = nullptr*/)
    : UIEventListener(pview) {
  m_nStep = 0;
  m_PolyCount = 0;
  mCenter = {0, 0};  //��������м�ĵ�
  angle = 0;
  flag = 0;
}
Create2DRegularPolygon::~Create2DRegularPolygon() {}
int Create2DRegularPolygon::GetType()  //��������
{
  return cmd2dRegularPolygon;
}
int Create2DRegularPolygon::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼�м�ĵ�
  {
    mCenter.x = pos.x();
    mCenter.y = pos.y();
    for (int i = 0; i < m_PolyCount; ++i) {
      m_ArrayPoint[i].x = 0;
      m_ArrayPoint[i].y = 0;
    }
    m_PolyCount = mView->RegularEdges();
    angle = 2 * dPi / m_PolyCount;
    mView->Prompt(_T("�����������������еĵ�"));
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
    //����������Ƥ��
    if (m_PolyCount > 1)  //�㳬��1��ʱ��������
      dc.Polygon(m_ArrayPoint, m_PolyCount);
    Vec2i ArrayTemp[255];
    for (int i = 0; i < m_PolyCount; ++i) {
      ArrayTemp[i].x() = m_ArrayPoint[i].x;
      ArrayTemp[i].y() = m_ArrayPoint[i].y;
    }
    Vec2d ArrayPoint[255];
    for (int i = 0; i < m_PolyCount; ++i)
      ArrayPoint[i] = mView->ViewPortToWorld(ArrayTemp[i]);
    //�������߲���ӵ�����
    CG2DPolygon* pPolygon = new CG2DPolygon(ArrayPoint, m_PolyCount);
    pPolygon->setPenColor(mView->PenColor());  //��̬
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
    mView->Prompt(_T("������������ε����"));
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
    dc.SetROP2(R2_NOTXORPEN);  //��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
    //�����ϴε���Ƥ��
    if (flag != 0)
      dc.Polygon(m_ArrayPoint, m_PolyCount);
    else
      flag = 1;
    //�����µ���Ƥ��
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
    mView->Prompt(_T("������������ε��е�"));
  } else {
  }
  return 0;
}

int Create2DRegularPolygon::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
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
    dc.SetROP2(R2_NOTXORPEN);  //��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
    //�����ϴε���Ƥ��
    dc.Polygon(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
  }
  m_nStep = 0;
  m_PolyCount = 0;
  angle = 0;
  flag = 0;
  mView->Prompt(_T("����"));
  return 0;
}
