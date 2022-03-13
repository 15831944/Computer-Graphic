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

// CG2019112380熊宇新OGL3DView.cpp: CCG2019112380熊宇新OGL3DView 类的实现
//

#include "pch.h"
#include "framework.h"


// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112380熊宇新.h"
#endif

#include "CG2019112380熊宇新OGL3DDoc.h"
#include "CG2019112380熊宇新OGL3DView.h"
#include "CG3DLineSegment.h"
#include "CG3DPoint.h"
#include "CG3DPolygon.h"
#include "CG3DQuads.h"
#include "CG3DRobot.h"
#include "CG3DTraingles.h"
#include "COGLDrawLinesegDlg.h"
#include "COGLDrawPointDlg.h"
#include "MainFrame.h"
#include"COGLViewPortPos.h"
#include "CG3DSphere.h"
#include "COGLDrawSphereDlg.h"
#include"CG3DLightSource.h"
#include"COGLCreateLightDlg.h"
 #include"CG3DTeapot.h"
#include"COGLCreateSpotDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112380熊宇新OGL3DView

IMPLEMENT_DYNCREATE(CCG2019112380熊宇新OGL3DView, COGL3DView)

BEGIN_MESSAGE_MAP(CCG2019112380熊宇新OGL3DView, COGL3DView)
// 标准打印命令
ON_COMMAND(ID_FILE_PRINT, &COGL3DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &COGL3DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW,
           &CCG2019112380熊宇新OGL3DView::OnFilePrintPreview)
ON_WM_CONTEXTMENU()
ON_WM_RBUTTONUP()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
ON_COMMAND(ID_DRAW_3DDOT, &CCG2019112380熊宇新OGL3DView::OnDraw3ddot)
ON_COMMAND(ID_DRAW_3DLINESEG, &CCG2019112380熊宇新OGL3DView::OnDraw3dlineseg)
ON_COMMAND(ID_DRAW_3DLINESTRIP,
           &CCG2019112380熊宇新OGL3DView::OnDraw3dlinestrip)
ON_COMMAND(ID_DRAW_3DLINELOOP, &CCG2019112380熊宇新OGL3DView::OnDraw3dlineloop)
ON_COMMAND(ID_DRAW_3DPOLYGON, &CCG2019112380熊宇新OGL3DView::OnDraw3dpolygon)
ON_COMMAND(ID_DRAW_3DTRAINGLE, &CCG2019112380熊宇新OGL3DView::OnDraw3dtraingle)
ON_COMMAND(ID_DRAW_3DTRAINGLE_FAN,
           &CCG2019112380熊宇新OGL3DView::OnDraw3dtraingleFan)
ON_COMMAND(ID_DRAW_3DQUADS, &CCG2019112380熊宇新OGL3DView::OnDraw3dquads)
ON_COMMAND(ID_DRAW_3DTRAINGLE_STRIP,
           &CCG2019112380熊宇新OGL3DView::OnDraw3dtraingleStrip)
ON_COMMAND(ID_DRAW_3DQUADS_STRIP,
           &CCG2019112380熊宇新OGL3DView::OnDraw3dquadsStrip)
ON_COMMAND(ID_DRAW_3DSPHERE, &CCG2019112380熊宇新OGL3DView::OnDraw3dsphere)
ON_COMMAND(ID_DRAW_3DROBOT, &CCG2019112380熊宇新OGL3DView::OnDraw3drobot)
ON_COMMAND(ID_3DROBOT_RESET, &CCG2019112380熊宇新OGL3DView::On3drobotReset)
ON_COMMAND(ID_3DROBOT_LEFTARM, &CCG2019112380熊宇新OGL3DView::On3drobotLeftarm)
ON_COMMAND(ID_3DROBOT_RIGHTARM,
           &CCG2019112380熊宇新OGL3DView::On3drobotRightarm)
ON_COMMAND(ID_3DROBOT_LEFTLEG, &CCG2019112380熊宇新OGL3DView::On3drobotLeftleg)
ON_COMMAND(ID_3DROBOT_RIGHTLEG,
           &CCG2019112380熊宇新OGL3DView::On3drobotRightleg)
