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
  m_nStep = 0;  //设为0可重写开始绘制线段
  mView->Prompt(_T("请输入要填充的种子点"));
}
int Create2DSeedFill::Cancel() {
  if (!mView)
    return -1;
  m_nStep;
  mView->Prompt(_T("就绪"));
  return 0;
}
