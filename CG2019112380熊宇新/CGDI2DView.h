#ifndef _CGDI2DVIEW_H_INCLUDED
#define _CGDI2DVIEW_H_INCLUDED
#include "CGView.h"
class CGDI2DView : public CGView {
  DECLARE_DYNCREATE(CGDI2DView)
 protected:  // 仅从序列化创建
  CGDI2DView();
  // 操作
 public:
  // 实现
 public:
  virtual ~CGDI2DView();
  // 重写
 public:
  virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
  //设置默认视口参数
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //渲染场景
  virtual bool RenderScene();
};
#endif  //_CGDI2DVIEW_H_INCLUDE