ON_COMMAND(ID_3DROBOT_LEFT, &CCG2019112380熊宇新OGL3DView::On3drobotLeft)
ON_COMMAND(ID_3DROBOT_RIGHT, &CCG2019112380熊宇新OGL3DView::On3drobotRight)

ON_COMMAND(ID_3DTRANSTALE_LEFT,
           &CCG2019112380熊宇新OGL3DView::On3dtranstaleLeft)
ON_COMMAND(ID_3DTRANSLATE_RIGHT,
           &CCG2019112380熊宇新OGL3DView::On3dtranslateRight)
ON_COMMAND(ID_3DTRANSLATE_UP, &CCG2019112380熊宇新OGL3DView::On3dtranslateUp)
ON_COMMAND(ID_3DTRANSLATE_DOWN,
           &CCG2019112380熊宇新OGL3DView::On3dtranslateDown)
ON_COMMAND(ID_3DTRANSLATE_BEFORE,
           &CCG2019112380熊宇新OGL3DView::On3dtranslateBefore)
ON_COMMAND(ID_3DTRANSLATE_AFTER,
           &CCG2019112380熊宇新OGL3DView::On3dtranslateAfter)
ON_COMMAND(ID_3DROTATE_XAXI, &CCG2019112380熊宇新OGL3DView::On3drotateXaxi)
ON_COMMAND(ID_3DSCALE_UP, &CCG2019112380熊宇新OGL3DView::On3dscaleUp)
ON_COMMAND(ID_3DSCALE_DOWN, &CCG2019112380熊宇新OGL3DView::On3dscaleDown)
ON_COMMAND(ID_3DROTATE_YAXI, &CCG2019112380熊宇新OGL3DView::On3drotateYaxi)
ON_COMMAND(ID_3DROTATE_ZAXI, &CCG2019112380熊宇新OGL3DView::On3drotateZaxi)
ON_COMMAND(ID_3DOBSERVER_SCALE_UP,
           &CCG2019112380熊宇新OGL3DView::On3dobserverScaleUp)
ON_COMMAND(ID_3DOBSERVER_SCALE_DOWN,
           &CCG2019112380熊宇新OGL3DView::On3dobserverScaleDown)
ON_COMMAND(ID_PARALLE_PROJECTION,
           &CCG2019112380熊宇新OGL3DView::OnParalleProjection)
ON_COMMAND(ID_PERSPECTIVE_PROJECTION,
           &CCG2019112380熊宇新OGL3DView::OnPerspectiveProjection)
ON_COMMAND(ID_3DFOCAL_CHANGE, &CCG2019112380熊宇新OGL3DView::On3dfocalChange)
ON_COMMAND(ID_3DMOVE_VIEWPORT, &CCG2019112380熊宇新OGL3DView::On3dmoveViewport)
ON_COMMAND(ID_CREATE_POINT_SOURCE,
           &CCG2019112380熊宇新OGL3DView::OnCreatePointSource)
ON_COMMAND(ID_3DDRAW_TEAPOT, &CCG2019112380熊宇新OGL3DView::On3ddrawTeapot)
ON_COMMAND(ID_CREATE_PARALLEL_SOURCE,
           &CCG2019112380熊宇新OGL3DView::OnCreateParallelSource)
ON_COMMAND(ID_CREATE_SPOT_SOURCE,
           &CCG2019112380熊宇新OGL3DView::OnCreateSpotSource)
END_MESSAGE_MAP()

// CCG2019112380熊宇新OGL3DView 构造/析构

CCG2019112380熊宇新OGL3DView::CCG2019112380熊宇新OGL3DView() noexcept {
  // TODO: 在此处添加构造代码
}

CCG2019112380熊宇新OGL3DView::~CCG2019112380熊宇新OGL3DView() {}

BOOL CCG2019112380熊宇新OGL3DView::PreCreateWindow(CREATESTRUCT& cs) {
  // TODO: 在此处通过修改
  //  CREATESTRUCT cs 来修改窗口类或样式

  return COGL3DView::PreCreateWindow(cs);
}

// CCG2019112380熊宇新OGL3DView 绘图

