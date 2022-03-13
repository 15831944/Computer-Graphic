// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2019112380熊宇新OGL3DView.h: CCG2019112380熊宇新OGL3DView 类的接口
//

#pragma once

class CCG2019112380熊宇新OGL3DView : public COGL3DView {
 protected:  // 仅从序列化创建
  CCG2019112380熊宇新OGL3DView() noexcept;
  DECLARE_DYNCREATE(CCG2019112380熊宇新OGL3DView)

  // 特性
 public:
  CCG2019112380熊宇新OGL3DDoc* GetDocument() const;
                                                  
  // 操作
 public:
  // 重写
 public:
  virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //图形对象添加到场景
  bool addRenderable(CGRenderable* r);
  bool delRenderable(CGRenderable* r);
 protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

    virtual void _3DTranslate(double tx, double ty, double tz);  //平移
  virtual void _3DRotate(double angle,
                         double cx,
                         double cy,
                         double cz);  //旋转（逆时针为正，度）
  virtual void _3DScale(double sx, double sy, double sz);  //缩放
  virtual void Move3DCamera(double tx, double ty);         //频移观察窗口
  virtual void Zoom3DCamera(double ratio);  //给定观察窗口的缩放比例
  virtual void Rotate3DCamera(double angle);  //转动相机（观察坐标系)
  virtual void setProjection(int mode);
  int FocalDistance();
  int MaterialSelect();
  virtual void setEyePos(double eyex, double eyey, double eyez);
  //virtual void setfocalDis(int dis); 
  // 实现
 public:
  virtual ~CCG2019112380熊宇新OGL3DView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:
  // 生成的消息映射函数
 protected:
  afx_msg void OnFilePrintPreview();
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  DECLARE_MESSAGE_MAP()
 public:
  //设置默认视口参数
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //渲染场景
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

#ifndef _DEBUG  // CG2019112380熊宇新OGL3DView.cpp 中的调试版本
inline CCG2019112380熊宇新OGL3DDoc* CCG2019112380熊宇新OGL3DView::GetDocument()
    const {
  return reinterpret_cast<CCG2019112380熊宇新OGL3DDoc*>(m_pDocument);
}
#endif
