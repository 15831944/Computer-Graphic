#include "pch.h"
#include "Transform2DRotateCamera.h"
#include"CG2019112380熊宇新GDI2DDoc.h"
double TC_GetAngle(Vec2d cen, Vec2d first, Vec2d second) {
  //计算角度
  double ma_x = first.x() - cen.x();
  double ma_y = first.y() - cen.y();
  double mb_x = second.x() - cen.x();
  double mb_y = second.y() - cen.y();
  double v1 = (ma_x * mb_x) + (ma_y * mb_y);
  double ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
  double mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
  double cosM = v1 / (ma_val * mb_val);
  if (cosM < -1) {
    cosM = -1;
  } else if (cosM > 1) {
    cosM = 1;
  }
  double angleAMB = acos(cosM);

  //计算两条线向量的顺逆时针方向
  Vec2d lineFirst(first.x() - cen.x(), first.y() - cen.y());
  Vec2d lineSecond(second.x() - cen.x(), second.y() - cen.y());
  bool isClockwise =
      lineFirst.x() * lineSecond.y() - lineSecond.x() * lineFirst.y() < 0;
  if (isClockwise) {
    angleAMB = dPi + dPi - angleAMB;
  }
  return angleAMB;
}
 int Transform2DRotateCamera ::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || mLDown)
    return 0;
  mStart = pos;
  mLDown = true;
  return 0;
}
int Transform2DRotateCamera ::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLDown)
    return 0;
  Vec2i mEnd = pos;
  CRect rect;
  mView->GetClientRect(rect);
  mView->Rotate2DCamera(
      -TC_GetAngle(Vec2d(0, 0), Vec2d(mStart.x(), rect.Height() - mStart.y()),
                   Vec2d(mEnd.x(), rect.Height() - mEnd.y())));
  mView->Invalidate();
  mView->UpdateWindow();
  mStart = mEnd;
  return 0;
}
int Transform2DRotateCamera ::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLDown)
    return 0;
  Vec2i mEnd = pos;
  CRect rect;
  mView->GetClientRect(rect);
  mView->Rotate2DCamera(
      -TC_GetAngle(Vec2d(0, 0), Vec2d(mStart.x(), rect.Height() - mStart.y()),
                   Vec2d(mEnd.x(), rect.Height() - mEnd.y())));
  mView->Invalidate();
  mView->UpdateWindow();
  mLDown = false;
  return 0;
}