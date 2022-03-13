#include "pch.h"
#include "CG2DClock_BJ.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"


IMPLEMENT_SERIAL(CG2DClock_BJ, CG2DRenderable, 1)
CG2DClock_BJ::CG2DClock_BJ()
    : CG2DRenderable(CString("CG2DClock_BJ")),
      mCenter(0, 0),
      mStart(0, 0),
      mEnd(0, 0) {
  cRadius = 0;
  m_Name.Format(_T("摆钟-%ld"), sID);
  cXRadius = 0;
  cYRadius = 0;
  cdis10 = 0;
  mXRadius = 0;
  mYRadius = 0;
  mRadius = 0;
}
CG2DClock_BJ::CG2DClock_BJ(const Vec2d& mStart,
                           const Vec2d& mEnd,
                           const Vec2d& mDis10)
    : CG2DRenderable(CString("CG2DClock_BJ")), mStart(mStart), mEnd(mEnd) {
  m_Name.Format(_T("摆钟-%ld"), sID);
  mCenter.x() = (mStart.x() + mEnd.x()) / 2;
  mCenter.y() = (mStart.y() + mEnd.y()) / 2;
  mMCSX = mCenter.x();
  mMCSY = mCenter.y();
  mMCSAngleX = 0;
  mMXRatio = 1;
  mMYRatio = 1;
  cStart = WorldtoModel(mStart);
  cEnd = WorldtoModel(mEnd);
  cCenter = WorldtoModel(mCenter);
  cDis10 = WorldtoModel(mDis10);
  cdis10 = sqrt((cDis10.x() - cStart.x()) * (cDis10.x() - cStart.x()) +
                (cDis10.y() - cStart.y()) * (cDis10.y() - cStart.y()));
  //表盘的半径
  cXRadius = sqrt((cEnd.x() - cStart.x()) * (cEnd.x() - cStart.x()) +
                  (cEnd.y() - cStart.y()) * (cEnd.y() - cStart.y())) /
                 2 * cos(dPi / 4) -
             cdis10;
  cYRadius = sqrt((cEnd.x() - cStart.x()) * (cEnd.x() - cStart.x()) +
                  (cEnd.y() - cStart.y()) * (cEnd.y() - cStart.y())) /
                 2 * cos(dPi / 4) -
             cdis10;
  cRadius = cXRadius;
  //长方形
  cRect1.x() = cCenter.x() - cXRadius - cdis10;
  cRect1.y() = cCenter.y() + cYRadius + cdis10;
  cRect2.x() = cCenter.x() + cXRadius + cdis10;
  cRect2.y() = cCenter.y() + cYRadius + cdis10;
  cRect3.x() = cCenter.x() - cXRadius - cdis10;
  cRect3.y() = cCenter.y() - cYRadius - cdis10;
  cRect4.x() = cCenter.x() + cXRadius + cdis10;
  cRect4.y() = cCenter.y() - cYRadius - cdis10;
  //外框
  cFenceLU.x() = cStart.x() + cdis10;
  cFenceLU.y() = cEnd.y();
  cFenceLD.x() = cStart.x() + cdis10;
  cFenceLD.y() = cEnd.y() - 1.3 * abs(cStart.y() - cEnd.y());

  cFenceRU.x() = cStart.x() + abs(cStart.x() - cEnd.x()) - cdis10;
  cFenceRU.y() = cEnd.y() - 1.3 * abs(cStart.y() - cEnd.y());
  cFenceRD.x() = cStart.x() + abs(cStart.x() - cEnd.x()) - cdis10;
  cFenceRD.y() = cEnd.y();
  //钟摆
  cClock1.x() = cStart.x() + 0.5 * abs(cStart.x() - cEnd.x());
  cClock1.y() = cEnd.y();
  cClock2.x() = cStart.x() + 0.5 * abs(cStart.x() - cEnd.x());
  cClock2.y() = cEnd.y() - 1.0 * abs(cStart.y() - cEnd.y());
  cClock3.x() = cStart.x() + 0.5 * abs(cStart.x() - cEnd.x());
  cClock3.y() = cEnd.y() - 1.1 * abs(cStart.y() - cEnd.y());
  //刻度线
  for (int i = 0; i < 60; ++i) {
    cOutScale[i].x() = cCenter.x() + cXRadius * sin(i * 2 * dPi / 60);
    cOutScale[i].y() = cCenter.y() + cXRadius * cos(i * 2 * dPi / 60);
  }
  for (int i = 0; i < 60; ++i) {
    if (i % 5 == 0) {
      cInScale[i].x() = cCenter.x() + 0.89 * cXRadius * sin(i * 2 * dPi / 60);
      cInScale[i].y() = cCenter.y() + 0.89 * cXRadius * cos(i * 2 * dPi / 60);
    } else {
      cInScale[i].x() = cCenter.x() + 0.91 * cXRadius * sin(i * 2 * dPi / 60);
      cInScale[i].y() = cCenter.y() + 0.91 * cXRadius * cos(i * 2 * dPi / 60);
    }
  }
}
CG2DClock_BJ::~CG2DClock_BJ() {}
//序列化
void CG2DClock_BJ::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << cStart.x() << cStart.y() << cEnd.x() << cEnd.y();
  } else {
    ar >> cStart.x() >> cStart.y() >> cEnd.x() >> cEnd.y();
  }
}
void CG2DClock_BJ::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;
  CClientDC dc(pRC->getView());
  //建模坐标系到世界坐标系
  mCenter = ModeltoWorld(cCenter);
  mRect1 = ModeltoWorld(cRect1);
  mRect2 = ModeltoWorld(cRect2);
  mRect3 = ModeltoWorld(cRect3);
  mRect4 = ModeltoWorld(cRect4);
  Vec2d cxradius, cyradius;
  cxradius.x() = cCenter.x() + cXRadius;
  cxradius.y() = cCenter.y();
  cyradius.x() = cCenter.x();
  cyradius.y() = cCenter.y() + cYRadius;
  Vec2d mxradius, myradius;
  mxradius = ModeltoWorld(cxradius);
  myradius = ModeltoWorld(cyradius);
  mXRadius = sqrt((mxradius.x() - mCenter.x()) * (mxradius.x() - mCenter.x()) +
                  (mxradius.y() - mCenter.y()) * (mxradius.y() - mCenter.y()));
  mYRadius = sqrt((myradius.x() - mCenter.x()) * (myradius.x() - mCenter.x()) +
                  (myradius.y() - mCenter.y()) * (myradius.y() - mCenter.y()));
  mFenceLU = ModeltoWorld(cFenceLU);
  mFenceLD = ModeltoWorld(cFenceLD);

  mFenceRU = ModeltoWorld(cFenceRU);
  mFenceRD = ModeltoWorld(cFenceRD);
  mClock1 = ModeltoWorld(cClock1);
  mClock2 = ModeltoWorld(cClock2);
  mClock3 = ModeltoWorld(cClock3);
  for (int i = 0; i < 60; ++i) {
    mOutScale[i] = ModeltoWorld(cOutScale[i]);
    mInScale[i] = ModeltoWorld(cInScale[i]);
  }
  //世界坐标系到设备坐标系
  Vec2d mCircleX, mCircleY;
  mCircleX.x() = mCenter.x() + mXRadius;
  mCircleX.y() = mCenter.y();
  mCircleY.x() = mCenter.x();
  mCircleY.y() = mCenter.y() + mYRadius;
  Vec2i Center, Start, End, RectX, RectY, CircleX, CircleY;
  Center = camera->WorldtoViewPort(mCenter);
  CircleX = camera->WorldtoViewPort(mCircleX);
  CircleY = camera->WorldtoViewPort(mCircleY);
  double XRadius =
      sqrt((Center.x() - CircleX.x()) * (Center.x() - CircleX.x()) +
           (Center.y() - CircleX.y()) * (Center.y() - CircleX.y()));
  double YRadius =
      sqrt((Center.x() - CircleY.x()) * (Center.x() - CircleY.x()) +
           (Center.y() - CircleY.y()) * (Center.y() - CircleY.y()));
  Vec2i Rect1, Rect2, Rect3, Rect4;
  Rect1 = camera->WorldtoViewPort(mRect1);
  Rect2 = camera->WorldtoViewPort(mRect2);
  Rect3 = camera->WorldtoViewPort(mRect3);
  Rect4 = camera->WorldtoViewPort(mRect4);
  Vec2i FenceLU, FenceLD, FenceRU, FenceRD;
  FenceLU = camera->WorldtoViewPort(mFenceLU);
  FenceLD = camera->WorldtoViewPort(mFenceLD);
  FenceRU = camera->WorldtoViewPort(mFenceRU);
  FenceRD = camera->WorldtoViewPort(mFenceRD);
  Vec2i Clock1, Clock2, Clock3;
  Clock1 = camera->WorldtoViewPort(mClock1);
  Clock2 = camera->WorldtoViewPort(mClock2);
  Clock3 = camera->WorldtoViewPort(mClock3);
  Vec2i InScale[60], OutScale[60];
  for (int i = 0; i < 60; ++i) {
    InScale[i] = camera->WorldtoViewPort(mInScale[i]);
    OutScale[i] = camera->WorldtoViewPort(mOutScale[i]);
  }
  CPen pen(PS_SOLID, 2, penColor());
  CPen* pOldPen = dc.SelectObject(&pen);
  if (status() == CGRenderable::statusSelected)  //对象处于选中状态
  {
    CClientDC dc(pRC->getView());
    CPen pen(PS_SOLID, 2, RGB(192, 192, 0));  // penColor()
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SelectStockObject(NULL_BRUSH);
    int oldMode = dc.SetROP2(R2_XORPEN);
    dc.MoveTo(Rect1.x(), Rect1.y());
    dc.LineTo(Rect2.x(), Rect2.y());
    dc.LineTo(Rect4.x(), Rect4.y());
    dc.LineTo(Rect3.x(), Rect3.y());
    dc.LineTo(Rect1.x(), Rect1.y());
    dc.Ellipse(Center.x() - XRadius, Center.y() - YRadius, Center.x() + XRadius,
               Center.y() + YRadius);
    dc.MoveTo(FenceLU.x(), FenceLU.y());
    dc.LineTo(FenceLD.x(), FenceLD.y());
    dc.LineTo(FenceRU.x(), FenceRU.y());
    dc.LineTo(FenceRD.x(), FenceRD.y());
    CTime time = CTime::GetCurrentTime();
    double Radians;
    int chose = timeChose();
    if (chose == 0) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0;
    } else if (chose == 1) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +       
                (double)time.GetSecond() / 3600.0 - 5.0;
    } else if (chose == 2) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0 - 8.0;
    } else {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0 - 13.0;
    }
    Radians = Radians * 2 * dPi / 12.0;
    CPen HourPen(PS_SOLID, 5, RGB(192, 192, 0));  //小时指针
    dc.SelectObject(&HourPen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.3 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.3 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    Radians = (double)time.GetMinute() + (double)time.GetSecond() / 60.0;
    Radians *= 2 * dPi / 60.0;
    CPen MinutePen(PS_SOLID, 3, RGB(192, 192, 0));  //分钟指针
    dc.SelectObject(&MinutePen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.5 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.5 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    Radians = (double)time.GetSecond();
    Radians *= 2 * dPi / 60.0;
    CPen SecondPen(PS_SOLID, 1, RGB(192, 192, 0));  //秒钟指针
    dc.SelectObject(&SecondPen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.7 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.7 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    CPen Pen1(PS_SOLID, 2, RGB(0, 0, 0));
    CPen Pen2(PS_SOLID, 3, RGB(0, 0, 0));
    for (int i = 0; i < 60; ++i) {
      if (i % 5 == 0)
        dc.SelectObject(&Pen2);
      else
        dc.SelectObject(&Pen1);
      dc.MoveTo(InScale[i].x(), InScale[i].y());
      dc.LineTo(OutScale[i].x(), OutScale[i].y());
    }
    //画钟摆
    dc.MoveTo(Clock1.x(), Clock1.y());
    double x = sqrt((Rect2.x() - Rect1.x()) * (Rect2.x() - Rect1.x()) +
                    (Rect2.y() - Rect1.y()) * (Rect2.y() - Rect1.y()));
    double cx = sqrt((cRect2.x() - cRect1.x()) * (cRect2.x() - cRect1.x()) +
                     (cRect2.y() - cRect1.y()) * (cRect2.y() - cRect1.y()));
    double y = sqrt((Rect2.x() - Rect4.x()) * (Rect2.x() - Rect4.x()) +
                    (Rect2.y() - Rect4.y()) * (Rect2.y() - Rect4.y()));
    double clockx2 = cClock2.x();
    double clocky2 = cClock2.y();
    double clockx3 = cClock3.x();
    double clocky3 = cClock3.y();
    double line2 =
        sqrt((cClock1.x() - cClock2.x()) * (cClock1.x() - cClock2.x()) +
             (cClock1.y() - cClock2.y()) * (cClock1.y() - cClock2.y()));
    double line3 =
        sqrt((cClock1.x() - cClock2.x()) * (cClock1.x() - cClock2.x()) +
             (cClock1.y() - cClock2.y()) * (cClock1.y() - cClock2.y())) +
        0.1 * cx;
    int sec = time.GetSecond() % 8;
    Vec2d tmp2, tmp3;
    switch (sec) {
      case 0:
        tmp2.x() = clockx2;
        tmp2.y() = clocky2;
        tmp3.x() = clockx3;
        tmp3.y() = clocky3;
        break;
      case 1:
        tmp2.x() = clockx2 + line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      case 2:
        tmp2.x() = clockx2 + line2 * sin(10 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(10 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(10 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(10 * 2 * dPi / 360));
        break;
      case 3:
        tmp2.x() = clockx2 + line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      case 4:
        tmp2.x() = clockx2;
        tmp2.y() = clocky2;
        tmp3.x() = clockx3;
        tmp3.y() = clocky3;
        break;
      case 5:
        tmp2.x() = clockx2 - line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line2 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        break;
      case 6:
        tmp2.x() = clockx2 - line2 * sin(10 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(10 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line3 * sin(10 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(10 * 2 * dPi / 360));
        break;
      case 7:
        tmp2.x() = clockx2 - line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      default:
        break;
    }
  }
  else 
  {
    dc.MoveTo(Rect1.x(), Rect1.y());
    dc.LineTo(Rect2.x(), Rect2.y());
    dc.LineTo(Rect4.x(), Rect4.y());
    dc.LineTo(Rect3.x(), Rect3.y());
    dc.LineTo(Rect1.x(), Rect1.y());
    dc.Ellipse(Center.x() - XRadius, Center.y() - YRadius, Center.x() + XRadius,
               Center.y() + YRadius);
    dc.MoveTo(FenceLU.x(), FenceLU.y());
    dc.LineTo(FenceLD.x(), FenceLD.y());
    dc.LineTo(FenceRU.x(), FenceRU.y());
    dc.LineTo(FenceRD.x(), FenceRD.y());
    CTime time = CTime::GetCurrentTime();
    double Radians;
    int chose = timeChose();
    if (chose == 0) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0;
    } else if (chose == 1) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0 - 5.0;
    } else if (chose == 2) {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0 - 8.0;
    } else {
      Radians = (double)time.GetHour() + (double)time.GetMinute() / 60.0 +
                (double)time.GetSecond() / 3600.0 - 13.0;
    }
    Radians = Radians * 2 * dPi / 12.0;
    CPen HourPen(PS_SOLID, 5, RGB(0, 0, 0));  //小时指针
    dc.SelectObject(&HourPen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.3 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.3 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    Radians = (double)time.GetMinute() + (double)time.GetSecond() / 60.0;
    Radians *= 2 * dPi / 60.0;
    CPen MinutePen(PS_SOLID, 3, RGB(192, 192, 0));  //分钟指针
    dc.SelectObject(&MinutePen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.5 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.5 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    Radians = (double)time.GetSecond();
    Radians *= 2 * dPi / 60.0;
    CPen SecondPen(PS_SOLID, 1, RGB(255, 0, 0));  //秒钟指针
    dc.SelectObject(&SecondPen);
    dc.MoveTo(Center.x(), Center.y());
    dc.LineTo(
        Center.x() + 0.7 * XRadius * sin(mMCSAngleX * 2 * dPi / 360 + Radians),
        Center.y() - 0.7 * XRadius * cos(mMCSAngleX * 2 * dPi / 360 + Radians));
    CPen Pen1(PS_SOLID, 2, RGB(0, 0, 0));
    CPen Pen2(PS_SOLID, 3, RGB(0, 0, 0));
    for (int i = 0; i < 60; ++i) {
      if (i % 5 == 0)
        dc.SelectObject(&Pen2);
      else
        dc.SelectObject(&Pen1);
      dc.MoveTo(InScale[i].x(), InScale[i].y());
      dc.LineTo(OutScale[i].x(), OutScale[i].y());
    }
    //画钟摆
    dc.MoveTo(Clock1.x(), Clock1.y());
    double x = sqrt((Rect2.x() - Rect1.x()) * (Rect2.x() - Rect1.x()) +
                    (Rect2.y() - Rect1.y()) * (Rect2.y() - Rect1.y()));
    double cx = sqrt((cRect2.x() - cRect1.x()) * (cRect2.x() - cRect1.x()) +
                     (cRect2.y() - cRect1.y()) * (cRect2.y() - cRect1.y()));
    double y = sqrt((Rect2.x() - Rect4.x()) * (Rect2.x() - Rect4.x()) +
                    (Rect2.y() - Rect4.y()) * (Rect2.y() - Rect4.y()));
    double clockx2 = cClock2.x();
    double clocky2 = cClock2.y();
    double clockx3 = cClock3.x();
    double clocky3 = cClock3.y();
    double line2 =
        sqrt((cClock1.x() - cClock2.x()) * (cClock1.x() - cClock2.x()) +
             (cClock1.y() - cClock2.y()) * (cClock1.y() - cClock2.y()));
    double line3 =
        sqrt((cClock1.x() - cClock2.x()) * (cClock1.x() - cClock2.x()) +
             (cClock1.y() - cClock2.y()) * (cClock1.y() - cClock2.y())) +
        0.1 * cx;
    int sec = time.GetSecond() % 8;
    Vec2d tmp2, tmp3;
    switch (sec) {
      case 0:
        tmp2.x() = clockx2;
        tmp2.y() = clocky2;
        tmp3.x() = clockx3;
        tmp3.y() = clocky3;
        break;
      case 1:
        tmp2.x() = clockx2 + line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      case 2:
        tmp2.x() = clockx2 + line2 * sin(10 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(10 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(10 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(10 * 2 * dPi / 360));
        break;
      case 3:
        tmp2.x() = clockx2 + line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 + line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      case 4:
        tmp2.x() = clockx2;
        tmp2.y() = clocky2;
        tmp3.x() = clockx3;
        tmp3.y() = clocky3;
        break;
      case 5:
        tmp2.x() = clockx2 - line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line2 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        break;
      case 6:
        tmp2.x() = clockx2 - line2 * sin(10 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(10 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line3 * sin(10 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(10 * 2 * dPi / 360));
        break;
      case 7:
        tmp2.x() = clockx2 - line2 * sin(5 * 2 * dPi / 360);
        tmp2.y() = clocky2 + (line2 - line2 * cos(5 * 2 * dPi / 360));
        tmp3.x() = clockx3 - line3 * sin(5 * 2 * dPi / 360);
        tmp3.y() = clocky3 + (line3 - line3 * cos(5 * 2 * dPi / 360));
        break;
      default:
        break;
    }
    mClock2 = ModeltoWorld(tmp2);
    mClock3 = ModeltoWorld(tmp3);
    Clock2 = camera->WorldtoViewPort(mClock2);
    Clock3 = camera->WorldtoViewPort(mClock3);
    dc.LineTo(Clock2.x(), Clock2.y());
    dc.Ellipse(Clock3.x() - 0.1 * x, Clock3.y() - 0.1 * y, Clock3.x() + 0.1 * x,
               Clock3.y() + 0.1 * y);
  }
  dc.SelectObject(pOldPen);
}

//图形对象包围盒
ABox2d& CG2DClock_BJ::BoundingABox()  // AABB包围盒，可用于设置
{
  if (boundsDirty()) {
    ComputeBounds();
  }
  return mABox;
}
void CG2DClock_BJ::ComputeBounds()  //计算包围盒
{
  mABox.setNull();  //先清空
  mCenter = ModeltoWorld(cCenter);
  mCenter = ModeltoWorld(cCenter);
  mRect1 = ModeltoWorld(cRect1);
  mRect2 = ModeltoWorld(cRect2);
  mRect3 = ModeltoWorld(cRect3);
  mRect4 = ModeltoWorld(cRect4);
  Vec2d cxradius, cyradius;
  cxradius.x() = cCenter.x() + cXRadius;
  cxradius.y() = cCenter.y();
  cyradius.x() = cCenter.x();
  cyradius.y() = cCenter.y() + cYRadius;
  Vec2d mxradius, myradius;
  mxradius = ModeltoWorld(cxradius);
  myradius = ModeltoWorld(cyradius);
  mXRadius = sqrt((mxradius.x() - mCenter.x()) * (mxradius.x() - mCenter.x()) +
                  (mxradius.y() - mCenter.y()) * (mxradius.y() - mCenter.y()));
  mYRadius = sqrt((myradius.x() - mCenter.x()) * (myradius.x() - mCenter.x()) +
                  (myradius.y() - mCenter.y()) * (myradius.y() - mCenter.y()));
  mFenceLU = ModeltoWorld(cFenceLU);
  mFenceLD = ModeltoWorld(cFenceLD);
  mFenceRU = ModeltoWorld(cFenceRU);
  mFenceRD = ModeltoWorld(cFenceRD);
  mClock1 = ModeltoWorld(cClock1);
  mClock2 = ModeltoWorld(cClock2);
  mClock3 = ModeltoWorld(cClock3);
  mABox.addPoint(mRect1);
  mABox.addPoint(mRect2);
  mABox.addPoint(mRect3);
  mABox.addPoint(mRect4);
  mABox.addPoint(mFenceLD);
  mABox.addPoint(mFenceRU);
  setBoundsDirty(false);
}
//图形对象的几何变换
void CG2DClock_BJ::Translate(double tx, double ty)  //平移
{
  //简单变换，不使用矩阵直接运算
  mMCSX += tx;
  mMCSY += ty;
  setBoundsDirty(true);
}
void CG2DClock_BJ::Rotate(double angle,
                          double cx,
                          double cy)  //旋转（逆时针为正，度）
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  Vec2d tmp2;
  tmp2.x() = mMCSX;
  tmp2.y() = mMCSY;
  Vec3d tmp3 = Vec3d(tmp2);
  tmp3 = operator*(mat, tmp3);
  tmp2 = tmp3.xy();
  mMCSX = tmp2.x();
  mMCSY = tmp2.y();
  mMCSAngleX -= angle;
  setBoundsDirty(true);
}
void CG2DClock_BJ::Scale(double sx, double sy)  //缩放
{
  //简单变换，不使用矩阵直接运算
  mMXRatio *= sx;
  mMYRatio *= sy;
  setBoundsDirty(true);
}
void CG2DClock_BJ::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mMCSY = -mMCSY;
  setBoundsDirty(true);
}
void CG2DClock_BJ::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mMCSX = -mMCSX;
  setBoundsDirty(true);
}
void CG2DClock_BJ::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mMCSX;
  mMCSX = mMCSY;
  mMCSY = t;
  setBoundsDirty(true);
}
void CG2DClock_BJ::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mMCSX;
  mMCSX = -mMCSY;
  mMCSY = -t;
  setBoundsDirty(true);
}
void CG2DClock_BJ::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mMCSX = -mMCSX;
  mMCSY = -mMCSY;
  setBoundsDirty(true);
}

void CG2DClock_BJ::ShearXAxis(double shx)  //沿X轴错切
{
  mCenter.x() = mCenter.x() + shx * mCenter.y();
  setBoundsDirty(true);
}

void CG2DClock_BJ::ShearYAxis(double shy)  //沿Y轴错切
{
  mCenter.y() = mCenter.y() + shy * mCenter.x();
  setBoundsDirty(true);
}

void CG2DClock_BJ::ShearXYAxis(double shx, double shy) {
  Mat3d mat = Mat3d::getShear(shx, shy);
  Vec3d Center = Vec3d(mCenter);
  Center = operator*(mat, Center);
  mCenter = Center.xy();
}

void CG2DClock_BJ::Transform(const Mat3d& mat) {
  Vec2d tmp2;
  tmp2.x() = mMCSX;
  tmp2.y() = mMCSY;
  Vec3d tmp3 = (Vec3d)tmp2;
  tmp3 = operator*(mat, tmp3);
  tmp2 = tmp3.xy();
  mMCSX = tmp2.x();
  mMCSY = tmp2.y();
}

void CG2DClock_BJ::Mirror(Vec2d& v1, Vec2d& v2)  //任意直线对称
{
  Mat3d mat;
  if (v1.x() == v2.x()) {
    double angle = 90;
    mat = Mat3d::getMirror(angle, Vec2d(v1.x(), 0));
  } else {
    double k = (v1.y() - v2.y()) / (v1.x() - v2.x());
    double angle = atan(k);
    if (angle < 0)
      angle += dPi;
    angle = angle / dPi * 180;
    double b = v1.y() - v1.x() * k;
    mat = Mat3d::getMirror(angle, Vec2d(0, b));
  }
  Vec2d tmp2;
  tmp2.x() = mMCSX;
  tmp2.y() = mMCSY;
  Vec3d tmp3 = (Vec3d)tmp2;
  tmp3 = operator*(mat, tmp3);
  tmp2 = tmp3.xy();
  mMCSX = tmp2.x();
  mMCSY = tmp2.y();
}

bool CG2DClock_BJ::Picked(const Vec2d& p, double r)  //是否拾取到
{
  //（给定位置和范围，范围r可以根据需要设为圆半径或正方形边长的一半）
  ComputeBounds();
  ABox2d box(p, r);
  if (mABox.intersects(box))  //如果点在线段包围盒内，进一步判断距离
  {
    //简单通过包围盒实现
    return true;
  }
  return false;
}
