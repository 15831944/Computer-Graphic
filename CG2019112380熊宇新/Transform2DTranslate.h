#ifndef _TRANSFORM2DTRANSLATE_H_INCLUDE
#define _TRANSFORM2DTRANSLATE_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Transform2DTranslate : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DTranslate(CGView* pView = nullptr);
  ~Transform2DTranslate();

  virtual int GetType();  //��������
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
  bool mLButtonDown;
};

#endif  //_TRANSFORM2DTRANSLATE_H_INCLUDE
