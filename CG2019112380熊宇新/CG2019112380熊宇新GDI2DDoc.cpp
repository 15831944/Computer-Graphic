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

// CG2019112380熊宇新GDI2DDoc.cpp: CCG2019112380熊宇新GDI2DDoc 类的实现
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112380熊宇新.h"
#endif

#include <propkey.h>
#include "CG2019112380熊宇新GDI2DDoc.h"
#include "CG2DLineSegment.h"
#include"CGScene.h"
#include"CGCamera.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112380熊宇新GDI2DDoc

IMPLEMENT_DYNCREATE(CCG2019112380熊宇新GDI2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCG2019112380熊宇新GDI2DDoc, CDocument)
ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdatePenWidth)
ON_UPDATE_COMMAND_UI(ID_COMBO_LAYER,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateComboLayer)
ON_COMMAND(ID_ADD_LAYER, &CCG2019112380熊宇新GDI2DDoc::OnAddLayer)
ON_COMMAND(ID_SETUP_LAYER, &CCG2019112380熊宇新GDI2DDoc::OnSetupLayer)
ON_UPDATE_COMMAND_UI(ID_Pen_Color,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdatePenColor)
ON_UPDATE_COMMAND_UI(ID_PEN_STYLE,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdatePenStyle)
ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateBrushColor)
ON_UPDATE_COMMAND_UI(ID_BRUSH_INDEX,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateBrushIndex)
ON_UPDATE_COMMAND_UI(ID_COMBO_LINE_ALGORITHM,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateComboLineAlgorithm)
ON_UPDATE_COMMAND_UI(ID_COMBO_CIRCLE_ALGORITHM,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateComboCircleAlgorithm)
ON_COMMAND(ID_POLYGON_EDGES, &CCG2019112380熊宇新GDI2DDoc::OnPolygonEdges)
ON_UPDATE_COMMAND_UI(ID_POLYGON_EDGES,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdatePolygonEdges)
ON_UPDATE_COMMAND_UI(ID_BOUND_COLOR,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateBoundColor)
ON_UPDATE_COMMAND_UI(ID_BACK_COLOR,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateBackColor)
// ON_UPDATE_COMMAND_UI(ID_DRAW_2DFILL,
//                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateDraw2dfill)
ON_UPDATE_COMMAND_UI(ID_COMBO_FILL_ALGORITHM,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateComboFillAlgorithm)
ON_UPDATE_COMMAND_UI(ID_TRANSFORM_SHEAR_XY_AXIS,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateTransformShearXyAxis)
ON_UPDATE_COMMAND_UI(ID_COMBO_TIME_CHOSE,
                     &CCG2019112380熊宇新GDI2DDoc::OnUpdateComboTimeChose)
END_MESSAGE_MAP()

// CCG2019112380熊宇新GDI2DDoc 构造/析构

CCG2019112380熊宇新GDI2DDoc::CCG2019112380熊宇新GDI2DDoc() noexcept {
  // TODO: 在此添加一次性构造代码
  // mScene.addRenderable(new CG2DLineSegment(Vec2d(100, 100), Vec2d(500,
  // 200)));
}

CCG2019112380熊宇新GDI2DDoc::~CCG2019112380熊宇新GDI2DDoc() {}

BOOL CCG2019112380熊宇新GDI2DDoc::OnNewDocument() {
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: 在此添加重新初始化代码
  // (SDI 文档将重用该文档)

  return TRUE;
}

// CCG2019112380熊宇新GDI2DDoc 序列化

