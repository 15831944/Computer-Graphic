#ifndef _CGDI2DVIEW_H_INCLUDED
#define _CGDI2DVIEW_H_INCLUDED
#include "CGView.h"
class CGDI2DView : public CGView {
  DECLARE_DYNCREATE(CGDI2DView)
 protected:  // �������л�����
  CGDI2DView();
  // ����
 public:
  // ʵ��
 public:
  virtual ~CGDI2DView();
  // ��д
 public:
  virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
  //����Ĭ���ӿڲ���
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //��Ⱦ����
  virtual bool RenderScene();
};
#endif  //_CGDI2DVIEW_H_INCLUDE