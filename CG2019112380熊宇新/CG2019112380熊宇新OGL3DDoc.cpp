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

// CG2019112380熊宇新OGL3DDoc.cpp: CCG2019112380熊宇新OGL3DDoc 类的实现
//
   #include "pch.h"
#include "framework.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112380熊宇新.h"
#endif

#include <propkey.h>
#include "CG2019112380熊宇新OGL3DDoc.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112380熊宇新OGL3DDoc

IMPLEMENT_DYNCREATE(CCG2019112380熊宇新OGL3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCG2019112380熊宇新OGL3DDoc, CDocument)
ON_UPDATE_COMMAND_UI(ID_DRAW_3DMODE,
                     &CCG2019112380熊宇新OGL3DDoc::OnUpdateDraw3dmode)
ON_COMMAND(ID_DRAW_3DMODE, &CCG2019112380熊宇新OGL3DDoc::OnDraw3dmode)
ON_UPDATE_COMMAND_UI(ID_3DFOCAL_DISTANCE,
                     &CCG2019112380熊宇新OGL3DDoc::OnUpdate3dfocalDistance)
ON_UPDATE_COMMAND_UI(ID_COMBO_TEAPOT_MATERIAL,
                     &CCG2019112380熊宇新OGL3DDoc::OnUpdateComboTeapotMaterial)
END_MESSAGE_MAP()

// CCG2019112380熊宇新OGL3DDoc 构造/析构

CCG2019112380熊宇新OGL3DDoc::CCG2019112380熊宇新OGL3DDoc() noexcept {
  // TODO: 在此添加一次性构造代码
}

CCG2019112380熊宇新OGL3DDoc::~CCG2019112380熊宇新OGL3DDoc() {}

BOOL CCG2019112380熊宇新OGL3DDoc::OnNewDocument() {
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: 在此添加重新初始化代码
  // (SDI 文档将重用该文档)

  return TRUE;
}

// CCG2019112380熊宇新OGL3DDoc 序列化

void CCG2019112380熊宇新OGL3DDoc::Serialize(CArchive& ar) {
  if (ar.IsStoring()) {
    // TODO: 在此添加存储代码
  } else {
    // TODO: 在此添加加载代码
  }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2019112380熊宇新OGL3DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
  // 修改此代码以绘制文档数据
  dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

  CString strText = _T("TODO: implement thumbnail drawing here");
  LOGFONT lf;

  CFont* pDefaultGUIFont =
      CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
  pDefaultGUIFont->GetLogFont(&lf);
  lf.lfHeight = 36;

  CFont fontDraw;
  fontDraw.CreateFontIndirect(&lf);

  CFont* pOldFont = dc.SelectObject(&fontDraw);
  dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
  dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2019112380熊宇新OGL3DDoc::InitializeSearchContent() {
  CString strSearchContent;
  // 从文档数据设置搜索内容。
  // 内容部分应由“;”分隔

  // 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
  SetSearchContent(strSearchContent);
}

void CCG2019112380熊宇新OGL3DDoc::SetSearchContent(const CString& value) {
  if (value.IsEmpty()) {
    RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
  } else {
    CMFCFilterChunkValueImpl* pChunk = nullptr;
    ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
    if (pChunk != nullptr) {
      pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
      SetChunkValue(pChunk);
    }
  }
}

#endif  // SHARED_HANDLERS

// CCG2019112380熊宇新OGL3DDoc 诊断

#ifdef _DEBUG
void CCG2019112380熊宇新OGL3DDoc::AssertValid() const {
  CDocument::AssertValid();
}

void CCG2019112380熊宇新OGL3DDoc::Dump(CDumpContext& dc) const {
  CDocument::Dump(dc);
}
#endif  //_DEBUG

// CCG2019112380熊宇新OGL3DDoc 命令

//设置默认视口参数
bool CCG2019112380熊宇新OGL3DDoc::setDefaultViewPort(int xl,
                                                     int yb,
                                                     int xr,
                                                     int yt) {
  return mScene.setDefaultViewPort(xl, yb, xr, yt);
}
//渲染场景到指定客户区（的视口）
bool CCG2019112380熊宇新OGL3DDoc::RenderScene(COGL3DView* pView) {
  if (pView == nullptr)
    return false;
  return mScene.RenderScene(pView);
}

bool CCG2019112380熊宇新OGL3DDoc::addRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable))) {
    return mScene.addRenderable(r);
  }
  return false;
}
bool CCG2019112380熊宇新OGL3DDoc::delRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable))) {
    return mScene.delRenderable(r);
  }
  return false;
}
int CCG2019112380熊宇新OGL3DDoc::threeDStyle() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->threeDStyle();
}

