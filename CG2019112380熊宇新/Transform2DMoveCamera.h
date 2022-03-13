#pragma once
#include "UIEventListener.h"
class Transform2DMoveCamera : public UIEventListener {
  friend class CGDI2DView;
 public:
  Transform2DMoveCamera(CGView* pview = nullptr)
      : UIEventListener(pview), mStart(0, 0), mLDown(false) {}
  ~Transform2DMoveCamera() {}
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int GetType() { return cmd2dMoveCamera; }
  virtual int Cancel() { return 0; }

 protected:
  Pos2i mStart;
  bool mLDown;
};
