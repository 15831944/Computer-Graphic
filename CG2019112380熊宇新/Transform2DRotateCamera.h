#pragma once
#include "UIEventListener.h"
class Transform2DRotateCamera : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DRotateCamera (CGView* pview = nullptr)
      : UIEventListener(pview), mStart(0, 0), mLDown(false) {}
  ~Transform2DRotateCamera () {}
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int GetType() { return cmd2dRotateCamera; }
  virtual int Cancel() { return 0; }

 protected:
  Pos2i mStart;
  bool mLDown;
};
