#pragma once
#include "UIEventListener.h"
class Create2DRay : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DRay(CGView* pview = nullptr);
  ~Create2DRay();

  virtual int GetType();  //√¸¡Ó¿‡–Õ
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);

  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
};
