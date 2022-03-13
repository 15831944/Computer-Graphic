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

// CG2019112380������OGL3DView.cpp: CCG2019112380������OGL3DView ���ʵ��
//

#include "pch.h"
#include "framework.h"


// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2019112380������.h"
#endif

#include "CG2019112380������OGL3DDoc.h"
#include "CG2019112380������OGL3DView.h"
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

// CCG2019112380������OGL3DView

IMPLEMENT_DYNCREATE(CCG2019112380������OGL3DView, COGL3DView)

BEGIN_MESSAGE_MAP(CCG2019112380������OGL3DView, COGL3DView)
// ��׼��ӡ����
ON_COMMAND(ID_FILE_PRINT, &COGL3DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &COGL3DView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW,
           &CCG2019112380������OGL3DView::OnFilePrintPreview)
ON_WM_CONTEXTMENU()
ON_WM_RBUTTONUP()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
ON_COMMAND(ID_DRAW_3DDOT, &CCG2019112380������OGL3DView::OnDraw3ddot)
ON_COMMAND(ID_DRAW_3DLINESEG, &CCG2019112380������OGL3DView::OnDraw3dlineseg)
ON_COMMAND(ID_DRAW_3DLINESTRIP,
           &CCG2019112380������OGL3DView::OnDraw3dlinestrip)
ON_COMMAND(ID_DRAW_3DLINELOOP, &CCG2019112380������OGL3DView::OnDraw3dlineloop)
ON_COMMAND(ID_DRAW_3DPOLYGON, &CCG2019112380������OGL3DView::OnDraw3dpolygon)
ON_COMMAND(ID_DRAW_3DTRAINGLE, &CCG2019112380������OGL3DView::OnDraw3dtraingle)
ON_COMMAND(ID_DRAW_3DTRAINGLE_FAN,
           &CCG2019112380������OGL3DView::OnDraw3dtraingleFan)
ON_COMMAND(ID_DRAW_3DQUADS, &CCG2019112380������OGL3DView::OnDraw3dquads)
ON_COMMAND(ID_DRAW_3DTRAINGLE_STRIP,
           &CCG2019112380������OGL3DView::OnDraw3dtraingleStrip)
ON_COMMAND(ID_DRAW_3DQUADS_STRIP,
           &CCG2019112380������OGL3DView::OnDraw3dquadsStrip)
ON_COMMAND(ID_DRAW_3DSPHERE, &CCG2019112380������OGL3DView::OnDraw3dsphere)
ON_COMMAND(ID_DRAW_3DROBOT, &CCG2019112380������OGL3DView::OnDraw3drobot)
ON_COMMAND(ID_3DROBOT_RESET, &CCG2019112380������OGL3DView::On3drobotReset)
ON_COMMAND(ID_3DROBOT_LEFTARM, &CCG2019112380������OGL3DView::On3drobotLeftarm)
ON_COMMAND(ID_3DROBOT_RIGHTARM,
           &CCG2019112380������OGL3DView::On3drobotRightarm)
ON_COMMAND(ID_3DROBOT_LEFTLEG, &CCG2019112380������OGL3DView::On3drobotLeftleg)
ON_COMMAND(ID_3DROBOT_RIGHTLEG,
           &CCG2019112380������OGL3DView::On3drobotRightleg)
ON_COMMAND(ID_3DROBOT_LEFT, &CCG2019112380������OGL3DView::On3drobotLeft)
ON_COMMAND(ID_3DROBOT_RIGHT, &CCG2019112380������OGL3DView::On3drobotRight)

ON_COMMAND(ID_3DTRANSTALE_LEFT,
           &CCG2019112380������OGL3DView::On3dtranstaleLeft)
ON_COMMAND(ID_3DTRANSLATE_RIGHT,
           &CCG2019112380������OGL3DView::On3dtranslateRight)
ON_COMMAND(ID_3DTRANSLATE_UP, &CCG2019112380������OGL3DView::On3dtranslateUp)
ON_COMMAND(ID_3DTRANSLATE_DOWN,
           &CCG2019112380������OGL3DView::On3dtranslateDown)
