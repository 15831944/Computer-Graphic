#ifndef _TRANSFORM2DROTATEORIGIN_H_INCLUDE
#define _TRANSFORM2DROTATEORIGIN_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Transform2DRotateOrigin : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DRotateOrigin(CGView* pView = nullptr);
  ~Transform2DRotateOrigin();

  virtual int GetType();  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮线
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();
  //获取三个点形成的角度
  double GetAngle(Vec2d& mCenter, Vec2d& mStart, Vec2d& mEnd);

 protected:
  Pos2i mStart;
  Pos2i mEnd;
  bool mLButtonDown;
};

#endif  //_TRANSFORM2DROTATEORIGIN_H_INCLUDE