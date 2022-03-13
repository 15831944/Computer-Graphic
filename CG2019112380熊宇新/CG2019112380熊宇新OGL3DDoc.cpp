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

// CG2019112380������OGL3DDoc.cpp: CCG2019112380������OGL3DDoc ���ʵ��
//
   #include "pch.h"
#include "framework.h"

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2019112380������.h"
#endif

#include <propkey.h>
#include "CG2019112380������OGL3DDoc.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112380������OGL3DDoc

IMPLEMENT_DYNCREATE(CCG2019112380������OGL3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCG2019112380������OGL3DDoc, CDocument)
ON_UPDATE_COMMAND_UI(ID_DRAW_3DMODE,
                     &CCG2019112380������OGL3DDoc::OnUpdateDraw3dmode)
ON_COMMAND(ID_DRAW_3DMODE, &CCG2019112380������OGL3DDoc::OnDraw3dmode)
ON_UPDATE_COMMAND_UI(ID_3DFOCAL_DISTANCE,
                     &CCG2019112380������OGL3DDoc::OnUpdate3dfocalDistance)
ON_UPDATE_COMMAND_UI(ID_COMBO_TEAPOT_MATERIAL,
                     &CCG2019112380������OGL3DDoc::OnUpdateComboTeapotMaterial)
END_MESSAGE_MAP()

// CCG2019112380������OGL3DDoc ����/����

CCG2019112380������OGL3DDoc::CCG2019112380������OGL3DDoc() noexcept {
  // TODO: �ڴ����һ���Թ������
}

CCG2019112380������OGL3DDoc::~CCG2019112380������OGL3DDoc() {}

BOOL CCG2019112380������OGL3DDoc::OnNewDocument() {
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: �ڴ�������³�ʼ������
  // (SDI �ĵ������ø��ĵ�)

  return TRUE;
}

// CCG2019112380������OGL3DDoc ���л�

void CCG2019112380������OGL3DDoc::Serialize(CArchive& ar) {
  if (ar.IsStoring()) {
    // TODO: �ڴ���Ӵ洢����
  } else {
    // TODO: �ڴ���Ӽ��ش���
  }
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCG2019112380������OGL3DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
  // �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CCG2019112380������OGL3DDoc::InitializeSearchContent() {
  CString strSearchContent;
  // ���ĵ����������������ݡ�
  // ���ݲ���Ӧ�ɡ�;���ָ�

  // ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
  SetSearchContent(strSearchContent);
}

void CCG2019112380������OGL3DDoc::SetSearchContent(const CString& value) {
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

// CCG2019112380������OGL3DDoc ���

#ifdef _DEBUG
void CCG2019112380������OGL3DDoc::AssertValid() const {
  CDocument::AssertValid();
}

void CCG2019112380������OGL3DDoc::Dump(CDumpContext& dc) const {
  CDocument::Dump(dc);
}
#endif  //_DEBUG

// CCG2019112380������OGL3DDoc ����

//����Ĭ���ӿڲ���
bool CCG2019112380������OGL3DDoc::setDefaultViewPort(int xl,
                                                     int yb,
                                                     int xr,
                                                     int yt) {
  return mScene.setDefaultViewPort(xl, yb, xr, yt);
}
//��Ⱦ������ָ���ͻ��������ӿڣ�
bool CCG2019112380������OGL3DDoc::RenderScene(COGL3DView* pView) {
  if (pView == nullptr)
    return false;
  return mScene.RenderScene(pView);
}

bool CCG2019112380������OGL3DDoc::addRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable))) {
    return mScene.addRenderable(r);
  }
  return false;
}
bool CCG2019112380������OGL3DDoc::delRenderable(CGRenderable* r) {
  if (r && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable))) {
    return mScene.delRenderable(r);
  }
  return false;
}
int CCG2019112380������OGL3DDoc::threeDStyle() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->threeDStyle();
}

void CCG2019112380������OGL3DDoc::OnUpdateDraw3dmode(CCmdUI* pCmdUI) {
  // TODO: �ڴ������������û����洦��������
  pCmdUI->Enable(true);
}

void CCG2019112380������OGL3DDoc::OnDraw3dmode() {
  // TODO: �ڴ���������������
}

void CCG2019112380������OGL3DDoc::robotReset() {
  return mScene.robotReset();
}
void CCG2019112380������OGL3DDoc::rightArmRotate() {
  return mScene.rightArmRotate();
}
void CCG2019112380������OGL3DDoc::leftArmRotate() {
  return mScene.leftArmRotate();
}
void CCG2019112380������OGL3DDoc::rightLegRotate() {
  return mScene.rightLegRotate();
}
void CCG2019112380������OGL3DDoc::leftLegRotate() {
  return mScene.leftLegRotate();
}
void CCG2019112380������OGL3DDoc::bodyLeftRotate() {
  return mScene.bodyLeftRotate();
}
void CCG2019112380������OGL3DDoc::bodyRigRotate() {
  return mScene.bodyRigRotate();
}
void CCG2019112380������OGL3DDoc::_3DTranslate(double tx,
                                               double ty,
                                               double tz)  //ƽ��
{
  return mScene._3DTranslate(tx, ty, tz);
}
void CCG2019112380������OGL3DDoc::_3DRotate(double angle,
                                            double cx,
                                            double cy,
                                            double cz)  //��ת����ʱ��Ϊ�����ȣ�
{
  return mScene._3DRotate(angle,cx, cy, cz);
}
void CCG2019112380������OGL3DDoc::_3DScale(double sx,
                                           double sy,
                                           double sz)  //����
{
  return mScene._3DScale(sx, sy, sz);
}
void CCG2019112380������OGL3DDoc:: Move3DCamera(double tx,
                                                  double ty)  //Ƶ�ƹ۲촰��
{}
void CCG2019112380������OGL3DDoc:: Zoom3DCamera(
                                         double ratio)  //�����۲촰�ڵ����ű���
{
  return mScene.Zoom3DCamera(ratio);
}
void CCG2019112380������OGL3DDoc::Rotate3DCamera(
    double angle)  //ת��������۲�����ϵ)
{}
void CCG2019112380������OGL3DDoc::setProjection(int mode) {
  return mScene.setProjection(mode);
}

void CCG2019112380������OGL3DDoc::OnUpdate3dfocalDistance(CCmdUI* pCmdUI) {
  // TODO: �ڴ������������û����洦��������
  pCmdUI->Enable(true);
}
int CCG2019112380������OGL3DDoc::FocalDistance() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->FocalDistance();
}
int CCG2019112380������OGL3DDoc::MaterialSelect() {
  CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
  if (!pMainWnd)
    return 0;
  return pMainWnd->MaterialSelect();
}
    //void CCG2019112380������OGL3DDoc::setfocalDis(int dis) {
//  return mScene.setfocalDis(dis);
//}

void CCG2019112380������OGL3DDoc::setEyePos(double eyex,
    double eyey,
    double eyez) {
  return mScene.setEyePos(eyex, eyey, eyez);
}

void CCG2019112380������OGL3DDoc::OnUpdateComboTeapotMaterial(CCmdUI* pCmdUI) {
  // TODO: �ڴ������������û����洦��������
  pCmdUI->Enable(true);
}