ON_COMMAND(ID_3DTRANSLATE_BEFORE,
           &CCG2019112380������OGL3DView::On3dtranslateBefore)
ON_COMMAND(ID_3DTRANSLATE_AFTER,
           &CCG2019112380������OGL3DView::On3dtranslateAfter)
ON_COMMAND(ID_3DROTATE_XAXI, &CCG2019112380������OGL3DView::On3drotateXaxi)
ON_COMMAND(ID_3DSCALE_UP, &CCG2019112380������OGL3DView::On3dscaleUp)
ON_COMMAND(ID_3DSCALE_DOWN, &CCG2019112380������OGL3DView::On3dscaleDown)
ON_COMMAND(ID_3DROTATE_YAXI, &CCG2019112380������OGL3DView::On3drotateYaxi)
ON_COMMAND(ID_3DROTATE_ZAXI, &CCG2019112380������OGL3DView::On3drotateZaxi)
ON_COMMAND(ID_3DOBSERVER_SCALE_UP,
           &CCG2019112380������OGL3DView::On3dobserverScaleUp)
ON_COMMAND(ID_3DOBSERVER_SCALE_DOWN,
           &CCG2019112380������OGL3DView::On3dobserverScaleDown)
ON_COMMAND(ID_PARALLE_PROJECTION,
           &CCG2019112380������OGL3DView::OnParalleProjection)
ON_COMMAND(ID_PERSPECTIVE_PROJECTION,
           &CCG2019112380������OGL3DView::OnPerspectiveProjection)
ON_COMMAND(ID_3DFOCAL_CHANGE, &CCG2019112380������OGL3DView::On3dfocalChange)
ON_COMMAND(ID_3DMOVE_VIEWPORT, &CCG2019112380������OGL3DView::On3dmoveViewport)
ON_COMMAND(ID_CREATE_POINT_SOURCE,
           &CCG2019112380������OGL3DView::OnCreatePointSource)
ON_COMMAND(ID_3DDRAW_TEAPOT, &CCG2019112380������OGL3DView::On3ddrawTeapot)
ON_COMMAND(ID_CREATE_PARALLEL_SOURCE,
           &CCG2019112380������OGL3DView::OnCreateParallelSource)
ON_COMMAND(ID_CREATE_SPOT_SOURCE,
           &CCG2019112380������OGL3DView::OnCreateSpotSource)
END_MESSAGE_MAP()

// CCG2019112380������OGL3DView ����/����

CCG2019112380������OGL3DView::CCG2019112380������OGL3DView() noexcept {
  // TODO: �ڴ˴���ӹ������
}

CCG2019112380������OGL3DView::~CCG2019112380������OGL3DView() {}

BOOL CCG2019112380������OGL3DView::PreCreateWindow(CREATESTRUCT& cs) {
  // TODO: �ڴ˴�ͨ���޸�
  //  CREATESTRUCT cs ���޸Ĵ��������ʽ

  return COGL3DView::PreCreateWindow(cs);
}

// CCG2019112380������OGL3DView ��ͼ

void CCG2019112380������OGL3DView::OnDraw(CDC* /*pDC*/) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;

  // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
  RenderScene();
}

// CCG2019112380������OGL3DView ��ӡ

void CCG2019112380������OGL3DView::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
  AFXPrintPreview(this);
#endif
}

BOOL CCG2019112380������OGL3DView::OnPreparePrinting(CPrintInfo* pInfo) {
  // Ĭ��׼��
  return DoPreparePrinting(pInfo);
}

void CCG2019112380������OGL3DView::OnBeginPrinting(CDC* /*pDC*/,
                                                   CPrintInfo* /*pInfo*/) {
  // TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCG2019112380������OGL3DView::OnEndPrinting(CDC* /*pDC*/,
                                                 CPrintInfo* /*pInfo*/) {
  // TODO: ��Ӵ�ӡ����е��������
}

void CCG2019112380������OGL3DView::OnRButtonUp(UINT /* nFlags */,
                                               CPoint point) {
  ClientToScreen(&point);
  OnContextMenu(this, point);
}

