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

// CG2019112380熊宇新GDI2DView.cpp: CCG2019112380熊宇新GDI2DView 类的实现
//

#include "framework.h"
#include "pch.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112380熊宇新.h"
#endif
#include "CG2019112380熊宇新GDI2DDoc.h" -
#include "CG2019112380熊宇新GDI2DView.h"
#include "CGDI2DRenderContext.h"
#include "Create2DCircle2PDiameter.h"
#include "Create2DCircle3P.h"
#include "Create2DCircle3PArc.h"
#include "Create2DCircleCR.h"
#include "Create2DLine.h"
#include "Create2DLineSegment.h"
#include "Create2DPolyline.h"
#include"Create2DPolygon.h"
#include"Create2DRegularPolygon.h"
#include "Create2DRay.h"
#include"Create2DSeedFill.h"
#include "MainFrame.h"
#include "UIEventListener.h"
#include"Transform2DTranslate.h"
#include"Transform2DRotateOrigin.h"
#include"Transform2DClip.h"
#include"Transform2DRotateCamera.h"
#include"Transform2DMoveCamera.h"
#include"Create2DClock.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112380熊宇新GDI2DView

IMPLEMENT_DYNCREATE(CCG2019112380熊宇新GDI2DView, CGDI2DView)

BEGIN_MESSAGE_MAP(CCG2019112380熊宇新GDI2DView, CGDI2DView)
// 标准打印命令
ON_COMMAND(ID_FILE_PRINT, &CGDI2DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &CGDI2DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW,
           &CCG2019112380熊宇新GDI2DView::OnFilePrintPreview)
ON_WM_CONTEXTMENU()
ON_WM_RBUTTONUP()
ON_WM_CHAR()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONDOWN()
ON_WM_MBUTTONUP()
ON_WM_RBUTTONDBLCLK()
ON_WM_RBUTTONDOWN()
ON_WM_SIZE()
ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_CDC_DRAW, &CCG2019112380熊宇新GDI2DView::OnCdcDraw)
ON_COMMAND(ID_DRAW_2DLINESEG, &CCG2019112380熊宇新GDI2DView::OnDraw2dlineseg)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DLINESEG,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlineseg)
ON_COMMAND(ID_DRAW_2DLINE_TIME, &CCG2019112380熊宇新GDI2DView::OnDraw2dlineTime)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DLINE_TIME,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlineTime)
ON_COMMAND(ID_DRAW_2DLINE, &CCG2019112380熊宇新GDI2DView::OnDraw2dline)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DLINE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dline)
ON_COMMAND(ID_DRAW_2DRAY, &CCG2019112380熊宇新GDI2DView::OnDraw2dray)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DRAY,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dray)
ON_COMMAND(ID_DRAW_2DLINE_PLOY, &CCG2019112380熊宇新GDI2DView::OnDraw2dlinePloy)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DLINE_PLOY,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlinePloy)
ON_COMMAND(ID_DRAW_2DCIRCLE_CR,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircleCenterRadius)
ON_UPDATE_COMMAND_UI(
    ID_DRAW_2DCIRCLE_CR,
    &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleCenterRadius)
ON_COMMAND(ID_DRAW_2DCIRCLE_DD,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircleDiameter)
ON_UPDATE_COMMAND_UI(
    ID_DRAW_2DCIRCLE_DD,
    &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleDiameter)
ON_COMMAND(ID_DRAW_2DCIRCLE_2PSEMI,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircle2psemi)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DCIRCLE_2PSEMI,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle2psemi)
ON_COMMAND(ID_DRAW_2DCIRCLE_3P,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3point)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DCIRCLE_3P,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3point)
ON_COMMAND(ID_DRAW_2DCIRCLE_3PARC,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3pointarc)
ON_UPDATE_COMMAND_UI(
    ID_DRAW_2DCIRCLE_3PARC,
    &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3pointarc)
ON_COMMAND(ID_DRAW_2DCIRCLE_3PFAN,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3pointfan)
ON_UPDATE_COMMAND_UI(
    ID_DRAW_2DCIRCLE_3PFAN,
    &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3pointfan)
