#include "pch.h"
#include "Create2DPolygon.h"
#include "CG2DPolygon.h"
#include "CGDI2DView.h"


Create2DPolygon::Create2DPolygon(CGView* pview /* = nullptr*/)
    : UIEventListener(pview) {
  m_nStep = 0;
  m_ptPolyFirst = {0, 0};  //���������һ����
  m_ptPolyLast = {0, 0};   //���������һ����
  m_PointOld = {0, 0};     //��Ƥ���е����һ����
  m_PolyCount = 0;
}
Create2DPolygon::~Create2DPolygon() {}
int Create2DPolygon::GetType()  //��������
{
  return cmd2dPolygon;
}
int Create2DPolygon::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼���
  {
    m_ptPolyFirst.x = pos.x();
    m_ptPolyFirst.y = pos.y();
    m_ArrayPoint[m_PolyCount].x = pos.x();
    m_ArrayPoint[m_PolyCount++].y = pos.y();
    m_ptPolyLast.x = pos.x();
    m_ptPolyLast.y = pos.y();
    m_PointOld.x = pos.x();
    m_PointOld.y = pos.y();
    mView->Prompt(_T("��������������еĵ�"));
  } else {
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - m_ptPolyLast.x) <=
          abs(pos.y() - m_ptPolyLast.y))  // x����仯С����ֱ��
      {
        m_ArrayPoint[m_PolyCount].x = m_ArrayPoint[m_PolyCount - 1].x;
        m_ArrayPoint[m_PolyCount].y = pos.y();
        m_ptPolyLast.x = m_ArrayPoint[m_PolyCount].x;
        m_ptPolyLast.y = m_ArrayPoint[m_PolyCount].y;
        m_PointOld.x = m_ArrayPoint[m_PolyCount].x;
        m_PointOld.y = m_ArrayPoint[m_PolyCount].y;
        m_PolyCount++;
      } else  // x����仯��ˮƽ��
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
    if (m_PolyCount > 1)  //�㳬��1��ʱ��������
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    mView->Prompt(_T("��������������еĵ�"));
  }
  return 0;
}
int Create2DPolygon::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("���������ε����"));
  } else {
    Pos2i curPos;
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - m_ptPolyLast.x) <=
          abs(pos.y() - m_ptPolyLast.y))  // x����仯С����ֱ��
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
    mView->Prompt(_T("��������������еĵ�"));
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);  //��ת��ǰ��Ļ��ɫ�����ߵĻ�ͼ��ʽ
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);  
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(CPoint(curPos.x(), curPos.y()));  //���Ƶ�ǰ����ʱ��
    m_PointOld.x = curPos.x();
    m_PointOld.y = curPos.y();
  }
  return 0;
}

int Create2DPolygon::OnRButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep >= 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);
    if (m_PolyCount > 1)  //�㳬��1��ʱ��������
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
    //��ȡ�����и���ĳ�������
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
  }
  m_nStep = 0;
  m_PolyCount = 0;
  mView->Prompt(_T("���������ε����"));
}

int Create2DPolygon::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep >= 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(m_ptPolyLast);
    dc.LineTo(m_PointOld);
    if (m_PolyCount > 1)  //�㳬��1��ʱ��������
      dc.Polyline(m_ArrayPoint, m_PolyCount);
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  m_PolyCount = 0;
  mView->Prompt(_T("����"));
  return 0;
}
