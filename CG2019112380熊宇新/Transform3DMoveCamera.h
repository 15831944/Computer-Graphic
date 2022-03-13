#pragma once
#include "UIEventListener.h"
class Transform3DMoveCamera : public UIEventListener {
  friend class COGL3DView;

 public:
  Transform3DMoveCamera(CGView* pView = nullptr);
  ~Transform3DMoveCamera();

  virtual int GetType();  //命令类型
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //取消Esc
  virtual int Cancel();

 protected:
  Vec2d mPoint;
  bool mLButtonDown;
};
