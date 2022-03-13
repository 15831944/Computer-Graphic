#ifndef _COGL3DRENDERCONTEXT_H_INCLUDED
#define _COGL3DRENDERCONTEXT_H_INCLUDED
#include "CGRenderContext.h"
class COGL3DView;
class COGL3DRenderContext : public CGRenderContext {
 public:
  COGL3DRenderContext();
  COGL3DRenderContext(COGL3DView* pView);
  virtual ~COGL3DRenderContext();
  //�Զ�������
  virtual bool InitRenderContext();
  virtual void SetupRenderContext();
  virtual void Ready();
  virtual void Finish();
  //��������
  void Shading(bool shading);
  bool IsShading();
  void Lighting(bool lighting);
  bool IsLighting();

 protected:
  void ClearBackground();
  void OnShading();
  bool SetupPixelFormat(void);
  void SetLogicalPalette(void);

 protected:
  bool bShading;              //�Ƿ�ʹ�ò�������
  bool bLighting;             //�Ƿ����ù���
  HPALETTE mPalette;          // OpenGL��ɫ��
  COLORREF mBackgroundColor;  //������ɫ
  double mBackgroundDepth;    //�������
};

#endif  //_COGL3DRENDERCONTEXT_H_INCLUDED