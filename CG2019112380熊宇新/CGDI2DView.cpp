#include "pch.h"
#include "CGDI2DView.h"
#include "CGDI2DRenderContext.h"

IMPLEMENT_DYNCREATE(CGDI2DView, CGView)
CGDI2DView::CGDI2DView() {
  m_pRenderContext = new CGDI2DRenderContext(this);
}
CGDI2DView::~CGDI2DView() {
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
}
void CGDI2DView::OnDraw(CDC* pDC)  // 重写以绘制该视图
{
  //派生类中实现
}
//设置默认视口参数
bool CGDI2DView::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  // mDefaultViewport.setViewPort(xl, yb, xr, yt);
  //派生类中实现
  return false;
}
//渲染场景
bool CGDI2DView::RenderScene() {
  //派生类中实现
  return false;
}