ON_COMMAND(ID_DRAW_2DCIRCLE_OJARC,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircleOjarc)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DCIRCLE_OJARC,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleOjarc)
ON_COMMAND(ID_DRAW_2DCIRCLE_OJFAN,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dcircleOjfan)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DCIRCLE_OJFAN,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleOjfan)
ON_COMMAND(ID_DRAW_2DELLIPSE, &CCG2019112380熊宇新GDI2DView::OnDraw2dellipse)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DELLIPSE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dellipse)
ON_COMMAND(ID_DRAW_2DELLIPSE_ARC,
           &CCG2019112380熊宇新GDI2DView::OnDraw2dellipseArc)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DELLIPSE_ARC,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dellipseArc)
ON_COMMAND(ID_COMMAND_NONE, &CCG2019112380熊宇新GDI2DView::OnCommandNone)
ON_UPDATE_COMMAND_UI(ID_COMMAND_NONE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateCommandNone)
ON_COMMAND(ID_DRAW_2DPOLYGON, &CCG2019112380熊宇新GDI2DView::OnDraw2dpolygon)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DPOLYGON,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dpolygon)
ON_COMMAND(ID_DRAW_2DFILL, &CCG2019112380熊宇新GDI2DView::OnDraw2dfill)
ON_UPDATE_COMMAND_UI(ID_DRAW_2DFILL,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dfill)
ON_COMMAND(ID_SELECT_UN, &CCG2019112380熊宇新GDI2DView::OnSelectUn)
ON_COMMAND(ID_TRANSFORM_TRANSLATE_LEFT,
           &CCG2019112380熊宇新GDI2DView::OnTransformTranslateLeft)
ON_COMMAND(ID_TRANSFORM_TRANSLATE_RIGHT,
           &CCG2019112380熊宇新GDI2DView::OnTransformTranslateRight)
ON_COMMAND(ID_TRANSFORM_TRANSLATE_UP,
           &CCG2019112380熊宇新GDI2DView::OnTransformTranslateUp)
ON_COMMAND(ID_TRANSFORM_TRANSLATE_DOWN,
           &CCG2019112380熊宇新GDI2DView::OnTransformTranslateDown)
ON_COMMAND(ID_TRANSFORM_MIRROR_X_AXIS,
           &CCG2019112380熊宇新GDI2DView::OnTransformMirrorXAxis)
ON_COMMAND(ID_TRANSFORM_MIRROR_Y_AXIS,
           &CCG2019112380熊宇新GDI2DView::OnTransformMirrorYAxis)
ON_COMMAND(ID_TRANSFORM_MIRROR_ORIGIN,
           &CCG2019112380熊宇新GDI2DView::OnTransformMirrorOrigin)
ON_COMMAND(ID_TRANSFORM_MIRROR_Y_EQU_X,
           &CCG2019112380熊宇新GDI2DView::OnTransformMirrorYEquX)
ON_COMMAND(ID_TRANSFORM_MIRROR_Y_EQU_NEX,
           &CCG2019112380熊宇新GDI2DView::OnTransformMirrorYEquNeX)
ON_COMMAND(ID_TRANSFORM_ZOOM_IN,
           &CCG2019112380熊宇新GDI2DView::OnTransformZoomIn)
ON_COMMAND(ID_TRANSFORM_ZOOM_OUT,
           &CCG2019112380熊宇新GDI2DView::OnTransformZoomOut)
ON_COMMAND(ID_TRANSFORM_TRANSLATE,
           &CCG2019112380熊宇新GDI2DView::OnTransformTranslate)
ON_UPDATE_COMMAND_UI(ID_TRANSFORM_TRANSLATE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateTransformTranslate)
ON_COMMAND(ID_TRANSFORM_ROTATE_ORIGIN,
           &CCG2019112380熊宇新GDI2DView::OnTransformRotateOrigin)
ON_UPDATE_COMMAND_UI(
    ID_TRANSFORM_ROTATE_ORIGIN,
    &CCG2019112380熊宇新GDI2DView::OnUpdateTransformRotateOrigin)