void CCG2019112380熊宇新GDI2DDoc::Serialize(CArchive& ar) {
  mScene.Serialize(ar);
  if (ar.IsStoring()) {
    // TODO: 在此添加存储代码
  } else {
    // TODO: 在此添加加载代码
  }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2019112380熊宇新GDI2DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
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
void CCG2019112380熊宇新GDI2DDoc::InitializeSearchContent() {
  CString strSearchContent;
  // 从文档数据设置搜索内容。
  // 内容部分应由“;”分隔

  // 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
  SetSearchContent(strSearchContent);
}

void CCG2019112380熊宇新GDI2DDoc::SetSearchContent(const CString& value) {
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

// CCG2019112380熊宇新GDI2DDoc 诊断

#ifdef _DEBUG
void CCG2019112380熊宇新GDI2DDoc::AssertValid() const {
  CDocument::AssertValid();
}

void CCG2019112380熊宇新GDI2DDoc::Dump(CDumpContext& dc) const {
  CDocument::Dump(dc);
}
#endif  //_DEBUG

bool CCG2019112380熊宇新GDI2DDoc::setDefaultViewPort(int xl,
                                                     int yb,
                                                     int xr,
                                                     int yt) {
  mScene.setDefaultWindow((double(xl) - xr) / 2.0, (double(yb) - yt) / 2.0,
                          xr / 2.0, yt / 2.0);
  //初次调用时设置(观察坐标系原点在观察窗口中心)
  static bool init = false;
  if (!init) {
    mScene.defaultCamera()->setVCS(0, 0, 0);
    mScene.defaultCamera()->setVCSWindow(
        (double(xl) - xr) / 2.0, (double(yb) - yt) / 2.0, xr / 2.0, yt / 2.0);
    init = true;
  }
  return mScene.setDefaultViewPort(xl, yb, xr, yt);
}
// CCG2019112380熊宇新GDI2DDoc 命令
//渲染场景到指定客户区
bool CCG2019112380熊宇新GDI2DDoc::RenderScene(CGDI2DView* pView) {
  if (pView == nullptr)
    return false;
  return mScene.RenderScene(pView);
}

Vec2d CCG2019112380熊宇新GDI2DDoc::ViewPortToWorld(const Vec2i& p) {
  return mScene.ViewPortToWorld(p);
}

double CCG2019112380熊宇新GDI2DDoc::LengthViewPortToWorld(const double p) {
  return mScene.LengthViewPortToWorld(p);
}
double CCG2019112380熊宇新GDI2DDoc::RadViewPortToWorld(const double p) {
  return mScene.RadViewPortToWorld(p);
}
Vec2i CCG2019112380熊宇新GDI2DDoc::WorldToViewPort(const Vec2d& p) {
  return mScene.WorldToViewPort(p);
}
double CCG2019112380熊宇新GDI2DDoc::LengthWorldToViewPort(const double p) {
  return mScene.LengthWorldToViewPort(p);
}
double CCG2019112380熊宇新GDI2DDoc::RadWorldToViewPort(const double p) {
  return mScene.RadWorldToViewPort(p);
}
CGRenderable* CCG2019112380熊宇新GDI2DDoc::RenderableSelectedByName(
    const CString& name) {
  mScene.RenderableUnselectAll();  //此处只实现单选
  return mScene.RenderableSelectedByName(name);
}

//图层属性
int CCG2019112380熊宇新GDI2DDoc::LayerIndex() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->LayerIndex();
}
//画笔属性
COLORREF CCG2019112380熊宇新GDI2DDoc::PenColor() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return RGB(0, 0, 0);
  return pMainWnd->PenColor();
}
int CCG2019112380熊宇新GDI2DDoc::PenWidth() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 1;
  return pMainWnd->PenWidth();
}
int CCG2019112380熊宇新GDI2DDoc::PenStyle() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return PS_SOLID;
  return pMainWnd->PenStyle();
}
//画刷属性
bool CCG2019112380熊宇新GDI2DDoc::UseBrush() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return false;
  return pMainWnd->UseBrush();
}
COLORREF CCG2019112380熊宇新GDI2DDoc::BrushColor() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return RGB(255, 255, 255);
  return pMainWnd->BrushColor();
}
int CCG2019112380熊宇新GDI2DDoc::BrushIndex() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return -1;
  return pMainWnd->BrushIndex();
}

//画线算法
int CCG2019112380熊宇新GDI2DDoc::LineAlgorithm() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->LineAlgorithm();
}
//圆弧算法
int CCG2019112380熊宇新GDI2DDoc::CircleAlgorithm() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->CircleAlgorithm();
}
//其他场景操作接口，如：
bool CCG2019112380熊宇新GDI2DDoc::addRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable))) {
    return mScene.addRenderable(r);
  }
  return false;
}
bool CCG2019112380熊宇新GDI2DDoc::delRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable))) {
    return mScene.delRenderable(r);
  }
  return false;
}

