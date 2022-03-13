#include "pch.h"
#include "Transform2DMoveCamera.h"
#include"CG2019112380ÐÜÓîÐÂGDI2DDoc.h"
int Transform2DMoveCamera ::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || mLDown)
    return 0;
  mStart = pos;
  mLDown = true;
  return 0;
}
int Transform2DMoveCamera ::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLDown)
    return 0;
  Vec2i mEnd = pos;
  Vec2d start = mView->ViewPortToWorld(mStart);
  Vec2d end = mView->ViewPortToWorld(mEnd);
  mView->Move2DCamera(-(end.x() - start.x()), -(end.y() - start.y()));
  mView->Invalidate();
  mView->UpdateWindow();
  mStart = mEnd;
  return 0;
}
int Transform2DMoveCamera ::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLDown)
    return 0;
  Vec2i mEnd = pos;
  Vec2d start = mView->ViewPortToWorld(mStart);
  Vec2d end = mView->ViewPortToWorld(mEnd);
  mView->Move2DCamera(-(end.x() - start.x()), -(end.y() - start.y()));
  mView->Invalidate();
  mView->UpdateWindow();
  mLDown = false;
  return 0;
}
