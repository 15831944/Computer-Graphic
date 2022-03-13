#include "pch.h"
#include "Create2DSeedFill.h"
#include"CG2DSeedFill.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"

Create2DSeedFill::~Create2DSeedFill() {}
int Create2DSeedFill::OnLButtonDown(UINT nF1ags, const Pos2i& pos) {
  if (!mView)
    return -1;
  mSeed = pos;
  Vec2d seed = mView->ViewPortToWorld(mSeed);
  CG2DSeedFill* pFill = new CG2DSeedFill(seed);
  pFill->setBrushColor(mView->BrushColor());
  pFill->setBounaryColor(mView->BoundColor());
  pFill->setAlog(mView->FillAlgorithm());
  mView->addRenderable(pFill);
  mView->Invalidate();
  mView->UpdateWindow();
  m_nStep = 0;  //��Ϊ0����д��ʼ�����߶�
  mView->Prompt(_T("������Ҫ�������ӵ�"));
}
int Create2DSeedFill::Cancel() {
  if (!mView)
    return -1;
  m_nStep;
  mView->Prompt(_T("����"));
  return 0;
}
