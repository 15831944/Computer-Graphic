#include "pch.h"
#include "Transform2DRotateOrigin.h"
#include "CGDI2DView.h"

Transform2DRotateOrigin::Transform2DRotateOrigin(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
  mLButtonDown = false;
}
Transform2DRotateOrigin::~Transform2DRotateOrigin() {}
int Transform2DRotateOrigin::GetType()  //命令类型
{
  return cmd2dRotateOrigin;
}
int Transform2DRotateOrigin::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  mLButtonDown = true;
  mStart = mEnd = pos;
  mView->Prompt(_T("请旋转图形"));
  return 0;
}
int Transform2DRotateOrigin::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || !mLButtonDown)
    return -1;
  mEnd = pos;
  Vec2d start = mView->ViewPortToWorld(mStart);
  Vec2d end = mView->ViewPortToWorld(mEnd);
  Vec2d center = {0, 0};
  double Angle = GetAngle(center, start, end);
  mView->Rotate(Angle, 0, 0);
  mStart = mEnd;
  return 0;
}
int Transform2DRotateOrigin::Cancel() {
  if (mView == nullptr)
    return -1;
  m_nStep = 0;
  mView->Prompt(_T("就绪"));
  return 0;
}

double Transform2DRotateOrigin::GetAngle(Vec2d& mCenter,
                                         Vec2d& mStart,
                                         Vec2d& mEnd) {
  double ma_x = mStart.x() - mCenter.x();
  double ma_y = mStart.y() - mCenter.y();
  double mb_x = mEnd.x() - mCenter.x();
  double mb_y = mEnd.y() - mCenter.y();
  double v1 = (ma_x * mb_x) + (ma_y * mb_y);
  double ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
  double mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
  double cosM = v1 / (ma_val * mb_val);
  if (cosM < -1) {
    cosM = -1;
  } else if (cosM > 1) {
    cosM = 1;
  }
  double angleAMB = acos(cosM) * 180 / dPi;
  Vec2d lineFirst(mStart.x() - mCenter.x(), mStart.y() - mCenter.y());
  Vec2d lineSecond(mEnd.x() - mCenter.x(), mEnd.y() - mCenter.y());
  bool isClockwise =
      lineFirst.x() * lineSecond.y() - lineSecond.x() * lineFirst.y() < 0;
  if (isClockwise) {
    angleAMB = 360 - angleAMB;
  }
  return angleAMB;
}

int Transform2DRotateOrigin::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  mLButtonDown = false;
  return 0;
}