void CCG2019112380熊宇新OGL3DDoc::OnUpdateDraw3dmode(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新OGL3DDoc::OnDraw3dmode() {
  // TODO: 在此添加命令处理程序代码
}

void CCG2019112380熊宇新OGL3DDoc::robotReset() {
  return mScene.robotReset();
}
void CCG2019112380熊宇新OGL3DDoc::rightArmRotate() {
  return mScene.rightArmRotate();
}
void CCG2019112380熊宇新OGL3DDoc::leftArmRotate() {
  return mScene.leftArmRotate();
}
void CCG2019112380熊宇新OGL3DDoc::rightLegRotate() {
  return mScene.rightLegRotate();
}
void CCG2019112380熊宇新OGL3DDoc::leftLegRotate() {
  return mScene.leftLegRotate();
}
void CCG2019112380熊宇新OGL3DDoc::bodyLeftRotate() {
  return mScene.bodyLeftRotate();
}
void CCG2019112380熊宇新OGL3DDoc::bodyRigRotate() {
  return mScene.bodyRigRotate();
}
void CCG2019112380熊宇新OGL3DDoc::_3DTranslate(double tx,
                                               double ty,
                                               double tz)  //平移
{
  return mScene._3DTranslate(tx, ty, tz);
}
void CCG2019112380熊宇新OGL3DDoc::_3DRotate(double angle,
                                            double cx,
                                            double cy,
                                            double cz)  //旋转（逆时针为正，度）
{
  return mScene._3DRotate(angle,cx, cy, cz);
}
void CCG2019112380熊宇新OGL3DDoc::_3DScale(double sx,
                                           double sy,
                                           double sz)  //缩放
{
  return mScene._3DScale(sx, sy, sz);
}
void CCG2019112380熊宇新OGL3DDoc:: Move3DCamera(double tx,
                                                  double ty)  //频移观察窗口
{}
void CCG2019112380熊宇新OGL3DDoc:: Zoom3DCamera(
                                         double ratio)  //给定观察窗口的缩放比例
{
  return mScene.Zoom3DCamera(ratio);
}
void CCG2019112380熊宇新OGL3DDoc::Rotate3DCamera(
    double angle)  //转动相机（观察坐标系)
{}
void CCG2019112380熊宇新OGL3DDoc::setProjection(int mode) {
  return mScene.setProjection(mode);
}

void CCG2019112380熊宇新OGL3DDoc::OnUpdate3dfocalDistance(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}
int CCG2019112380熊宇新OGL3DDoc::FocalDistance() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->FocalDistance();
}
int CCG2019112380熊宇新OGL3DDoc::MaterialSelect() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->MaterialSelect();
}
    //void CCG2019112380熊宇新OGL3DDoc::setfocalDis(int dis) {
//  return mScene.setfocalDis(dis);
//}

void CCG2019112380熊宇新OGL3DDoc::setEyePos(double eyex,
    double eyey,
    double eyez) {
  return mScene.setEyePos(eyex, eyey, eyez);
}

void CCG2019112380熊宇新OGL3DDoc::OnUpdateComboTeapotMaterial(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}