void CCG2019112380������OGL3DView::OnContextMenu(CWnd* /* pWnd */,
                                                 CPoint point) {
#ifndef SHARED_HANDLERS
  theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x,
                                                point.y, this, TRUE);
#endif
}

// CCG2019112380������OGL3DView ���

#ifdef _DEBUG
void CCG2019112380������OGL3DView::AssertValid() const {
  COGL3DView::AssertValid();
}

void CCG2019112380������OGL3DView::Dump(CDumpContext& dc) const {
  COGL3DView::Dump(dc);
}

CCG2019112380������OGL3DDoc* CCG2019112380������OGL3DView::GetDocument()
    const  // �ǵ��԰汾��������
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112380������OGL3DDoc)));
  return (CCG2019112380������OGL3DDoc*)m_pDocument;
}
#endif  //_DEBUG

// CCG2019112380������OGL3DView ��Ϣ�������

//����Ĭ���ӿڲ���
bool CCG2019112380������OGL3DView::setDefaultViewPort(int xl,
                                                      int yb,
                                                      int xr,
                                                      int yt) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->setDefaultViewPort(xl, yb, xr, yt);
}

//��Ⱦ����
bool CCG2019112380������OGL3DView::RenderScene() {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return false;
  return pDoc->RenderScene(this);
}

int CCG2019112380������OGL3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (COGL3DView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  �ڴ������ר�õĴ�������

  return 0;
}

int CCG2019112380������OGL3DView::threeDStyle() {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT(pDoc);
  if (!pDoc) {
    return 0;
  }
  return pDoc->threeDStyle();
}

void CCG2019112380������OGL3DView::OnDestroy() {
  COGL3DView::OnDestroy();

  // TODO: �ڴ˴������Ϣ����������
}

BOOL CCG2019112380������OGL3DView::OnEraseBkgnd(CDC* pDC) {
  // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

  return COGL3DView::OnEraseBkgnd(pDC);
}

void CCG2019112380������OGL3DView::OnSize(UINT nType, int cx, int cy) {
  COGL3DView::OnSize(nType, cx, cy);

  // TODO: �ڴ˴������Ϣ����������
  setDefaultViewPort(0, 0, cx, cy);
}
bool CCG2019112380������OGL3DView::addRenderable(CGRenderable* r) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
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
bool CCG2019112380������OGL3DView::delRenderable(CGRenderable* r) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
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

//��
void CCG2019112380������OGL3DView::OnDraw3ddot() {
  // TODO: �ڴ���������������
  COGLDrawPointDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d v(dlg.x, dlg.y, dlg.z);
  addRenderable(new CG3DPoint(v));
  Invalidate();
  UpdateData();
}