void CCG2019112380熊宇新OGL3DView::OnDraw(CDC* /*pDC*/) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;

  // TODO: 在此处为本机数据添加绘制代码
  RenderScene();
}

// CCG2019112380熊宇新OGL3DView 打印

void CCG2019112380熊宇新OGL3DView::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
  AFXPrintPreview(this);
#endif
}

BOOL CCG2019112380熊宇新OGL3DView::OnPreparePrinting(CPrintInfo* pInfo) {
  // 默认准备
  return DoPreparePrinting(pInfo);
}

void CCG2019112380熊宇新OGL3DView::OnBeginPrinting(CDC* /*pDC*/,
                                                   CPrintInfo* /*pInfo*/) {
  // TODO: 添加额外的打印前进行的初始化过程
}

void CCG2019112380熊宇新OGL3DView::OnEndPrinting(CDC* /*pDC*/,
                                                 CPrintInfo* /*pInfo*/) {
  // TODO: 添加打印后进行的清理过程
}

void CCG2019112380熊宇新OGL3DView::OnRButtonUp(UINT /* nFlags */,
                                               CPoint point) {
  ClientToScreen(&point);
  OnContextMenu(this, point);
}

void CCG2019112380熊宇新OGL3DView::OnContextMenu(CWnd* /* pWnd */,
                                                 CPoint point) {
#ifndef SHARED_HANDLERS
  theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x,
                                                point.y, this, TRUE);
#endif
}

// CCG2019112380熊宇新OGL3DView 诊断

#ifdef _DEBUG
void CCG2019112380熊宇新OGL3DView::AssertValid() const {
  COGL3DView::AssertValid();
}

void CCG2019112380熊宇新OGL3DView::Dump(CDumpContext& dc) const {
  COGL3DView::Dump(dc);
}

CCG2019112380熊宇新OGL3DDoc* CCG2019112380熊宇新OGL3DView::GetDocument()
    const  // 非调试版本是内联的
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112380熊宇新OGL3DDoc)));
  return (CCG2019112380熊宇新OGL3DDoc*)m_pDocument;
}
#endif  //_DEBUG

// CCG2019112380熊宇新OGL3DView 消息处理程序

//设置默认视口参数
bool CCG2019112380熊宇新OGL3DView::setDefaultViewPort(int xl,
                                                      int yb,
                                                      int xr,
                                                      int yt) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->setDefaultViewPort(xl, yb, xr, yt);
}

//渲染场景
bool CCG2019112380熊宇新OGL3DView::RenderScene() {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->RenderScene(this);
}

int CCG2019112380熊宇新OGL3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (COGL3DView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  在此添加您专用的创建代码

  return 0;
}

int CCG2019112380熊宇新OGL3DView::threeDStyle() {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT(pDoc);
  if (!pDoc) {
    return 0;
  }
  return pDoc->threeDStyle();
}

void CCG2019112380熊宇新OGL3DView::OnDestroy() {
  COGL3DView::OnDestroy();

  // TODO: 在此处添加消息处理程序代码
}

BOOL CCG2019112380熊宇新OGL3DView::OnEraseBkgnd(CDC* pDC) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  return COGL3DView::OnEraseBkgnd(pDC);
}

void CCG2019112380熊宇新OGL3DView::OnSize(UINT nType, int cx, int cy) {
  COGL3DView::OnSize(nType, cx, cy);

  // TODO: 在此处添加消息处理程序代码
  setDefaultViewPort(0, 0, cx, cy);
}
bool CCG2019112380熊宇新OGL3DView::addRenderable(CGRenderable* r) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  bool ret = pDoc->addRenderable(r);
  if (ret) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if (pMainWnd && pMainWnd->MDIGetActive()->GetActiveView() == this)
      pMainWnd->FillClassView();
  }
  return ret;
}
bool CCG2019112380熊宇新OGL3DView::delRenderable(CGRenderable* r) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  bool ret = pDoc->delRenderable(r);
  if (ret) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if (pMainWnd && pMainWnd->MDIGetActive()->GetActiveView() == this)
      pMainWnd->FillClassView();
  }
  return ret;
}

