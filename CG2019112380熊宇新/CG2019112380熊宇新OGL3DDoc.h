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

// CG2019112380������OGL3DDoc.h: CCG2019112380������OGL3DDoc ��Ľӿ�
//

#pragma once
#include "CG3DRenderable.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
class CCG2019112380������OGL3DDoc : public CDocument {
 protected:  // �������л�����
  CCG2019112380������OGL3DDoc() noexcept;
  DECLARE_DYNCREATE(CCG2019112380������OGL3DDoc)
  // ����
 public:
  //��ʾ��������
  COGL3DScene* GetScene() { return &mScene; }

 protected:
  //�����ĳ���
  COGL3DScene mScene;
  // ����
 public:
  //����Ĭ���ӿڲ������ٶ�������ʾͼ�ε�ֻ��һ��View��
  bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //��Ⱦ������ָ���ͻ���
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

  void _3DTranslate(double tx, double ty, double tz);  //ƽ��
  void _3DRotate(double angle,
                 double cx,
                 double cy,
                 double cz);  //��ת����ʱ��Ϊ�����ȣ�
  void _3DScale(double sx, double sy, double sz);  //����
  virtual void Move3DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom3DCamera(double ratio);  //�����۲촰�ڵ����ű���
  virtual void Rotate3DCamera(double angle);  //ת��������۲�����ϵ)
  virtual void setProjection(int mode);
  int FocalDistance();
  int MaterialSelect();
  virtual void setEyePos(double eyex, double eyey, double eyez);
  //virtual void setfocalDis(int dis);
  CGRenderable* CCG2019112380������OGL3DDoc::RenderableSelectedByName(
      const CString& name) {
    mScene.RenderableUnselectAll();  //�˴�ֻʵ�ֵ�ѡ
    return mScene.RenderableSelectedByName(name);
  }
#ifdef SHARED_HANDLERS
  virtual void InitializeSearchContent();
  virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  // SHARED_HANDLERS

  // ʵ��
 public:
  virtual ~CCG2019112380������OGL3DDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:
  // ���ɵ���Ϣӳ�亯��
 protected:
  DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
  // ����Ϊ����������������������ݵ� Helper ����
  void SetSearchContent(const CString& value);
#endif  // SHARED_HANDLERS
 public:
  afx_msg void OnUpdateDraw3dmode(CCmdUI* pCmdUI);
  afx_msg void OnDraw3dmode();
  afx_msg void OnUpdate3dfocalDistance(CCmdUI* pCmdUI);
  afx_msg void OnUpdateComboTeapotMaterial(CCmdUI* pCmdUI);
};
