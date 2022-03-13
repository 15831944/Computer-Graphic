#include "pch.h"
#include "Transform2DTranslate.h"
#include "CGDI2DView.h"

Transform2DTranslate::Transform2DTranslate(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
  mLButtonDown = false;
}
Transform2DTranslate::~Transform2DTranslate() {}
int Transform2DTranslate::GetType()  //命令类型
{
  return cmd2dTranslate;
}
int Transform2DTranslate::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  mStart = mEnd = pos;
  mLButtonDown = true;
  mView->Prompt(_T("请移动图形"));
  return 0;
}
int Transform2DTranslate::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLButtonDown)
    return -1;
  mEnd = pos;
  Vec2d start = mView->ViewPortToWorld(mStart);
  Vec2d end = mView->ViewPortToWorld(mEnd);
  mView->Translate(end.x() - start.x(), end.y() - start.y());
  mStart = mEnd;
  return 0;
}
int Transform2DTranslate::Cancel() {
  if (mView == nullptr)
    return -1;
  m_nStep = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}

int Transform2DTranslate::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLButtonDown)
    return -1;
  mLButtonDown = false;
  return 0;
}