//点
void CCG2019112380熊宇新OGL3DView::OnDraw3ddot() {
  // TODO: 在此添加命令处理程序代码
  COGLDrawPointDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d v(dlg.x, dlg.y, dlg.z);
  addRenderable(new CG3DPoint(v));
  Invalidate();
  UpdateData();
}

//线段
void CCG2019112380熊宇新OGL3DView::OnDraw3dlineseg() {
  // TODO: 在此添加命令处理程序代码
  COGLDrawLinesegDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d v1(dlg.x1, dlg.y1, dlg.z1);
  Vec3d v2(dlg.x2, dlg.y2, dlg.z2);
  addRenderable(new CG3DLineSegment(v1, v2));
  Invalidate();
  UpdateData();
}

//不闭合线折线
void CCG2019112380熊宇新OGL3DView::OnDraw3dlinestrip() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(200, 100, 0));
  arr.push_back(Vec3d(250, 140, 0));
  arr.push_back(Vec3d(300, 110, 0));
  arr.push_back(Vec3d(350, 200, 0));
  arr.push_back(Vec3d(400, 180, 0));
  arr.push_back(Vec3d(450, 250, 0));
  addRenderable(new CG3DPolygon(arr, 0));
  Invalidate();
  UpdateData();
}

//闭合折线
void CCG2019112380熊宇新OGL3DView::OnDraw3dlineloop() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(300, -150, 0));
  arr.push_back(Vec3d(230, -150, 0));
  arr.push_back(Vec3d(300, -50, 0));
  arr.push_back(Vec3d(230, -50, 0));
  addRenderable(new CG3DPolygon(arr, 1));
  Invalidate();
  UpdateData();
}

//多边形
void CCG2019112380熊宇新OGL3DView::OnDraw3dpolygon() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(60, -100, 0));
  arr.push_back(Vec3d(80, -150, 0));
  arr.push_back(Vec3d(100, -100, 0));
  arr.push_back(Vec3d(140, -100, 0));
  arr.push_back(Vec3d(160, -60, 0));
  arr.push_back(Vec3d(100, -60, 0));
  arr.push_back(Vec3d(80, -10, 0));
  arr.push_back(Vec3d(60, -60, 0));
  addRenderable(new CG3DPolygon(arr, 2));
  Invalidate();
  UpdateData();
}

//三角形  mode==0
void CCG2019112380熊宇新OGL3DView::OnDraw3dtraingle() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(0, 50, 0));
  arr.push_back(Vec3d(-50, -50, 0));
  arr.push_back(Vec3d(50, -50, 0));
  addRenderable(new CG3DTraingles(arr, 0));
  Invalidate();
  UpdateData();
}

//三角扇 mode==1
void CCG2019112380熊宇新OGL3DView::OnDraw3dtraingleFan() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(-100, 0, 0));
  arr.push_back(Vec3d(-100, 60, 0));
  arr.push_back(Vec3d(-145, 45, 0));
  arr.push_back(Vec3d(-160, 0, 0));
  arr.push_back(Vec3d(-145, -45, 0));
  arr.push_back(Vec3d(-100, -60, 0));
  addRenderable(new CG3DTraingles(arr, 1));
  Invalidate();
  UpdateData();
}

//三角条带 mode==2
void CCG2019112380熊宇新OGL3DView::OnDraw3dtraingleStrip() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(-200, -60, 0));
  arr.push_back(Vec3d(-170, -100, 0));
  arr.push_back(Vec3d(-150, -70, 0));
  arr.push_back(Vec3d(-110, -120, 0));
  arr.push_back(Vec3d(-80, -70, 0));
  addRenderable(new CG3DTraingles(arr, 2));
  Invalidate();
  UpdateData();
}

//四边形 mode==0
void CCG2019112380熊宇新OGL3DView::OnDraw3dquads() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(100, 100, 0));
  arr.push_back(Vec3d(200, 100, 0));
  arr.push_back(Vec3d(250, 200, 100));
  arr.push_back(Vec3d(150, 200, 100));
  addRenderable(new CG3DQuads(arr, 0));
  Invalidate();
  UpdateData();
}

