#include"pch.h"
#include"CGRenderContext.h"
#include"CGDI2DView.h"
#include"CG2DSeedFill.h"
#include"CGRenderContext.h"
#include"CG2DRenderable.h"
#include"CGCamera.h"
#include"CGScene.h"
IMPLEMENT_SERIAL(CG2DSeedFill, CG2DRenderable, 1)
CG2DSeedFill::CG2DSeedFill()
    : CG2DRenderable(CString("CG2DSeedFill")),
      mSeed(0, 0),
      mBounaryColor(0x00ffffff),
      mdir(4),
      mAlog(false) {}
CG2DSeedFill::CG2DSeedFill(const Vec2d& seed)
    : CG2DRenderable(CString("CG2DSeedFill")),
      mSeed(seed),
      mBounaryColor(0x00ffffff),
      mdir(4),
      mAlog(false) {
  m_Name.Format(_T("填充-%ld"), sID);
}
void CG2DSeedFill::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  CClientDC dc(pRC->getView());
  Vec2i seed = camera->WorldtoViewPort(mSeed);
  if (mAlog)
    pRC->SeedFill_Boundary(seed, brushColor(), BounaryColor(), mdir);
  else
    pRC->SeedFill_Point(seed, brushColor(), mdir);
}