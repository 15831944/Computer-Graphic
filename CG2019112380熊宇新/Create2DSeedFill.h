#pragma once
#include "UIEventListener.h"
#include"CGView.h"
class Create2DSeedFill : public UIEventListener {
 public:
  Create2DSeedFill(CGView* pview = nullptr)
      : UIEventListener(pview), mSeed(0, 0) {
    m_nStep = 0;
    mView->Prompt(_T("请输入要填充的种子点"));
  }
  ~Create2DSeedFill();
  virtual int GetType() { return cmd2dSeedFill; }
  virtual int OnLButtonDown(UINT nF1ags, const Pos2i& pos);
  virtual int Cancel();

 protected:
  Vec2i mSeed;
};