//四边形条带 mode==1
void CCG2019112380熊宇新OGL3DView::OnDraw3dquadsStrip() {
  // TODO: 在此添加命令处理程序代码
  Vec3dArray arr;
  arr.push_back(Vec3d(-50, 100, 0));
  arr.push_back(Vec3d(-60, 200, 0));
  arr.push_back(Vec3d(-100, 130, 100));
  arr.push_back(Vec3d(-120, 230, 100));
  arr.push_back(Vec3d(-170, 100, 0));
  arr.push_back(Vec3d(-200, 180, 0));
  addRenderable(new CG3DQuads(arr, 1));
  Invalidate();
}

//绘制球体
void CCG2019112380熊宇新OGL3DView::OnDraw3dsphere() {
  // TODO: 在此添加命令处理程序代码
  COGLDrawSphereDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d center(dlg.x, dlg.y, dlg.z);
  double r = dlg.r;
  int slice = dlg.slice;
  int stacks = dlg.stacks;
  CG3DSphere* pSphere = new CG3DSphere(center, r, slice, stacks);
  pSphere->setDrawStyle(threeDStyle());
  addRenderable(pSphere);
  Invalidate();
}

void CCG2019112380熊宇新OGL3DView::OnDraw3drobot() {
  // TODO: 在此添加命令处理程序代码
  // COGLDrawSphereDlg dlg;
  // dlg.DoModal();
  // double x = dlg.x;
  CG3DRobot* probot = new CG3DRobot();
  addRenderable(probot);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotReset() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->robotReset();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotLeftarm() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->leftArmRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotRightarm() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->rightArmRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotLeftleg() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->leftLegRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotRightleg() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->rightLegRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotLeft() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->bodyLeftRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::On3drobotRight() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->bodyRigRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::_3DTranslate(double tx,
                                                double ty,
                                                double tz)  //平移
{
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->_3DTranslate(tx, ty, tz);
  Invalidate();
  UpdateData();
}
void CCG2019112380熊宇新OGL3DView::_3DRotate(
    double angle,
    double cx,
    double cy,
    double cz)  //旋转（逆时针为正，度）
{
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->_3DRotate(angle, cx, cy, cz);
  Invalidate();
  UpdateData();
}
void CCG2019112380熊宇新OGL3DView::_3DScale(double sx,
                                            double sy,
                                            double sz)  //缩放

{
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  pDoc->_3DScale(sx, sy, sz);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::Move3DCamera(double tx,
                                                double ty)  //频移观察窗口
{

}

void CCG2019112380熊宇新OGL3DView::Zoom3DCamera(
    double ratio)  //给定观察窗口的缩放比例
{
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)                                     
    return;
  pDoc->Zoom3DCamera(ratio);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::Rotate3DCamera(
    double angle)  //转动相机（观察坐标系)
{}
void CCG2019112380熊宇新OGL3DView::setProjection(int mode) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  pDoc->setProjection(mode);
  Invalidate();
  UpdateData();
}
int CCG2019112380熊宇新OGL3DView::FocalDistance() {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 1; 
  return pDoc->FocalDistance();
  Invalidate();
  UpdateData();
}
int CCG2019112380熊宇新OGL3DView::MaterialSelect(){
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 1;
  return pDoc->MaterialSelect();
  Invalidate();
  UpdateData();
}
void CCG2019112380熊宇新OGL3DView::setEyePos(double eyex,
                                                           double eyey,
                                                           double eyez) {
  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return ;
  pDoc->setEyePos(eyex, eyey, eyez);
  Invalidate();
  UpdateData();
}
//void CCG2019112380熊宇新OGL3DView::setfocalDis(int dis) {
//  CCG2019112380熊宇新OGL3DDoc* pDoc = GetDocument();
//  ASSERT_VALID(pDoc);
//  if (!pDoc)
//    return;
//  pDoc->setfocalDis(dis);
//  Invalidate();
//  UpdateData();
//}
void CCG2019112380熊宇新OGL3DView::On3dtranstaleLeft() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(-50, 0, 0);
}

void CCG2019112380熊宇新OGL3DView::On3dtranslateRight() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(50, 0, 0);
}

void CCG2019112380熊宇新OGL3DView::On3dtranslateUp() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(0, 50, 0);
}