//�߶�
void CCG2019112380������OGL3DView::OnDraw3dlineseg() {
  // TODO: �ڴ���������������
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

//���պ�������
void CCG2019112380������OGL3DView::OnDraw3dlinestrip() {
  // TODO: �ڴ���������������
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

//�պ�����
void CCG2019112380������OGL3DView::OnDraw3dlineloop() {
  // TODO: �ڴ���������������
  Vec3dArray arr;
  arr.push_back(Vec3d(300, -150, 0));
  arr.push_back(Vec3d(230, -150, 0));
  arr.push_back(Vec3d(300, -50, 0));
  arr.push_back(Vec3d(230, -50, 0));
  addRenderable(new CG3DPolygon(arr, 1));
  Invalidate();
  UpdateData();
}

//�����
void CCG2019112380������OGL3DView::OnDraw3dpolygon() {
  // TODO: �ڴ���������������
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

//������  mode==0
void CCG2019112380������OGL3DView::OnDraw3dtraingle() {
  // TODO: �ڴ���������������
  Vec3dArray arr;
  arr.push_back(Vec3d(0, 50, 0));
  arr.push_back(Vec3d(-50, -50, 0));
  arr.push_back(Vec3d(50, -50, 0));
  addRenderable(new CG3DTraingles(arr, 0));
  Invalidate();
  UpdateData();
}

//������ mode==1
void CCG2019112380������OGL3DView::OnDraw3dtraingleFan() {
  // TODO: �ڴ���������������
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

//�������� mode==2
void CCG2019112380������OGL3DView::OnDraw3dtraingleStrip() {
  // TODO: �ڴ���������������
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

//�ı��� mode==0
void CCG2019112380������OGL3DView::OnDraw3dquads() {
  // TODO: �ڴ���������������
  Vec3dArray arr;
  arr.push_back(Vec3d(100, 100, 0));
  arr.push_back(Vec3d(200, 100, 0));
  arr.push_back(Vec3d(250, 200, 100));
  arr.push_back(Vec3d(150, 200, 100));
  addRenderable(new CG3DQuads(arr, 0));
  Invalidate();
  UpdateData();
}

//�ı������� mode==1
void CCG2019112380������OGL3DView::OnDraw3dquadsStrip() {
  // TODO: �ڴ���������������
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

//��������
void CCG2019112380������OGL3DView::OnDraw3dsphere() {
  // TODO: �ڴ���������������
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

void CCG2019112380������OGL3DView::OnDraw3drobot() {
  // TODO: �ڴ���������������
  // COGLDrawSphereDlg dlg;
  // dlg.DoModal();
  // double x = dlg.x;
  CG3DRobot* probot = new CG3DRobot();
  addRenderable(probot);
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotReset() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->robotReset();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotLeftarm() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->leftArmRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotRightarm() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->rightArmRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotLeftleg() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->leftLegRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotRightleg() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->rightLegRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotLeft() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->bodyLeftRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::On3drobotRight() {
  // TODO: �ڴ���������������
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->bodyRigRotate();
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::_3DTranslate(double tx,
                                                double ty,
                                                double tz)  //ƽ��
{
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->_3DTranslate(tx, ty, tz);
  Invalidate();
  UpdateData();
}
void CCG2019112380������OGL3DView::_3DRotate(
    double angle,
    double cx,
    double cy,
    double cz)  //��ת����ʱ��Ϊ�����ȣ�
{
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  if (!pDoc)
    return;
  pDoc->_3DRotate(angle, cx, cy, cz);
  Invalidate();
  UpdateData();
}
void CCG2019112380������OGL3DView::_3DScale(double sx,
                                            double sy,
                                            double sz)  //����

{
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  pDoc->_3DScale(sx, sy, sz);
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::Move3DCamera(double tx,
                                                double ty)  //Ƶ�ƹ۲촰��
{

}

void CCG2019112380������OGL3DView::Zoom3DCamera(
    double ratio)  //�����۲촰�ڵ����ű���
{
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)                                     
    return;
  pDoc->Zoom3DCamera(ratio);
  Invalidate();
  UpdateData();
}

void CCG2019112380������OGL3DView::Rotate3DCamera(
    double angle)  //ת��������۲�����ϵ)
{}
void CCG2019112380������OGL3DView::setProjection(int mode) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  pDoc->setProjection(mode);
  Invalidate();
  UpdateData();
}
int CCG2019112380������OGL3DView::FocalDistance() {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 1; 
  return pDoc->FocalDistance();
  Invalidate();
  UpdateData();
}
int CCG2019112380������OGL3DView::MaterialSelect(){
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return 1;
  return pDoc->MaterialSelect();
  Invalidate();
  UpdateData();
}
void CCG2019112380������OGL3DView::setEyePos(double eyex,
                                                           double eyey,
                                                           double eyez) {
  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return ;
  pDoc->setEyePos(eyex, eyey, eyez);
  Invalidate();
  UpdateData();
}
//void CCG2019112380������OGL3DView::setfocalDis(int dis) {
//  CCG2019112380������OGL3DDoc* pDoc = GetDocument();
//  ASSERT_VALID(pDoc);
//  if (!pDoc)
//    return;
//  pDoc->setfocalDis(dis);
//  Invalidate();
//  UpdateData();
//}
void CCG2019112380������OGL3DView::On3dtranstaleLeft() {
  // TODO: �ڴ���������������
  _3DTranslate(-50, 0, 0);
}

void CCG2019112380������OGL3DView::On3dtranslateRight() {
  // TODO: �ڴ���������������
  _3DTranslate(50, 0, 0);
}

void CCG2019112380������OGL3DView::On3dtranslateUp() {
  // TODO: �ڴ���������������
  _3DTranslate(0, 50, 0);
}

void CCG2019112380������OGL3DView::On3dtranslateDown() {
  // TODO: �ڴ���������������
  _3DTranslate(0, -50, 0);
}

void CCG2019112380������OGL3DView::On3dtranslateBefore() {
  // TODO: �ڴ���������������
  _3DTranslate(0, 0, 50);
}

void CCG2019112380������OGL3DView::On3dtranslateAfter() {
  // TODO: �ڴ���������������
  _3DTranslate(0, 0, -50);
}


void CCG2019112380������OGL3DView::On3dscaleUp() {
  // TODO: �ڴ���������������
  _3DScale(1.2, 1.2, 1.2);
}

void CCG2019112380������OGL3DView::On3dscaleDown() {
  // TODO: �ڴ���������������
  _3DScale(0.8, 0.8, 0.8);
}

void CCG2019112380������OGL3DView::On3drotateXaxi() {
  // TODO: �ڴ���������������
  _3DRotate(30, 1.0, 0, 0);
}

void CCG2019112380������OGL3DView::On3drotateYaxi() {
  // TODO: �ڴ���������������
  _3DRotate(30, 0.0, 1.0, 0.0);
}

void CCG2019112380������OGL3DView::On3drotateZaxi() {
  // TODO: �ڴ���������������
  _3DRotate(30, 0.0, 0.0, 1.0);
}

void CCG2019112380������OGL3DView::On3dobserverScaleUp() {
  // TODO: �ڴ���������������
  Zoom3DCamera(1.3);
}

void CCG2019112380������OGL3DView::On3dobserverScaleDown() {
  // TODO: �ڴ���������������
  Zoom3DCamera(0.7);
}

void CCG2019112380������OGL3DView::OnParalleProjection() {
  // TODO: �ڴ���������������
  setProjection(0);
}

void CCG2019112380������OGL3DView::OnPerspectiveProjection() {
  // TODO: �ڴ���������������
  setProjection(1);
}

void CCG2019112380������OGL3DView::On3dfocalChange() {
  // TODO: �ڴ���������������
  int num = FocalDistance();
  double s = 1.0;
  s += num / 9.9;
  Zoom3DCamera(s);
}

void CCG2019112380������OGL3DView::On3dmoveViewport() {
  // TODO: �ڴ���������������
  COGLViewPortPos dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3d v(dlg.x, dlg.y, dlg.z);
  setEyePos(v.x(), v.y(), v.z());
}
//����ƽ�й�
void CCG2019112380������OGL3DView::OnCreateParallelSource() {
  // TODO: �ڴ���������������
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
// �������Դ
void CCG2019112380������OGL3DView::OnCreatePointSource() {
  // TODO: �ڴ���������������
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
//�����۹��
void CCG2019112380������OGL3DView::OnCreateSpotSource() {
  // TODO: �ڴ���������������
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

//�������
void CCG2019112380������OGL3DView::On3ddrawTeapot() {
  // TODO: �ڴ���������������
  int choice = 0;
  choice = MaterialSelect();  //����ѡ��
  COGLDrawPointDlg dlg;
  dlg.DoModal();
  if (!dlg.f)
    return;
  Vec3f pos(dlg.x, dlg.y, dlg.z);  //���λ��
  float shiness = 0.0;             //����
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
      shiness = 0.1;  //�챦ʯ����
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
      shiness = 0.088;  //�������
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
      shiness = 0.4;  //�ƽ����
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
      shiness = 0.1;  //����ʯ
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
      shiness = 0.25;  //������
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

void CCG2019112380������OGL3DView::OnActivateView(BOOL bActivate,
                                                  CView* pActivateView,
                                                  CView* pDeactiveView) {
  // TODO: �ڴ����ר�ô����/����û���

  if (bActivate) {
    CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    if (pMainWnd)
      pMainWnd->FillClassView();
  }
  COGL3DView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
