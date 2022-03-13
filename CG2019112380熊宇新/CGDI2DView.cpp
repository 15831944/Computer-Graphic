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
void CGDI2DView::OnDraw(CDC* pDC)  // ��д�Ի��Ƹ���ͼ
{
  //��������ʵ��
}
//����Ĭ���ӿڲ���
bool CGDI2DView::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  // mDefaultViewport.setViewPort(xl, yb, xr, yt);
  //��������ʵ��
  return false;
}
//��Ⱦ����
bool CGDI2DView::RenderScene() {
  //��������ʵ��
  return false;
}