void CCG2019112380熊宇新OGL3DView::On3dtranslateDown() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(0, -50, 0);
}

void CCG2019112380熊宇新OGL3DView::On3dtranslateBefore() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(0, 0, 50);
}

void CCG2019112380熊宇新OGL3DView::On3dtranslateAfter() {
  // TODO: 在此添加命令处理程序代码
  _3DTranslate(0, 0, -50);
}


void CCG2019112380熊宇新OGL3DView::On3dscaleUp() {
  // TODO: 在此添加命令处理程序代码
  _3DScale(1.2, 1.2, 1.2);
}

void CCG2019112380熊宇新OGL3DView::On3dscaleDown() {
  // TODO: 在此添加命令处理程序代码
  _3DScale(0.8, 0.8, 0.8);
}

void CCG2019112380熊宇新OGL3DView::On3drotateXaxi() {
  // TODO: 在此添加命令处理程序代码
  _3DRotate(30, 1.0, 0, 0);
}

void CCG2019112380熊宇新OGL3DView::On3drotateYaxi() {
  // TODO: 在此添加命令处理程序代码
  _3DRotate(30, 0.0, 1.0, 0.0);
}

void CCG2019112380熊宇新OGL3DView::On3drotateZaxi() {
  // TODO: 在此添加命令处理程序代码
  _3DRotate(30, 0.0, 0.0, 1.0);
}

void CCG2019112380熊宇新OGL3DView::On3dobserverScaleUp() {
  // TODO: 在此添加命令处理程序代码
  Zoom3DCamera(1.3);
}

void CCG2019112380熊宇新OGL3DView::On3dobserverScaleDown() {
  // TODO: 在此添加命令处理程序代码
  Zoom3DCamera(0.7);
}

void CCG2019112380熊宇新OGL3DView::OnParalleProjection() {
  // TODO: 在此添加命令处理程序代码
  setProjection(0);
}

void CCG2019112380熊宇新OGL3DView::OnPerspectiveProjection() {
  // TODO: 在此添加命令处理程序代码
  setProjection(1);
}

void CCG2019112380熊宇新OGL3DView::On3dfocalChange() {
  // TODO: 在此添加命令处理程序代码
  int num = FocalDistance();
  double s = 1.0;
  s += num / 9.9;
  Zoom3DCamera(s);
}

void CCG2019112380熊宇新OGL3DView::On3dmoveViewport() {
  // TODO: 在此添加命令处理程序代码
  COGLViewPortPos dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d v(dlg.x, dlg.y, dlg.z);
  setEyePos(v.x(), v.y(), v.z());
}
//创建平行光
void CCG2019112380熊宇新OGL3DView::OnCreateParallelSource() {
  // TODO: 在此添加命令处理程序代码
  COGLCreateLightDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d ambient(dlg.ambient1, dlg.ambient2, dlg.ambient3);
  Vec3d diffuse(dlg.diffuse1, dlg.diffuse2, dlg.diffuse3);
  Vec3d specular(dlg.specular1, dlg.specular2, dlg.specular3);
  Vec3d pos(dlg.pos1, dlg.pos2, dlg.pos3);
  CG3DLightSource* pLight =
      new CG3DLightSource(0, ambient, diffuse, specular, pos);
  addRenderable(pLight);
  Invalidate();
  UpdateData();
}
// 创建点光源
void CCG2019112380熊宇新OGL3DView::OnCreatePointSource() {
  // TODO: 在此添加命令处理程序代码
  COGLCreateLightDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d ambient(dlg.ambient1, dlg.ambient2, dlg.ambient3);
  Vec3d diffuse(dlg.diffuse1, dlg.diffuse2, dlg.diffuse3);
  Vec3d specular(dlg.specular1, dlg.specular2, dlg.specular3);
  Vec3d pos(dlg.pos1, dlg.pos2, dlg.pos3);
  CG3DLightSource* pLight =
      new CG3DLightSource(1, ambient, diffuse, specular, pos);
  addRenderable(pLight);
  Invalidate();
  UpdateData();
}
//创建聚光灯
void CCG2019112380熊宇新OGL3DView::OnCreateSpotSource() {
  // TODO: 在此添加命令处理程序代码
  COGLCreateLightDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  //COGLCreateSpotDlg dlg2;
  //dlg2.DoModal();
  //if (!dlg.f)
  //  return;
  Vec3d ambient(dlg.ambient1, dlg.ambient2, dlg.ambient3);
  Vec3d diffuse(dlg.diffuse1, dlg.diffuse2, dlg.diffuse3);
  Vec3d specular(dlg.specular1, dlg.specular2, dlg.specular3);
  Vec3d pos(dlg.pos1, dlg.pos2, dlg.pos3);
  //Vec3d dire(dlg2.direction1, dlg2.direction2, dlg2.direction3);
  //double angle = dlg2.angle;
  //double expon = dlg2.exponent;
  CG3DLightSource* pLight = new CG3DLightSource(
      2, ambient, diffuse, specular, pos /*, dire, angle, expon */);
  addRenderable(pLight);
  Invalidate();
  UpdateData();
}

