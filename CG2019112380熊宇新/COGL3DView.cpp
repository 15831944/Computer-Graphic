#include "pch.h"
#include "COGL3DView.h"
#include "COGL3DRenderContext.h"

// COGL3DView
IMPLEMENT_DYNCREATE(COGL3DView, CGView)
BEGIN_MESSAGE_MAP(COGL3DView, CGView)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
END_MESSAGE_MAP()
// CGDI3DView 构造/析构
COGL3DView::COGL3DView() {}
COGL3DView::~COGL3DView() {
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
}
void COGL3DView::OnDraw(CDC* pDC)  // 重写以绘制该视图
{}
BOOL COGL3DView::PreCreateWindow(CREATESTRUCT& cs) {
  cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
  return CGView::PreCreateWindow(cs);
}
//渲染场景
bool COGL3DView::RenderScene() {
  return false;
}
int COGL3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CGView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // TODO: 在此添加您专用的创建代码
  if (m_pRenderContext == nullptr)
    m_pRenderContext = new COGL3DRenderContext(this);
  if (m_pRenderContext != nullptr)
    if (!m_pRenderContext->InitRenderContext())
      return -1;
  return 0;
}
void COGL3DView::OnDestroy() {
  CGView::OnDestroy();
  // TODO: 在此处添加消息处理程序代码
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
}
BOOL COGL3DView::OnEraseBkgnd(CDC* pDC) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  return CGView::OnEraseBkgnd(pDC);
  // return TRUE;
}
void COGL3DView::OnSize(UINT nType, int cx, int cy) {
  CGView::OnSize(nType, cx, cy);
  // TODO: 在此处添加消息处理程序代码
}