ON_COMMAND(ID_CUT_CODE, &CCG2019112380熊宇新GDI2DView::OnCutCode)
ON_UPDATE_COMMAND_UI(ID_CUT_CODE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateCutCode)
ON_COMMAND(ID_OBSERVE_SCALE_UP, &CCG2019112380熊宇新GDI2DView::OnObserveScaleUp)
ON_COMMAND(ID_OBSERVE_SCALE_DOWN,
           &CCG2019112380熊宇新GDI2DView::OnObserveScaleDown)
ON_COMMAND(ID_OBSERVE_MOVE_VIEWPOINT,
           &CCG2019112380熊宇新GDI2DView::OnObserveMoveViewpoint)
ON_UPDATE_COMMAND_UI(
    ID_OBSERVE_MOVE_VIEWPOINT,
    &CCG2019112380熊宇新GDI2DView::OnUpdateObserveMoveViewpoint)
ON_COMMAND(ID_OBSERVE_ROTATE_ANGLE,
           &CCG2019112380熊宇新GDI2DView::OnObserveRotateAngle)
ON_UPDATE_COMMAND_UI(ID_OBSERVE_ROTATE_ANGLE,
                     &CCG2019112380熊宇新GDI2DView::OnUpdateObserveRotateAngle)
ON_COMMAND(ID_TRANSFORM_SHEAR_X,
           &CCG2019112380熊宇新GDI2DView::OnTransformShearX)
ON_COMMAND(ID_TRANSFORM_SHEAR_Y_AXIS,
           &CCG2019112380熊宇新GDI2DView::OnTransformShearYAxis)
ON_WM_CREATE()
ON_WM_TIMER()
ON_COMMAND(ID_CLOCK, &CCG2019112380熊宇新GDI2DView::OnClock)
ON_UPDATE_COMMAND_UI(ID_CLOCK, &CCG2019112380熊宇新GDI2DView::OnUpdateClock)
END_MESSAGE_MAP()

// CCG2019112380熊宇新GDI2DView 构造/析构

CCG2019112380熊宇新GDI2DView::CCG2019112380熊宇新GDI2DView() noexcept {
  // TODO: 在此处添加构造代码
}

CCG2019112380熊宇新GDI2DView::~CCG2019112380熊宇新GDI2DView() {}

BOOL CCG2019112380熊宇新GDI2DView::PreCreateWindow(CREATESTRUCT& cs) {
  // TODO: 在此处通过修改
  //  CREATESTRUCT cs 来修改窗口类或样式

  return CView::PreCreateWindow(cs);
}

// CCG2019112380熊宇新GDI2DView 绘图

void CCG2019112380熊宇新GDI2DView::OnDraw(CDC* pDC) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;

  // TODO: 在此处为本机数据添加绘制代码
  RenderScene();
  // DrawGraphics(pDC);
}

void CCG2019112380熊宇新GDI2DView::DrawGraphics(CDC* pDC) {
  //绘制直线
  CPen myPen1(PS_SOLID, 1, RGB(255, 0, 0));
  CPen* p01dPen = pDC->SelectObject(&myPen1);
  pDC->MoveTo(100, 100);
  pDC->LineTo(300, 100);
  pDC->SelectObject(p01dPen);

  //绘制圆
  CPen myPen2(PS_DASHDOTDOT, 0.7, RGB(255, 0, 225));
  CPen* p02dPen = pDC->SelectObject(&myPen2);
  pDC->Ellipse(310, 100, 600, 300);
  pDC->SelectObject(p02dPen);

  //绘制圆弧
  CPen myPen3(PS_DASH, 0.5, RGB(0, 72, 255));
  CPen* p03dPen = pDC->SelectObject(&myPen3);
  pDC->Arc(CRect(100, 150, 300, 300), CPoint(100, 100), CPoint(150, 250));
  pDC->SelectObject(p03dPen);

  //绘制矩形
  // pDC->FillSolidRect(100, 310, 300, 400, RGB(0, 70, 255));
  CPen myPen4(PS_SOLID, 1, RGB(0, 255, 90));
  CPen* p04dPen = pDC->SelectObject(&myPen4);
  pDC->Rectangle(100, 310, 300, 400);
  pDC->SelectObject(p04dPen);

  //绘制多边形
  CPoint p[5];
  p[0].x = 610, p[0].y = 10;
  p[1].x = 760, p[1].y = 10;
  p[2].x = 760, p[2].y = 100;
  p[3].x = 685, p[3].y = 150;
  p[4].x = 610, p[4].y = 100;
  CPen myPen5(PS_SOLID, 2, RGB(0, 55, 255));
  CPen* p05dPen = pDC->SelectObject(&myPen5);
  pDC->Polygon(p, 5);
  pDC->SelectObject(p05dPen);

  //绘制文本
  CPen mypen6(PS_DASHDOT, 10, RGB(0, 0, 0));
  CPen* p06dPen = pDC->SelectObject(&mypen6);
  CFont myfont;
  myfont.CreatePointFont(300, _T("黑体"));
  CFont* poldfont = pDC->SelectObject(&myfont);
  pDC->TextOutW(10, 10, L"计算机图形");
  pDC->SelectObject(p06dPen);
  pDC->SelectObject(poldfont);
}

