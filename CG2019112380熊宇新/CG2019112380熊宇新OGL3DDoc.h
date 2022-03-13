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

// CG2019112380熊宇新OGL3DDoc.h: CCG2019112380熊宇新OGL3DDoc 类的接口
//

#pragma once
#include "CG3DRenderable.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
class CCG2019112380熊宇新OGL3DDoc : public CDocument {
 protected:  // 仅从序列化创建
  CCG2019112380熊宇新OGL3DDoc() noexcept;
  DECLARE_DYNCREATE(CCG2019112380熊宇新OGL3DDoc)
  // 特性
 public:
  //显示场景树用
  COGL3DScene* GetScene() { return &mScene; }

 protected:
  //包含的场景
  COGL3DScene mScene;
  // 操作
 public:
  //设置默认视口参数（假定用于显示图形的只有一个View）
  bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //渲染场景到指定客户区
  bool RenderScene(COGL3DView* pView);
  bool addRenderable(CGRenderable* r);
  bool delRenderable(CGRenderable* r);

 public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);
  int threeDStyle();
  void robotReset();
  void rightArmRotate();
  void leftArmRotate();
  void rightLegRotate();
  void leftLegRotate();
  void bodyLeftRotate();
  void bodyRigRotate();

  void _3DTranslate(double tx, double ty, double tz);  //平移
  void _3DRotate(double angle,
                 double cx,
                 double cy,
                 double cz);  //旋转（逆时针为正，度）
  void _3DScale(double sx, double sy, double sz);  //缩放
  virtual void Move3DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom3DCamera(double ratio);  //给定观察窗口的缩放比例
  virtual void Rotate3DCamera(double angle);  //转动相机（观察坐标系)
  virtual void setProjection(int mode);
  int FocalDistance();
  int MaterialSelect();
  virtual void setEyePos(double eyex, double eyey, double eyez);
  //virtual void setfocalDis(int dis);
  CGRenderable* CCG2019112380熊宇新OGL3DDoc::RenderableSelectedByName(
      const CString& name) {
    mScene.RenderableUnselectAll();  //此处只实现单选
    return mScene.RenderableSelectedByName(name);
  }
#ifdef SHARED_HANDLERS
  virtual void InitializeSearchContent();
  virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  // SHARED_HANDLERS

  // 实现
 public:
  virtual ~CCG2019112380熊宇新OGL3DDoc();
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
  afx_msg void OnUpdateDraw3dmode(CCmdUI* pCmdUI);
  afx_msg void OnDraw3dmode();
  afx_msg void OnUpdate3dfocalDistance(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboTeapotMaterial(CCmdUI* pCmdUI);
};