int CCG2019112380熊宇新GDI2DDoc::RegularEdges() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->RegularEdges();
}
int CCG2019112380熊宇新GDI2DDoc::FillAlgorithm() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->FillAlgorithm();
}
int CCG2019112380熊宇新GDI2DDoc::TimeChose() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->TimeChose();
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdatePenWidth(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateComboLayer(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnAddLayer() {
  // TODO: 在此添加命令处理程序代码
}

void CCG2019112380熊宇新GDI2DDoc::OnSetupLayer() {
  // TODO: 在此添加命令处理程序代码
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdatePenColor(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdatePenStyle(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateBrushColor(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateBrushIndex(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateComboLineAlgorithm(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateComboCircleAlgorithm(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnPolygonEdges() {
  // TODO: 在此添加命令处理程序代码
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdatePolygonEdges(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(false);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateBoundColor(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateBackColor(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

// void CCG2019112380熊宇新GDI2DDoc::OnUpdateDraw2dfill(CCmdUI* pCmdUI) {
//  // TODO: 在此添加命令更新用户界面处理程序代码
//  pCmdUI->Enable(true);
//}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateComboFillAlgorithm(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}

//二维图形对象的几何变换（针对选择集中的对象）
void CCG2019112380熊宇新GDI2DDoc::Translate(double tx, double ty)  //平移
{
  mScene.Translate(tx, ty);
}
void CCG2019112380熊宇新GDI2DDoc::Rotate(double angle,
                                         double cx,
                                         double cy)  //旋转（逆时针为正，度）
{
  mScene.Rotate(angle, cx, cy);
}
void CCG2019112380熊宇新GDI2DDoc::Scale(double sx, double sy)  //缩放
{
  mScene.Scale(sx, sy);
}
void CCG2019112380熊宇新GDI2DDoc::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  mScene.MirrorXAxis();
}
void CCG2019112380熊宇新GDI2DDoc::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  mScene.MirrorYAxis();
}
void CCG2019112380熊宇新GDI2DDoc::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  mScene.MirrorYeqPosX();
}
void CCG2019112380熊宇新GDI2DDoc::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  mScene.MirrorYeNegPX();
}
void CCG2019112380熊宇新GDI2DDoc::MirrorOrigin()  //关于原点对称（二维、三维）
{
  mScene.MirrorOrigin();
}
void CCG2019112380熊宇新GDI2DDoc::ShearXAxis(double shx)  //沿X轴错切
{
  mScene.ShearXAxis(shx);
}
void CCG2019112380熊宇新GDI2DDoc::ShearYAxis(double shy)  //沿Y轴错切
{
  mScene.ShearYAxis(shy);
}
void CCG2019112380熊宇新GDI2DDoc::ShearXYAxis(double shx,
                                              double shy)  //沿X、Y轴错切
{
  mScene.ShearXYAxis(shx, shy);
}
void CCG2019112380熊宇新GDI2DDoc::Transform(
    const Mat3d& mat)  //几何变换（左乘给定矩阵）
{
  mScene.Transform(mat);
}
//测试裁剪用（通过View类调用）;
void CCG2019112380熊宇新GDI2DDoc::Clip(double xl,
                                       double yb,
                                       double xr,
                                       double yt,
                                       CGRenderContext* pRC) {
  mScene.Clip(xl, yb, xr, yt, pRC);
}

  void CCG2019112380熊宇新GDI2DDoc::Move2DCamera(double tx, double ty) {
  mScene.Move2DCamera(tx, ty);
}
//观察窗口左下角、右上角
void CCG2019112380熊宇新GDI2DDoc::Zoom2DCamera(const Vec2d& lb,
                                               const Vec2d& rt) {
  mScene.Zoom2DCamera(lb, rt);
}
//给定观察窗口的缩放比例（
void CCG2019112380熊宇新GDI2DDoc::Zoom2DCamera(double ratio) {
  mScene.Zoom2DCamera(ratio);
}
//现实全部窗口
void CCG2019112380熊宇新GDI2DDoc::Zoom2DCamera() {
  ABox2d box = mScene.ComputeBounds();
  mScene.Zoom2DCamera(box.minCorner(), box.maxCorner());
}
//转动相机（观察坐标系)
void CCG2019112380熊宇新GDI2DDoc::Rotate2DCamera(double angle) {
  mScene.Rotate2DCamera(angle);
}


bool CCG2019112380熊宇新GDI2DDoc::RenderableUnselectByName(
    const CString& name) {
  return mScene.RenderableUnselectByName(name);
}
bool CCG2019112380熊宇新GDI2DDoc::RenderableUnselect(CGRenderable* r) {
  return mScene.RenderableUnselect(r);
}
void CCG2019112380熊宇新GDI2DDoc::RenderableUnselectAll() {
  mScene.RenderableUnselectAll();
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateTransformShearXyAxis(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(false);
}

void CCG2019112380熊宇新GDI2DDoc::OnUpdateComboTimeChose(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->Enable(true);
}