//设置默认视口参数
bool CCG2019112380熊宇新GDI2DView::setDefaultViewPort(int xl,
                                                      int yb,
                                                      int xr,
                                                      int yt) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->setDefaultViewPort(xl, yb, xr, yt);
}
//渲染场景
bool CCG2019112380熊宇新GDI2DView::RenderScene() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->RenderScene(this);
}
void CCG2019112380熊宇新GDI2DView::OnSize(UINT nType, int cx, int cy) {
  CGDI2DView::OnSize(nType, cx, cy);
  // TODO: 在此处添加消息处理程序代码
  static int cnt = 0;
  cnt++;
  if (cnt >= 5)
    setDefaultViewPort(0, 0, cx, cy);
  setDefaultViewPort(0, 0, cx, cy);
}

// CCG2019112380熊宇新GDI2DView 打印

void CCG2019112380熊宇新GDI2DView::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
  AFXPrintPreview(this);
#endif
}

BOOL CCG2019112380熊宇新GDI2DView::OnPreparePrinting(CPrintInfo* pInfo) {
  // 默认准备
  return DoPreparePrinting(pInfo);
}

void CCG2019112380熊宇新GDI2DView::OnBeginPrinting(CDC* /*pDC*/,
                                                   CPrintInfo* /*pInfo*/) {
  // TODO: 添加额外的打印前进行的初始化过程
}

void CCG2019112380熊宇新GDI2DView::OnEndPrinting(CDC* /*pDC*/,
                                                 CPrintInfo* /*pInfo*/) {
  // TODO: 添加打印后进行的清理过程
}

void CCG2019112380熊宇新GDI2DView::OnRButtonUp(UINT  nFlags ,
                                               CPoint point) {
  if (m_pCommand)
    m_pCommand->OnRButtonUp(nFlags, Pos2i(point.x, point.y));
  OnContextMenu(this, point);
}

void CCG2019112380熊宇新GDI2DView::OnContextMenu(CWnd* /* pWnd */,
                                                 CPoint point) {
#ifndef SHARED_HANDLERS
  theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x,
                                                point.y, this, TRUE);
#endif
}

// CCG2019112380熊宇新GDI2DView 诊断

#ifdef _DEBUG
void CCG2019112380熊宇新GDI2DView::AssertValid() const {
  CView::AssertValid();
}

void CCG2019112380熊宇新GDI2DView::Dump(CDumpContext& dc) const {
  CView::Dump(dc);
}

CCG2019112380熊宇新GDI2DDoc* CCG2019112380熊宇新GDI2DView::GetDocument()
    const  // 非调试版本是内联的
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112380熊宇新GDI2DDoc)));
  return (CCG2019112380熊宇新GDI2DDoc*)m_pDocument;
}
#endif  //_DEBUG

// CCG2019112380熊宇新GDI2DView 消息处理程序

void CCG2019112380熊宇新GDI2DView::OnChar(UINT nChar,
                                          UINT nRepCnt,
                                          UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CView::OnChar(nChar, nRepCnt, nFlags);
}

