#ifndef _RECTCLIP2DRENDERABLE_H_INCLUDED
#define _RECTCLIP2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
class Transform2DClip : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DClip(CGView* pview = nullptr);
  ~Transform2DClip();
  virtual int GetType();  //命令类型
  //鼠标事件( 都给出默认实现，派生类根据需要重写)
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
};
#endif  //_RECTCLIP2DRENDERABLE_H_INCLUDED