//创建茶壶
void CCG2019112380熊宇新OGL3DView::On3ddrawTeapot() {
  // TODO: 在此添加命令处理程序代码
  int choice = 0;
  choice = MaterialSelect();  //材质选择
  COGLDrawPointDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3f pos(dlg.x, dlg.y, dlg.z);  //茶壶位置
  float shiness = 0.0;             //亮度
  Vec3f ambient(0.0, 0.0, 0.0);
  Vec3f diffuse(0.0, 0.0, 0.0);
  Vec3f specular(0.0, 0.0, 0.0);
  switch (choice) {
    case 0:
      ambient.x() = 0.174500;
      ambient.y() = 0.011750;
      ambient.z() = 0.011750;
      diffuse.x() = 0.61424;
      diffuse.y() = 0.04136;
      diffuse.z() = 0.04136;
      specular.x() = 0.297254;
      specular.y() = 0.62959;
      specular.z() = 0.62959;
      shiness = 0.1;  //红宝石参数
      break;
    case 1:
      ambient.x() = 0.25;
      ambient.y() = 0.20725;
      ambient.z() = 0.20725;
      diffuse.x() = 1.0;
      diffuse.y() = 0.829;
      diffuse.z() = 0.829;
      specular.x() = 0.296648;
      specular.y() = 0.296648;
      specular.z() = 0.296648;
      shiness = 0.088;  //珍珠参数
      break;
    case 2:
      ambient.x() = 0.24725;
      ambient.y() = 0.1995;
      ambient.z() = 0.0745;
      diffuse.x() = 0.75164;
      diffuse.y() = 0.60648;
      diffuse.z() = 0.22648;
      specular.x() = 0.628281;
      specular.y() = 0.555802;
      specular.z() = 0.366065;
      shiness = 0.4;  //黄金参数
      break;
    case 3:
      ambient.x() = 0.1;
      ambient.y() = 0.18725;
      ambient.z() = 0.1745;
      diffuse.x() = 0.396;
      diffuse.y() = 0.74151;
      diffuse.z() = 0.69102;
      specular.x() = 0.297254;
      specular.y() = 0.30829;
      specular.z() = 0.306678;
      shiness = 0.1;  //绿松石
      break;
    case 4:
      ambient.x() = 0.0;
      ambient.y() = 0.0;
      ambient.z() = 0.0;
      diffuse.x() = 0.55;
      diffuse.y() = 0.55;
      diffuse.z() = 0.55;
      specular.x() = 0.70;
      specular.y() = 0.70;
      specular.z() = 0.70;
      shiness = 0.25;  //白塑料
      break;
    default:
      shiness = 1.0;
      break;
  }
  CG3DTeapot* pTeapot =
      new CG3DTeapot(pos, ambient, diffuse, specular, shiness);
  addRenderable(pTeapot);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新OGL3DView::OnActivateView(BOOL bActivate,
                                                  CView* pActivateView,
                                                  CView* pDeactiveView) {
  // TODO: 在此添加专用代码和/或调用基类

  if (bActivate) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if (pMainWnd)
      pMainWnd->FillClassView();
  }
  COGL3DView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
