#ifndef _CREATE2DPolyline_H_INCLUDE
#define _CREATE2DPolyline_H_INCLUDE
#pragma once
#include "UIEventListener.h"

class Create2DPolyline : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DPolyline(CGView* pView = nullptr);
  ~Create2DPolyline();

  virtual int GetType();  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int OnRButtonDown(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  CPoint m_ArrayPoint[255];  //记录每个折线点
  int m_PolyCount;           //折线的点的计数
  CPoint m_ptPolyFirst;      //折线中第一个点
  CPoint m_ptPolyLast;       //折线中最后一个点
  CPoint m_PointOld;         //橡皮线中的最后一个点
};
#endif  //_CREATE2DPolyLine_H_INCLUDE
