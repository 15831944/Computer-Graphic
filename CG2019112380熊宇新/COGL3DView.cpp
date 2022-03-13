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
// CGDI3DView ����/����
COGL3DView::COGL3DView() {}
COGL3DView::~COGL3DView() {
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
}
void COGL3DView::OnDraw(CDC* pDC)  // ��д�Ի��Ƹ���ͼ
{}
BOOL COGL3DView::PreCreateWindow(CREATESTRUCT& cs) {
  cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
  return CGView::PreCreateWindow(cs);
}
//��Ⱦ����
bool COGL3DView::RenderScene() {
  return false;
}
int COGL3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CGView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // TODO: �ڴ������ר�õĴ�������
  if (m_pRenderContext == nullptr)
    m_pRenderContext = new COGL3DRenderContext(this);
  if (m_pRenderContext != nullptr)
    if (!m_pRenderContext->InitRenderContext())
      return -1;
  return 0;
}
void COGL3DView::OnDestroy() {
  CGView::OnDestroy();
  // TODO: �ڴ˴������Ϣ����������
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
}
BOOL COGL3DView::OnEraseBkgnd(CDC* pDC) {
  // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
  return CGView::OnEraseBkgnd(pDC);
  // return TRUE;
}
void COGL3DView::OnSize(UINT nType, int cx, int cy) {
  CGView::OnSize(nType, cx, cy);
  // TODO: �ڴ˴������Ϣ����������
}