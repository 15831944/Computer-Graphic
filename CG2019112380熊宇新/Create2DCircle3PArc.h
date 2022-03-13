#ifndef _CREATE2DCIRCLE3PARC_H_INCLUDE
#define _CREATE2DCIRCLE3PARC_H_INCLUDE
#pragma once
#include "UIEventListener.h"
//三点圆弧
class Create2DCircle3PArc : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DCircle3PArc(CGView* pView = nullptr);
  ~Create2DCircle3PArc();

  virtual int GetType();  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  Pos2i mCenter;
  Pos2i mStart;
  Pos2i mEnd;
  double Radius;
  Pos2i Upperleft;
  Pos2i Lowerright;
};
#endif  //_CREATE2DCIRCLE3PARC_H_INCLUDE
