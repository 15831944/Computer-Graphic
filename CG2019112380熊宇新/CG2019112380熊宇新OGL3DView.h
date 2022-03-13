// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û�����
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο�����
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CG2019112380������OGL3DView.h: CCG2019112380������OGL3DView ��Ľӿ�
//

#pragma once

class CCG2019112380������OGL3DView : public COGL3DView {
 protected:  // �������л�����
  CCG2019112380������OGL3DView() noexcept;
  DECLARE_DYNCREATE(CCG2019112380������OGL3DView)

  // ����
 public:
  CCG2019112380������OGL3DDoc* GetDocument() const;
                                                  
  // ����
 public:
  // ��д
 public:
  virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //ͼ�ζ�����ӵ�����
  bool addRenderable(CGRenderable* r);
  bool delRenderable(CGRenderable* r);
 protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    virtual void _3DTranslate(double tx, double ty, double tz);  //ƽ��
  virtual void _3DRotate(double angle,
                         double cx,
                         double cy,
                         double cz);  //��ת����ʱ��Ϊ�����ȣ�
  virtual void _3DScale(double sx, double sy, double sz);  //����
  virtual void Move3DCamera(double tx, double ty);         //Ƶ�ƹ۲촰��
  virtual void Zoom3DCamera(double ratio);  //�����۲촰�ڵ����ű���
  virtual void Rotate3DCamera(double angle);  //ת��������۲�����ϵ)
  virtual void setProjection(int mode);
  int FocalDistance();
  int MaterialSelect();
  virtual void setEyePos(double eyex, double eyey, double eyez);
  //virtual void setfocalDis(int dis); 
  // ʵ��
 public:
  virtual ~CCG2019112380������OGL3DView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:
  // ���ɵ���Ϣӳ�亯��
 protected:
  afx_msg void OnFilePrintPreview();
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  DECLARE_MESSAGE_MAP()
 public:
  //����Ĭ���ӿڲ���
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //��Ⱦ����
  virtual bool RenderScene();
  virtual int threeDStyle();
                                            
 public:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDraw3ddot();
  afx_msg void OnDraw3dlineseg();
  afx_msg void OnDraw3dlinestrip();
  afx_msg void OnDraw3dlineloop();
  afx_msg void OnDraw3dpolygon();
  afx_msg void OnDraw3dtraingle();
  afx_msg void OnDraw3dtraingleFan();
  afx_msg void OnDraw3dquads();
  afx_msg void OnDraw3dtraingleStrip();
  afx_msg void OnDraw3dquadsStrip();
  afx_msg void OnDraw3dsphere();
  afx_msg void OnDraw3drobot();
  afx_msg void On3drobotReset();
  afx_msg void On3drobotLeftarm();
  afx_msg void On3drobotRightarm();
  afx_msg void On3drobotLeftleg();
  afx_msg void On3drobotRightleg();
  afx_msg void On3drobotLeft();
  afx_msg void On3drobotRight();
  afx_msg void On3dtranstaleLeft();
  afx_msg void On3dtranslateRight();
  afx_msg void On3dtranslateUp();
  afx_msg void On3dtranslateDown();
  afx_msg void On3dtranslateBefore();
  afx_msg void On3dtranslateAfter();
  afx_msg void On3drotateXaxi();
  afx_msg void On3dscaleUp();
  afx_msg void On3dscaleDown();
  afx_msg void On3drotateYaxi();
  afx_msg void On3drotateZaxi();
  afx_msg void On3dobserverScaleUp();
  afx_msg void On3dobserverScaleDown();
  afx_msg void OnParalleProjection();
  afx_msg void OnPerspectiveProjection();
  afx_msg void On3dfocalChange();
  afx_msg void On3dmoveViewport();
  afx_msg void OnCreatePointSource();
  afx_msg void On3ddrawTeapot();
  afx_msg void OnCreateParallelSource();
  afx_msg void OnCreateSpotSource();
  virtual void OnActivateView(BOOL bActivate,
                              CView* pActivateView,
                              CView* pDeactiveView);
};

#ifndef _DEBUG  // CG2019112380������OGL3DView.cpp �еĵ��԰汾
inline CCG2019112380������OGL3DDoc* CCG2019112380������OGL3DView::GetDocument()
    const {
  return reinterpret_cast<CCG2019112380������OGL3DDoc*>(m_pDocument);
}
#endif
