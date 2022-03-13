#pragma once
#include "UIEventListener.h"
class Create2DLineSegment : public UIEventListener {
	friend class CGDI2DView;

 public:
        Create2DLineSegment(CGView* pview=nullptr);
  ~Create2DLineSegment();

  virtual int GetType();  //��������
  virtual int OnLButtonDown(UINT nFlags,const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags,const Pos2i& pos);

  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
};
