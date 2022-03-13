#ifndef _CREATE2DREGULARPOLYGON_H_INCLUDE
#define _CREATE2DREGULARPOLYGON_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Create2DRegularPolygon : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DRegularPolygon(CGView* pView = nullptr);
  ~Create2DRegularPolygon();

  virtual int GetType();  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  CPoint m_ArrayPoint[255];  //记录每个折线点
  int m_PolyCount;           //折线的点的计数
  CPoint mCenter;            //正多边形最中间的点
  double angle;
  int flag;
};

#endif  //_CREATE2DREGULARPOLYGON_H_INCLUDE