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

// CG2019112380熊宇新GDI2DDoc.h: CCG2019112380熊宇新GDI2DDoc 类的接口
//

#pragma once

#include "CGDI2DScene.h"
#include "CGDI2DView.h"
class CCG2019112380熊宇新GDI2DDoc : public CDocument {
 protected:  // 仅从序列化创建
  CCG2019112380熊宇新GDI2DDoc() noexcept;
  DECLARE_DYNCREATE(CCG2019112380熊宇新GDI2DDoc)

  CGDI2DScene mScene;
  // 特性
 public:
  CGDI2DScene* GetScene() { return &mScene; }

  // 设置默认视口参数（假定用于显示图形的只有一个View）
  bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //渲染场景到指定客户区
  bool RenderScene(CGDI2DView* pView);

  int LayerIndex();
  COLORREF PenColor();
  int PenWidth();
  int PenStyle();
  bool UseBrush();
  COLORREF BrushColor();
  int BrushIndex();

  int LineAlgorithm();
  int CircleAlgorithm();
  //填充算法
  int FillAlgorithm();
  int TimeChose();
  //正多边形边数
  int RegularEdges();
  //其他场景操作接口，如：
  bool addRenderable(CGRenderable* r);
  bool delRenderable(CGRenderable* r);
  bool RenderableUnselectByName(const CString& name);
  bool RenderableUnselect(CGRenderable* r);
  void RenderableUnselectAll();
  // 操作
 public:
  // 重写
 public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

  CGRenderable* RenderableSelectedByName(const CString& name);
  //二维图形对象的几何变换（针对选择集中的对象）
  void Translate(double tx, double ty);             //平移
  void Rotate(double angle, double cx, double cy);  //旋转（逆时针为正，度）
  void Scale(double sx, double sy);                 //缩放
  void MirrorXAxis();           //关于X轴对称（二维、三维）
  void MirrorYAxis();           //关于Y轴对称（二维、三维）
  void MirrorYeqPosX();         //关于y=x对称（二维、三维）
  void MirrorYeNegPX();         //关于y=-x对称（二维、三维）
  void MirrorOrigin();          //关于原点对称（二维、三维）
  void ShearXAxis(double shx);  //沿X轴错切
  void ShearYAxis(double shy);  //沿Y轴错切
  void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切
  void Transform(const Mat3d& mat);  //几何变换（左乘给定矩阵）



  //观察（二维）（注意保持与视口高宽比一致）
  void Move2DCamera(double tx, double ty);              //频移观察窗口
  void Zoom2DCamera(const Vec2d& lb, const Vec2d& rt);  //观察窗口左下角、右上角
  void Zoom2DCamera(double ratio);    //给定观察窗口的缩放比例（）
  void Zoom2DCamera();                //显示全部场景
  void Rotate2DCamera(double angle);  //转动相机（观察坐标系）

  	Vec2d ViewPortToWorld(const Vec2i& p);
  double LengthViewPortToWorld(const double p);
  double RadViewPortToWorld(const double p);
  Vec2i WorldToViewPort(const Vec2d& p);
  double LengthWorldToViewPort(const double p);
  double RadWorldToViewPort(const double p);
  //测试裁剪用（通过View类调用）;
  void Clip(double xl, double yb, double xr, double yt, CGRenderContext* pRC);
#ifdef SHARED_HANDLERS
  virtual void InitializeSearchContent();
  virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  // SHARED_HANDLERS

  // 实现
 public:
  virtual ~CCG2019112380熊宇新GDI2DDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:
  // 生成的消息映射函数
 protected:
  DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
  // 用于为搜索处理程序设置搜索内容的 Helper 函数
  void SetSearchContent(const CString& value);
#endif  // SHARED_HANDLERS
 public:
  afx_msg void OnUpdateComboLayer(CCmdUI* pCmdUI);
  afx_msg void OnAddLayer();
  afx_msg void OnSetupLayer();
  afx_msg void OnUpdatePenWidth(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePenColor(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePenStyle(CCmdUI* pCmdUI);
  afx_msg void OnUpdateBrushColor(CCmdUI* pCmdUI);
  afx_msg void OnUpdateBrushIndex(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboLineAlgorithm(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboCircleAlgorithm(CCmdUI* pCmdUI);

  afx_msg void OnPolygonEdges();
  afx_msg void OnUpdatePolygonEdges(CCmdUI* pCmdUI);
  afx_msg void OnUpdateBoundColor(CCmdUI* pCmdUI);
  afx_msg void OnUpdateBackColor(CCmdUI* pCmdUI);
  //afx_msg void OnUpdateDraw2dfill(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboFillAlgorithm(CCmdUI* pCmdUI);
  afx_msg void OnUpdateTransformShearXyAxis(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboTimeChose(CCmdUI* pCmdUI);
};
