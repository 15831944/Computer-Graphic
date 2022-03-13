#ifndef _COGL3DVIEW_H_INCLUDED
#define _COGL3DVIEW_H_INCLUDED
#pragma once
#include "CGView.h"
class COGL3DView : public CGView {
  DECLARE_DYNCREATE(COGL3DView)
 protected:
  COGL3DView();
  virtual ~COGL3DView();

 public:
  virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  //��Ⱦ����
  virtual bool RenderScene();

 protected:
  DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif  //_COGL3DVIEW_H_INCLUDED