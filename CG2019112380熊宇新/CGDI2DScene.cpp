#include "pch.h"
#include "CGDI2DScene.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"
#include "CGRenderable.h"

IMPLEMENT_SERIAL(CGDI2DScene, CGScene, 1)
CGDI2DScene::CGDI2DScene() {
  mDefaultCamera = new CGDI2DCamera();  //初始化默认相机
}
CGDI2DScene::~CGDI2DScene() {
  if (mDefaultCamera) {
    delete mDefaultCamera;
    mDefaultCamera = nullptr;
  }
}
//序列化
void CGDI2DScene::Serialize(CArchive& ar) {
  CGScene::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}
//渲染场景到指定客户区（依赖CGDI2DMfcView）
bool CGDI2DScene::RenderScene(CGView* pView) {
  if (pView == nullptr || !pView->IsKindOf(RUNTIME_CLASS(CGDI2DView)))
    return false;
  CRect rc;
  pView->GetClientRect(&rc);
  //
  mDefaultCamera->setClientRect(0, 0, rc.Width(), rc.Height());   //客户区
  mDefaultCamera->setViewPortBox(0, 0, rc.Width(), rc.Height());  //视口
  //测试窗口
  // mDefaultCamera->setViewWindowBox(0, 0, rc.Width(), rc.Height());
  //绘制场景中所有对象
  CGDI2DView* pv = dynamic_cast<CGDI2DView*>(pView);
  if (pv != nullptr) {
    CGRenderContext* pRC = pv->GetRenderContext();
    if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)))
      return false;
    CGDI2DRenderContext* pRenderContext =
        dynamic_cast<CGDI2DRenderContext*>(pRC);
    if (pRenderContext == nullptr)
      return false;
    pRenderContext->setView(pView);
    int i = 0, cnt = mRenderables.GetSize();
    while (i < cnt) {
      if (mRenderables.GetAt(i) != nullptr) {
        mRenderables.GetAt(i)->Render(pRenderContext);
      }
      i++;
    }
  }
  CClientDC dc(pView);
  double angle = -RadWorldToViewPort(0);
  Vec2i vi = WorldToViewPort(Vec2d(0, 0));
  CPen Rpen, Bpen;
  Rpen.CreatePen(PS_SOLID, 1,RGB(0,0,0));
  Bpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
  CPen* oldpen = dc.SelectObject(&Rpen);
  dc.MoveTo(vi.x() - 0xffff * cos(angle) + 0.5,
            vi.y() - 0xffff * sin(angle) + 0.5);
  dc.LineTo(vi.x() + 0xffff * cos(angle) + 0.5,
            vi.y() + 0xffff * sin(angle) + 0.5);
  dc.SelectObject(&Bpen);
  dc.MoveTo(vi.x() - 0xffff * cos(angle + dPi / 2) + 0.5,
            vi.y() - 0xffff * sin(angle + dPi / 2) + 0.5);
  dc.LineTo(vi.x() + 0xffff * cos(angle + dPi / 2) + 0.5,
            vi.y() + 0xffff * sin(angle + dPi / 2) + 0.5);
  dc.SelectObject(oldpen);
  Rpen.DeleteObject();
  Bpen.DeleteObject();
  return true;
}
