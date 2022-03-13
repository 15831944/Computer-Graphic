#include "pch.h"
#include "Create2DCircle2PDiameter.h"
#include <cmath>
#include "CG2DCircle.h"
#include "CGDI2DView.h"

Create2DCircle2PDiameter::Create2DCircle2PDiameter(CGView* pview /* = nullptr*/)
    : UIEventListener(pview),
      mCenter(0, 0),
      Upperleft(0, 0),
      Lowerright(0, 0),
      mDot1(0, 0),
      mDot2(0, 0) {
  m_nStep = 0;
  Radius = 0;
}
Create2DCircle2PDiameter::~Create2DCircle2PDiameter() {}
int Create2DCircle2PDiameter::GetType()  //��������
{
  return cmd2dCricle2PDiameter;
}
int Create2DCircle2PDiameter::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼Բ��
  {
    mDot1 = mDot2 = mCenter = Upperleft = Lowerright = pos;
    mView->Prompt(_T("������ֱ������һ���˵�"));
  } else if (m_nStep == 2) {
    //���������Ƥ��
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
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
    //��ȡԲ�Ķ�Ӧ�ĳ�������
    Vec2d Center = mView->ViewPortToWorld(mCenter);
    //����Բ����ӵ�����
    CG2DCircle* pCircle = new CG2DCircle(Center, Radius);
    pCircle->setPenColor(mView->PenColor());  //��̬
    pCircle->setPenWidth(mView->PenWidth());
    pCircle->setPenStyle(mView->PenStyle());
    pCircle->setBrushUse(mView->UseBrush());
    pCircle->setBrushColor(mView->BrushColor());
    pCircle->setBrushIndex(mView->BrushIndex());
    mView->addRenderable(pCircle);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ����Բ
    mView->Prompt(_T("������ֱ����һ���˵�"));
  } else {
  }
  return 0;
}
int Create2DCircle2PDiameter::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 0) {
    mView->Prompt(_T("������ֱ����һ���˵�"));
  } else if (m_nStep == 1) {
    Pos2i preupperleft, prelowerright;
    preupperleft = Upperleft;
    prelowerright = Lowerright;
    //�����ϴε���Ƥ��
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
    dc.Ellipse(preupperleft.x(), preupperleft.y(), prelowerright.x(),
               prelowerright.y());
    //�����µ���Ƥ��
    mDot2 = pos;
    //��Բ�İ뾶
    mCenter.x() = (mDot1.x() + mDot2.x()) / 2;
    mCenter.y() = (mDot1.y() + mDot2.y()) / 2;
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
int Create2DCircle2PDiameter::Cancel() {
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
    dc.SetROP2(R2_NOTXORPEN);
    dc.Ellipse(Upperleft.x(), Upperleft.y(), Lowerright.x(), Lowerright.y());
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrush);
    if (pBrush)
      delete pBrush;
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}