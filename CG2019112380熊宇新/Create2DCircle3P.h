#ifndef _CREATE2DCIRCLE3PCircum_H_INCLUDE
#define _CREATE2DCIRCLE3PCircum_H_INCLUDE
#pragma once
#include "UIEventListener.h"
//三点画圆
class Create2DCircle3P : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DCircle3P(CGView* pView = nullptr);
  ~Create2DCircle3P();

  virtual int GetType();  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  Pos2i mCenter;
  double Radius;
  Pos2i mStart;
  Pos2i mMiddle;
  Pos2i mEnd;
  Pos2i Upperleft;
  Pos2i Lowerright;
  int flag = -1;
};
#endif  //_CREATE2DCIRCLE3PCircum_H_INCLUDE