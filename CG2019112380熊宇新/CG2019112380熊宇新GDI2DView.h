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

// CG2019112380熊宇新GDI2DView.h: CCG2019112380熊宇新GDI2DView 类的接口
//

#pragma once

#include "CGDI2DView.h"
#include "MainFrame.h"
class CCG2019112380熊宇新GDI2DView : public CGDI2DView {
 protected:  // 仅从序列化创建                 
  CCG2019112380熊宇新GDI2DView() noexcept;
  DECLARE_DYNCREATE(CCG2019112380熊宇新GDI2DView)

  // 特性
 public:
  CCG2019112380熊宇新GDI2DDoc* GetDocument() const;
  void DrawGraphics(CDC* pDC);

  // 操作
 public:
  //设置默认视口参数
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //渲染场景
  virtual bool RenderScene();

  // 重写
 public:
  virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  
  virtual void Prompt(const CString& str);

  //基类虚函数的重写，实现交互绘图中便捷访问
  //通过调用Doc类对应函数实现
  virtual int LayerIndex();
  virtual COLORREF PenColor();
  virtual int PenWidth();
  virtual int PenStyle();
  virtual bool UseBrush();
  virtual COLORREF BrushColor();
  virtual int BrushIndex();
  virtual int LineAlgorithm();
  virtual int CircleAlgorithm();
  virtual int TimeChose();

  //其他场景操作接口，如：
  bool addRenderable(CGRenderable* r);
  bool delRenderable(CGRenderable* r);

    //填充算法
  int FillAlgorithm() const;
  //正多边形边数
  int RegularEdges() const;
  //是否勾选正多边形
  bool RegularPolygon() const;
  //边界颜色
  COLORREF BoundColor() const;                    
  // 内点颜色
  COLORREF FloodColor() const;
  //二维图形对象的几何变换（针对选择集中的对象）
  virtual void Translate(double tx, double ty);  //平移
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //旋转（逆时针为正，度）
  virtual void Scale(double sx, double sy);  //缩放
  virtual void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切

  //测试裁剪用（通过通过交互命令类调用，针对选择集中的对象）;
  virtual void Clip(double xl, double yb, double xr, double yt);

  //根据视口坐标获取对应场景坐标（二维)-调用场景类的ViewPortToWorld
  virtual Vec2d ViewPortToWorld(const Vec2i& p);
  virtual double LengthViewPortToWorld(const double p);
  virtual double RadViewPortToWorld(const double p);
  virtual Vec2i WorldToViewPort(const Vec2d& p);
  virtual double LengthWorldToViewPort(const double p);
  virtual double RadWorldToViewPort(const double p);

  // 观察（二维）（注意在实现中要保持与视口高宽比一致）
  virtual void Move2DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom2DCamera(const Vec2d& lb, const Vec2d& rt);  //观察窗口左下角、右上角
  virtual void Zoom2DCamera(double ratio);  //给定观察窗口的缩放比例
  virtual void Rotate2DCamera(double angle);  //转动相机（观察坐标系)

 protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  // 实现
 public:
  virtual ~CCG2019112380熊宇新GDI2DView();
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
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

  afx_msg void OnCdcDraw();
  afx_msg void OnDraw2dlineseg();
  afx_msg void OnUpdateDraw2dlineseg(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dlineTime();
  afx_msg void OnUpdateDraw2dlineTime(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dline();
  afx_msg void OnUpdateDraw2dline(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dray();
  afx_msg void OnUpdateDraw2dray(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dlinePloy();
  afx_msg void OnUpdateDraw2dlinePloy(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircleCenterRadius();
  afx_msg void OnUpdateDraw2dcircleCenterRadius(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircleDiameter();
  afx_msg void OnUpdateDraw2dcircleDiameter(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircle2psemi();
  afx_msg void OnUpdateDraw2dcircle2psemi(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircle3point();
  afx_msg void OnUpdateDraw2dcircle3point(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircle3pointarc();
  afx_msg void OnUpdateDraw2dcircle3pointarc(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircle3pointfan();
  afx_msg void OnUpdateDraw2dcircle3pointfan(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircleOjarc();
  afx_msg void OnUpdateDraw2dcircleOjarc(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dcircleOjfan();
  afx_msg void OnUpdateDraw2dcircleOjfan(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dellipse();
  afx_msg void OnUpdateDraw2dellipse(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dellipseArc();
  afx_msg void OnUpdateDraw2dellipseArc(CCmdUI* pCmdUI);
  afx_msg void OnCommandNone();
  afx_msg void OnUpdateCommandNone(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dpolygon();
  afx_msg void OnUpdateDraw2dpolygon(CCmdUI* pCmdUI);
  afx_msg void OnDraw2dfill();
  afx_msg void OnUpdateDraw2dfill(CCmdUI* pCmdUI);
  virtual void OnActivateView(BOOL bActivate,
                              CView* pActivateView,
                              CView* pDeactiveView);
  afx_msg void OnSelectUn();
  afx_msg void OnTransformTranslateLeft();
  afx_msg void OnTransformTranslateRight();
  afx_msg void OnTransformTranslateUp();
  afx_msg void OnTransformTranslateDown();
  afx_msg void OnTransformMirrorXAxis();
  afx_msg void OnTransformMirrorYAxis();
  afx_msg void OnTransformMirrorOrigin();
  afx_msg void OnTransformMirrorYEquX();
  afx_msg void OnTransformMirrorYEquNeX();
  afx_msg void OnTransformZoomIn();
  afx_msg void OnTransformZoomOut();
  afx_msg void OnTransformTranslate();
  afx_msg void OnUpdateTransformTranslate(CCmdUI* pCmdUI);
  afx_msg void OnTransformRotateOrigin();
  afx_msg void OnUpdateTransformRotateOrigin(CCmdUI* pCmdUI);
  afx_msg void OnCutCode();
  afx_msg void OnUpdateCutCode(CCmdUI* pCmdUI);
  afx_msg void OnObserveScaleUp();
  afx_msg void OnObserveScaleDown();
  afx_msg void OnObserveMoveViewpoint();
  afx_msg void OnUpdateObserveMoveViewpoint(CCmdUI* pCmdUI);
  afx_msg void OnObserveRotateAngle();
  afx_msg void OnUpdateObserveRotateAngle(CCmdUI* pCmdUI);
  afx_msg void OnTransformShearX();
  afx_msg void OnTransformShearYAxis();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnClock();
  afx_msg void OnUpdateClock(CCmdUI* pCmdUI);
};


#ifndef _DEBUG  // CG2019112380熊宇新GDI2DView.cpp 中的调试版本
inline CCG2019112380熊宇新GDI2DDoc* CCG2019112380熊宇新GDI2DView::GetDocument()
    const {
  return reinterpret_cast<CCG2019112380熊宇新GDI2DDoc*>(m_pDocument);
}
#endif
