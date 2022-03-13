#include "pch.h"
#include "CG2DRenderable.h"

IMPLEMENT_SERIAL(CG2DRenderable, CGRenderable, 1)
CG2DRenderable::CG2DRenderable()
    : CGRenderable(CString("CG2DRenderable")),
      mPenColor(RGB(0, 0, 0)),
      mPenWidth(1),
      mPenStyle(PS_SOLID),
      mBrushColor(RGB(0, 0, 0)),
      mBrushIndex(-1)
{
}
CG2DRenderable::CG2DRenderable(const CString& name)
    : CGRenderable(CString(name)),
      mPenColor(RGB(0, 0, 0)),
      mPenWidth(1),
      mPenStyle(PS_SOLID),
      mBrushColor(RGB(0, 0, 0)),
      mBrushIndex(-1)
{
}
CG2DRenderable::~CG2DRenderable() {}
//序列化
void CG2DRenderable::Serialize(CArchive& ar) {
  CGRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mPenColor << mPenWidth << mPenStyle << mBrushColor << mBrushIndex
       << mBrushUse;
  } else {
    ar >> mPenColor >> mPenWidth >> mPenStyle >> mBrushColor >> mBrushIndex >>
        mBrushUse;
  }
}
void CG2DRenderable::setPenColor(COLORREF color) {
  mPenColor = color;
}
COLORREF CG2DRenderable::penColor() const {
  return mPenColor;
}
void CG2DRenderable::setPenWidth(int width) {
  mPenWidth = width;
}
int CG2DRenderable::penWidth() const {
  return mPenWidth;
}
void CG2DRenderable::setPenStyle(int style) {
  mPenStyle = style;
}
int CG2DRenderable::penStyle() const {
  return mPenStyle;
}
void CG2DRenderable::setBrushColor(COLORREF color) {
  mBrushColor = color;
}
COLORREF CG2DRenderable::brushColor() const {
  return mBrushColor;
}
void CG2DRenderable::setBrushIndex(int index) {
  mBrushIndex = index;
}
int CG2DRenderable::brushIndex() const {
  return mBrushIndex;
}
void CG2DRenderable::setTimeChose(int choice) {
  mTimeChose = choice;
}
int CG2DRenderable::timeChose() const{
  return mTimeChose;
}
void CG2DRenderable::Render(CGRenderContext* pRC) {
  //派生类中实现
}
void CG2DRenderable::setBrushUse(bool use) {
  mBrushUse = use;
}
bool CG2DRenderable::brushUse() const {
  return mBrushUse;
}
//图形对象包围盒
ABox2d& CG2DRenderable::BoundingABox()  // AABB包围盒，可用于设置
{
  if (boundsDirty()) {
    ComputeBounds();
  }
  return mABox;
}
void CG2DRenderable::ComputeBounds()  //计算包围盒，需要在派生类中实现
{
  //派生类中实现，然后要调用如下函数
  setBoundsDirty(false);
}
//世界坐标系转换到建模坐标系
Vec2d CG2DRenderable::WorldtoModel(const Vec2d& p) {
  Vec3d tmp = Vec3(p);
  Mat3d T1 = Mat3d::getTranslation(Vec2d(-mMCSX, -mMCSY));
  Mat3d T2 = Mat3d::getRotation(mMCSAngleX, Vec2d(0, 0));
  Mat3d T3 = Mat3d::getScaling(1 / mMXRatio, 1 / mMYRatio);
  Mat3d T = operator*(T3, operator*(T2, T1));
  tmp = operator*(T, tmp);
  Vec2d ans = tmp.xy();
  return ans;
}

//建模坐标系转换到世界坐标系
Vec2d CG2DRenderable::ModeltoWorld(const Vec2d& p) {
  Vec3d tmp = Vec3(p);
  Mat3d T1 = Mat3d::getTranslation(Vec2d(mMCSX, mMCSY));
  Mat3d T2 = Mat3d::getRotation(-mMCSAngleX, Vec2d(mMCSX, mMCSY));
  Vec2d c, ref;
  c.x() = mMXRatio;
  c.y() = mMYRatio;
  ref.x() = mMCSX;
  ref.y() = mMCSY;
  Mat3d T3 = Mat3d::getScaling(c, ref);
  Mat3d T = operator*(T3, operator*(T2, T1));
  tmp = operator*(T, tmp);
  Vec2d ans = tmp.xy();
  return ans;
}