void CCG2019112380熊宇新GDI2DView::OnKeyDown(UINT nChar,
                                             UINT nRepCnt,
                                             UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (nChar == VK_ESCAPE) {
    if (m_pCommand) {
      m_pCommand->Cancel();
      delete m_pCommand;
      m_pCommand = nullptr;
    }
  }
  if (m_pCommand)
    m_pCommand->OnKeyDown(nChar, nRepCnt, nFlags);
  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCG2019112380熊宇新GDI2DView::OnKeyUp(UINT nChar,
                                           UINT nRepCnt,
                                           UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (m_pCommand)
    m_pCommand->OnKeyUp(nChar, nRepCnt, nFlags);
  CView::OnKeyUp(nChar, nRepCnt, nFlags);
  CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCG2019112380熊宇新GDI2DView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (m_pCommand)
    m_pCommand->OnLButtonDblClk(nFlags, Pos2i(point.x, point.y));
  CView::OnLButtonDblClk(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnLButtonDown(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  //如果有交互命令，调用交互命令的处理
  if (m_pCommand)
    m_pCommand->OnLButtonDown(nFlags, Pos2i(point.x, point.y));
  CView::OnLButtonDown(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnLButtonUp(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (m_pCommand)
    m_pCommand->OnLButtonUp(nFlags, Pos2i(point.x, point.y));
  CView::OnLButtonUp(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnMButtonDblClk(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CView::OnMButtonDblClk(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnMButtonDown(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CView::OnMButtonDown(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnMButtonUp(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CView::OnMButtonUp(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnRButtonDblClk(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (m_pCommand)
    m_pCommand->OnRButtonDblClk(nFlags, Pos2i(point.x, point.y));
  CView::OnRButtonDblClk(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnRButtonDown(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (m_pCommand)
    m_pCommand->OnRButtonDown(nFlags, Pos2i(point.x, point.y));
  CView::OnRButtonDown(nFlags, point);
}

void CCG2019112380熊宇新GDI2DView::OnMouseHWheel(UINT nFlags,
                                                 short zDelta,
                                                 CPoint pt) {
  // 此功能要求 Windows Vista 或更高版本。
  // _WIN32_WINNT 符号必须 >= 0x0600。
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CView::OnMouseHWheel(nFlags, zDelta, pt);
}

void CCG2019112380熊宇新GDI2DView::OnMouseMove(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (pDoc != nullptr && pMainWnd != nullptr) {
    Vec2d v = pDoc->ViewPortToWorld(Vec2i(point.x, point.y));
    CString str;
    str.Format(_T("视口坐标（%d, %d）:世界坐标（%.2f,%.2f）"), point.x, point.y,
               v.x(), v.y());
    pMainWnd->ShowCoordOnStatusBar(str);
  }
  if (m_pCommand)
    m_pCommand->OnMouseMove(nFlags, Pos2i(point.x, point.y));
  CView::OnMouseMove(nFlags, point);
}

BOOL CCG2019112380熊宇新GDI2DView::OnMouseWheel(UINT nFlags,
                                                short zDelta,
                                                CPoint pt) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  return CView::OnMouseWheel(nFlags, zDelta, pt);
}

//状态栏上显示提示信息
void CCG2019112380熊宇新GDI2DView::Prompt(const CString& str) {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (pMainWnd != nullptr) {
    pMainWnd->ShowPrompt(str);
  }
}

Vec2d CCG2019112380熊宇新GDI2DView::ViewPortToWorld(const Vec2i& p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return Vec2d();
  return pDoc->ViewPortToWorld(p);
}

double CCG2019112380熊宇新GDI2DView::LengthViewPortToWorld(const double p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 0;
  return pDoc->LengthViewPortToWorld(p);
}
double CCG2019112380熊宇新GDI2DView::RadViewPortToWorld(const double p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 0;
  return pDoc->RadViewPortToWorld(p);
}

Vec2i CCG2019112380熊宇新GDI2DView::WorldToViewPort(const Vec2d& p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return Vec2i();
  return pDoc->WorldToViewPort(p);
}

double CCG2019112380熊宇新GDI2DView::LengthWorldToViewPort(const double p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = this->GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 0;
  return pDoc->LengthWorldToViewPort(p);
}
double CCG2019112380熊宇新GDI2DView::RadWorldToViewPort(const double p) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 0;
  return pDoc->RadWorldToViewPort(p);
}
//图层属性
int CCG2019112380熊宇新GDI2DView::LayerIndex() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->LayerIndex();
}
//画笔属性
COLORREF CCG2019112380熊宇新GDI2DView::PenColor() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->PenColor();
}
int CCG2019112380熊宇新GDI2DView::PenWidth() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->PenWidth();
}
int CCG2019112380熊宇新GDI2DView::PenStyle() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->PenStyle();
}
//画刷属性
bool CCG2019112380熊宇新GDI2DView::UseBrush() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->UseBrush();
}
COLORREF CCG2019112380熊宇新GDI2DView::BrushColor() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->BrushColor();
}
int CCG2019112380熊宇新GDI2DView::BrushIndex() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return -1;
  return pMainWnd->BrushIndex();
}
//画线算法
int CCG2019112380熊宇新GDI2DView::LineAlgorithm() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->LineAlgorithm();
}
//圆弧算法
int CCG2019112380熊宇新GDI2DView::CircleAlgorithm() {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->CircleAlgorithm();
}

//其他场景操作接口，如：
bool CCG2019112380熊宇新GDI2DView::addRenderable(CGRenderable* r) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
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
bool CCG2019112380熊宇新GDI2DView::delRenderable(CGRenderable* r) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
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

//填充算法
int CCG2019112380熊宇新GDI2DView::FillAlgorithm() const {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT(pDoc);
  if (!pDoc) {
    return 0;
  }
  return pDoc->FillAlgorithm();
}
int CCG2019112380熊宇新GDI2DView::TimeChose(){
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT(pDoc);
  if (!pDoc) {
    return 0;
  }
  return pDoc->TimeChose();
}
//是否勾选正多边形
bool CCG2019112380熊宇新GDI2DView::RegularPolygon() const {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return false;
  return pMainWnd->RegularPolygon();
}
//正多边形边数
int CCG2019112380熊宇新GDI2DView::RegularEdges() const {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->RegularEdges();
}
//点阵区域的边界颜色
COLORREF CCG2019112380熊宇新GDI2DView::BoundColor() const {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return RGB(0, 0, 0);
  return pMainWnd->BoundColor();
}
//点阵区域的内点颜色
COLORREF CCG2019112380熊宇新GDI2DView::FloodColor() const {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return RGB(255, 255, 255);
  return pMainWnd->FloodColor();
}

void CCG2019112380熊宇新GDI2DView::OnCdcDraw() {
  // TODO: 在此添加命令处理程序代码
}

//线段处理
void CCG2019112380熊宇新GDI2DView::OnDraw2dlineseg() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DLineSegment(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlineseg(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dLineSegment);
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dlineTime() {
  // TODO: 在此添加命令处理程序代码
  CGDI2DRenderContext rc(this);
  LARGE_INTEGER start, end, frequency;
  QueryPerformanceFrequency(&frequency);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlineTime(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

//直线处理
void CCG2019112380熊宇新GDI2DView::OnDraw2dline() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DLine(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dline(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dLine);
}

//射线处理
void CCG2019112380熊宇新GDI2DView::OnDraw2dray() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DRay(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dray(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dRay);
}

//折线处理
void CCG2019112380熊宇新GDI2DView::OnDraw2dlinePloy() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DPolyline(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dlinePloy(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dPolyline);
}

//圆心半径画圆
void CCG2019112380熊宇新GDI2DView::OnDraw2dcircleCenterRadius() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DCircleCR(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleCenterRadius(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand &&
                   m_pCommand->GetType() == cmd2dCircleCenterRadius);
}

//两点直径画圆
void CCG2019112380熊宇新GDI2DView::OnDraw2dcircleDiameter() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DCircle2PDiameter(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleDiameter(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand &&
                   m_pCommand->GetType() == cmd2dCricle2PDiameter);
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dcircle2psemi() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle2psemi(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

//三点画圆
void CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3point() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DCircle3P(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3point(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dCricle3PCircum);
}

//三点圆弧
void CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3pointarc() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DCircle3PArc(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3pointarc(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dCircle3PArc);
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dcircle3pointfan() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircle3pointfan(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

//三点外接圆弧
void CCG2019112380熊宇新GDI2DView::OnDraw2dcircleOjarc() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleOjarc(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dCircle3PExArc);
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dcircleOjfan() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dcircleOjfan(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dellipse() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dellipse(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dellipseArc() {
  // TODO: 在此添加命令处理程序代码
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dellipseArc(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
}

void CCG2019112380熊宇新GDI2DView::OnCommandNone() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
}
void CCG2019112380熊宇新GDI2DView::OnUpdateCommandNone(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(!m_pCommand);
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dpolygon() {
  // TODO: 在此添加命令处理程序代码
    if (m_pCommand) {
        m_pCommand->Cancel();
        delete m_pCommand;
        m_pCommand = nullptr;
     }
    if (!RegularPolygon())
      m_pCommand = new Create2DPolygon(this);
    else
      m_pCommand = new Create2DRegularPolygon(this);
}
void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dpolygon(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand &&
                   (m_pCommand->GetType() == cmd2dPolygon ||
                    m_pCommand->GetType() == cmd2dRegularPolygon));
}

void CCG2019112380熊宇新GDI2DView::OnDraw2dfill() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DSeedFill (this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateDraw2dfill(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dSeedFill);
}

void CCG2019112380熊宇新GDI2DView::OnActivateView(BOOL bActivate,
                                                  CView* pActivateView,
                                                  CView* pDeactiveView) {
  // TODO: 在此添加专用代码和/或调用基类
  if (bActivate) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if (pMainWnd)
      pMainWnd->FillClassView();
  }
  CGDI2DView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CCG2019112380熊宇新GDI2DView::Translate(double tx, double ty)  //平移
{
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Translate(tx, ty);
  Invalidate();
  UpdateWindow();
}
void CCG2019112380熊宇新GDI2DView::Rotate(double angle,double cx, double cy)  //旋转（逆时针为正，度）
{
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Rotate(angle, cx, cy);
  Invalidate();
  UpdateWindow();
}
void CCG2019112380熊宇新GDI2DView::Scale(double sx, double sy)  //缩放
{
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Scale(sx, sy);                     
  Invalidate();
  UpdateWindow();
}
void CCG2019112380熊宇新GDI2DView::ShearXYAxis(double shx,double shy)  //沿X、Y轴错切
{
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->ShearXYAxis(shx, shy);
  Invalidate();
  UpdateWindow();
}
//测试裁剪用（通过通过交互命令类调用，针对选择集中的对象）;
void CCG2019112380熊宇新GDI2DView::Clip(double xl, double yb,
                                      double xr, double yt) {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc) {
    pDoc->Clip(xl, yb, xr, yt, m_pRenderContext);
    Invalidate();
    UpdateWindow();
  }
}

 void CCG2019112380熊宇新GDI2DView::Move2DCamera(double tx, double ty)
 {
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  return pDoc->Move2DCamera(tx, ty);
}
 //观察窗口左下角、右上角
void CCG2019112380熊宇新GDI2DView::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt)
{
	CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	return pDoc->Zoom2DCamera(lb,rt);
}
//给定观察窗口的缩放比例（
void CCG2019112380熊宇新GDI2DView::Zoom2DCamera(double ratio)
{
	CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	return pDoc->Zoom2DCamera(ratio);
}

//转动相机（观察坐标系)
void CCG2019112380熊宇新GDI2DView::Rotate2DCamera(double angle)
{
	CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	return pDoc->Rotate2DCamera(angle);
}

void CCG2019112380熊宇新GDI2DView::OnSelectUn() {
  // TODO: 在此添加命令处理程序代码
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (pMainWnd)
    pMainWnd->UnselectClassView();
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->RenderableUnselectAll();
  Invalidate();
  UpdateWindow();
}

//左移十个单位
void CCG2019112380熊宇新GDI2DView::OnTransformTranslateLeft() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Translate( -10,0);  
  //每次移动的距离可自定义一个常量，此处表示点击【左移】，选中的图形左移5个单位
  Invalidate();
  UpdateWindow();
}

//右移十个单位
void CCG2019112380熊宇新GDI2DView::OnTransformTranslateRight() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Translate(10, 0);
  //每次移动的距离可自定义一个常量，此处表示点击【右移】，选中的图形右移5个单位
  Invalidate();
  UpdateWindow();
}

//上移十个单位
void CCG2019112380熊宇新GDI2DView::OnTransformTranslateUp() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Translate(0, 10);
  //每次移动的距离可自定义一个常量，此处表示点击【上移】，选中的图形上移5个单位
  Invalidate();
  UpdateWindow();
}

//下移十个单位
void CCG2019112380熊宇新GDI2DView::OnTransformTranslateDown() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Translate(0, -10);
  //每次移动的距离可自定义一个常量，此处表示点击【下移】，选中的图形下移5个单位
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformMirrorXAxis() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->MirrorXAxis();  //关于x轴对称
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformMirrorYAxis() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
	if (pDoc)
		pDoc->MirrorYAxis(); //关于y轴对称
	Invalidate();
	UpdateWindow();;
}

void CCG2019112380熊宇新GDI2DView::OnTransformMirrorOrigin() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->MirrorOrigin();  //关于原点轴对称
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformMirrorYEquX() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->MirrorYeqPosX();  //关于x=y轴对称
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformMirrorYEquNeX() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->MirrorYeNegPX();  //关于x=-y轴对称
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformZoomIn() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Scale(0.8, 0.8);  //缩小
  Invalidate();
  UpdateWindow();
}

void CCG2019112380熊宇新GDI2DView::OnTransformZoomOut() {
  // TODO: 在此添加命令处理程序代码
  CCG2019112380熊宇新GDI2DDoc* pDoc = GetDocument();
  if (pDoc)
    pDoc->Scale(1.5, 1.5);  //放大
  Invalidate();
  UpdateWindow();
}

//  平移处理
void CCG2019112380熊宇新GDI2DView::OnTransformTranslate() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Transform2DTranslate(this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateTransformTranslate(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dTranslate);
}

void CCG2019112380熊宇新GDI2DView::OnTransformRotateOrigin() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Transform2DRotateOrigin(this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateTransformRotateOrigin(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dRotateOrigin);
  
}

void CCG2019112380熊宇新GDI2DView::OnCutCode() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Transform2DClip(this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateCutCode(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码	
    pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dClip);
}

void CCG2019112380熊宇新GDI2DView::OnObserveScaleUp() {
  // TODO: 在此添加命令处理程序代码
  Zoom2DCamera(1.25);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新GDI2DView::OnObserveScaleDown() {
  // TODO: 在此添加命令处理程序代码
  Zoom2DCamera(0.8);
  Invalidate();
  UpdateData();
}

void CCG2019112380熊宇新GDI2DView::OnObserveMoveViewpoint() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Transform2DMoveCamera(this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateObserveMoveViewpoint(
    CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dMoveCamera);
}

void CCG2019112380熊宇新GDI2DView::OnObserveRotateAngle() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Transform2DRotateCamera (this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateObserveRotateAngle(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dRotateCamera);
}

void CCG2019112380熊宇新GDI2DView::OnTransformShearX() {
  // TODO: 在此添加命令处理程序代码
  ShearXYAxis(0.2, 0);
}

void CCG2019112380熊宇新GDI2DView::OnTransformShearYAxis() {
  // TODO: 在此添加命令处理程序代码
  ShearXYAxis(0, 0.2);
}

int CCG2019112380熊宇新GDI2DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CGDI2DView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  在此添加您专用的创建代码
  SetTimer(10, 1000, NULL);
  return 0;
}

void CCG2019112380熊宇新GDI2DView::OnTimer(UINT_PTR nIDEvent) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  Invalidate(true);
  CGDI2DView::OnTimer(nIDEvent);
}

void CCG2019112380熊宇新GDI2DView::OnClock() {
  // TODO: 在此添加命令处理程序代码
  if (m_pCommand) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
  m_pCommand = new Create2DClock(this);
}

void CCG2019112380熊宇新GDI2DView::OnUpdateClock(CCmdUI* pCmdUI) {
  // TODO: 在此添加命令更新用户界面处理程序代码
  pCmdUI->SetCheck(m_pCommand && m_pCommand->GetType() == cmd2dClock);
}

