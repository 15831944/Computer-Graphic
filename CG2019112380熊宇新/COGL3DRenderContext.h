#ifndef _COGL3DRENDERCONTEXT_H_INCLUDED
#define _COGL3DRENDERCONTEXT_H_INCLUDED
#include "CGRenderContext.h"
class COGL3DView;
class COGL3DRenderContext : public CGRenderContext {
 public:
  COGL3DRenderContext();
  COGL3DRenderContext(COGL3DView* pView);
  virtual ~COGL3DRenderContext();
  //自定义内容
  virtual bool InitRenderContext();
  virtual void SetupRenderContext();
  virtual void Ready();
  virtual void Finish();
  //辅助函数
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
  bool bShading;              //是否使用材质属性
  bool bLighting;             //是否启用光照
  HPALETTE mPalette;          // OpenGL调色板
  COLORREF mBackgroundColor;  //背景颜色
  double mBackgroundDepth;    //背景深度
};

#endif  //_COGL3DRENDERCONTEXT_H_INCLUDED