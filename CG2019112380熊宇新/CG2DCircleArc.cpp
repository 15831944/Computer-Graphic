#include "pch.h"
#include "CG2DCircleArc.h"
#include <cmath>
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DScene.h"
#include "CGDI2DView.h"

IMPLEMENT_SERIAL(CG2DCircleArc, CG2DRenderable, 1)
CG2DCircleArc::CG2DCircleArc()
    : CG2DRenderable(CString("CG2DCircleArc")),
      mCenter(0, 0),
      mStart(0, 0),
      mEnd(0, 0) {}
CG2DCircleArc::CG2DCircleArc(const Vec2d& mCenter,
                             const Vec2d& mStart,
                             const Vec2d& mEnd,
                             bool d)
    : CG2DRenderable(CString("CG2DCircleArc")),
      mCenter(mCenter),
      mStart(mStart),
      mEnd(mEnd) {
  direction = d;
  m_Name.Format(_T("圆弧-%ld"), sID);
  mRadius = sqrt((mStart.x() - mCenter.x()) * (mStart.x() - mCenter.x()) +
                (mStart.y() - mCenter.y()) * (mStart.y() - mCenter.y()));
  XRadius = mRadius;
  YRadius = mRadius;
}
CG2DCircleArc::~CG2DCircleArc() {}
//序列化
void CG2DCircleArc::Serialize(CArchive& ar) {
  CG2DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mCenter.x() << mCenter.y() << mStart.x() << mStart.y() << mEnd.x()
       << mEnd.y();
  } else {
    ar >> mCenter.x() >> mCenter.y() >> mStart.x() >> mStart.y() >> mEnd.x() >>
        mEnd.y();
  }
}
void CG2DCircleArc::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(CGDI2DView)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr)
    return;

  Vec2i Center = camera->WorldtoViewPort(mCenter);
  Vec2i Start = camera->WorldtoViewPort(mStart);
  Vec2i End = camera->WorldtoViewPort(mEnd);
  Vec2i Upperleft;
  Vec2i Lowerright;
  CClientDC dc(pRC->getView());
  CPen pen(penStyle(), penWidth(), penColor());
  CPen* pOldPen = dc.SelectObject(&pen);
  if (direction)
    dc.SetArcDirection(AD_CLOCKWISE);
  else
    dc.SetArcDirection(AD_COUNTERCLOCKWISE);

  if (status() == CGRenderable::statusSelected)  //对象处于选中状态
  {
    CClientDC dc(pRC->getView());
    CPen pen(penStyle(), penWidth(), RGB(192, 192, 0));  // penColor()
    CPen* pOldPen = dc.SelectObject(&pen);
    int oldMode = dc.SetROP2(R2_XORPEN);
    if (direction)
      dc.SetArcDirection(AD_CLOCKWISE);
    else
      dc.SetArcDirection(AD_COUNTERCLOCKWISE);
    dc.Arc(Center.x() - (int)(XRadius + 0.5), Center.y() - (int)(YRadius + 0.5),
           Center.x() + (int)(XRadius + 0.5), Center.y() + (int)(YRadius + 0.5),
           Start.x(), Start.y(), End.x(), End.y());
    dc.SelectObject(pOldPen);
    dc.SetROP2(oldMode);
  } else {
    dc.Arc(Center.x() - (int)(XRadius + 0.5), Center.y() - (int)(YRadius + 0.5),
           Center.x() + (int)(XRadius + 0.5), Center.y() + (int)(YRadius + 0.5),
           Start.x(), Start.y(), End.x(), End.y());
  }
  dc.SelectObject(pOldPen);
}
void CG2DCircleArc::ComputeBounds()  //计算包围盒
{
  mABox.setNull();  //先清空
  Vec2d mUpperleft, mLowerright;
  mUpperleft.x() = mCenter.x() - (int)(XRadius + 0.5);
  mUpperleft.y() = mCenter.y() - (int)(YRadius + 0.5);
  mLowerright.x() = mCenter.x() + (int)(XRadius + 0.5);
  mLowerright.y() = mCenter.y() + (int)(YRadius + 0.5);
  mABox.addPoint(mUpperleft);
  mABox.addPoint(mLowerright);
  setBoundsDirty(false);
}
//图形对象的几何变换
void CG2DCircleArc::Translate(double tx, double ty)  //平移
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() += tx;
  mCenter.y() += ty;
  mStart.x() += tx;
  mStart.y() += ty;
  mEnd.x() += tx;
  mEnd.y() += ty;
  setBoundsDirty(true);
}
void CG2DCircleArc::Rotate(double angle,
                           double cx,
                           double cy)  //旋转（逆时针为正，度）
{
  //使用变换矩阵实现
  Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
  Vec3d Center = Vec3d(mCenter);
  Center = operator*(mat, Center);
  mCenter = Center.xy();
  Vec3d Start = Vec3d(mStart);
  Start = operator*(mat, Start);
  mStart = Start.xy();
  Vec3d End = Vec3d(mEnd);
  End = operator*(mat, End);
  mEnd = End.xy();
  setBoundsDirty(true);
}
void CG2DCircleArc::Scale(double sx, double sy)  //缩放
{
  //简单变换，不使用矩阵直接运算
  XRadius = XRadius * sx;
  YRadius = YRadius * sy;
  mCenter.x() *= sx;
  mCenter.y() *= sy;
  mStart.x() *= sx;
  mStart.y() *= sy;
  mEnd.x() *= sx;
  mEnd.y() *= sy;
  setBoundsDirty(true);
}
void CG2DCircleArc::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.y() = -mCenter.y();
  mStart.y() = -mStart.y();
  mEnd.y() = -mEnd.y();
  direction = !direction;
  setBoundsDirty(true);
}
void CG2DCircleArc::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() = -mCenter.x();
  mStart.x() = -mStart.x();
  mEnd.x() = -mEnd.x();
  direction = !direction;
  setBoundsDirty(true);
}
void CG2DCircleArc::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mCenter.x();
  mCenter.x() = mCenter.y();
  mCenter.y() = t;
  t = mStart.x();
  mStart.x() = mStart.y();
  mStart.y() = t;
  t = mEnd.x();
  mEnd.x() = mEnd.y();
  mEnd.y() = t;
  direction = !direction;
  setBoundsDirty(true);
}
void CG2DCircleArc::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  double t = mCenter.x();
  mCenter.x() = -mCenter.y();
  mCenter.y() = -t;
  t = mStart.x();
  mStart.x() = -mStart.y();
  mStart.y() = -t;
  t = mEnd.x();
  mEnd.x() = -mEnd.y();
  mEnd.y() = -t;
  direction = !direction;
  setBoundsDirty(true);
}
void CG2DCircleArc::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //简单变换，不使用矩阵直接运算
  mCenter.x() = -mCenter.x();
  mCenter.y() = -mCenter.y();
  mStart.x() = -mStart.x();
  mStart.y() = -mStart.y();
  mEnd.x() = -mEnd.x();
  mEnd.y() = -mEnd.y();
  setBoundsDirty(true);
}

void CG2DCircleArc::Transform(const Mat3d& mat) {
  Vec3d Center = (Vec3d)mCenter;
  Center = operator*(mat, Center);
  mCenter = Center.xy();
  Vec3d Start = (Vec3d)mStart;
  Start = operator*(mat, Start);
  mStart = Start.xy();
  Vec3d End = (Vec3d)mEnd;
  End = operator*(mat, End);
  mEnd = End.xy();
}