#include "pch.h"
#include "CGDI2DCamera.h"

IMPLEMENT_SERIAL(CGDI2DCamera, CGCamera, 1)
CGDI2DCamera::CGDI2DCamera()
    : CGCamera(CString("CGDI2DCamera")),
      mVCSAngleX(0),
      mVCSX(0),
      mVCSY(0),
      wLeft(0),
      wRight(0),
      wBottom(0),
      wTop(0),
      mNCSAngleX(0),
      mNCSX(0),
      mNCSY(0) {}
CGDI2DCamera::CGDI2DCamera(const CString& name)
    : CGCamera(CString(name)),
      mVCSAngleX(0),
      mVCSX(0),
      mVCSY(0),
      wLeft(0),
      wRight(0),
      wBottom(0),
      wTop(0),
      mNCSAngleX(0),
      mNCSX(0),
      mNCSY(0) {}
void CGDI2DCamera::Serialize(CArchive& ar) {
  CGCamera::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}
//世界坐标系转换到视口（二维）
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p) {
  //此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
  //观察窗口与视口一样的大小。视口与客户区重叠
   //return Vec2i(int(p.x()), int(-p.y())+ mClienRect.height());
  //画布坐标系在客户区中心，x向右，y向上。
  return VirtualEquipmenttoViewPort(WatchtoVirtualEquipment(WorldtoWatch(p)));
}

double CGDI2DCamera::LengthWorldtoViewPort(const double p) {
  return p / HeightFactorWtoV();
}
double CGDI2DCamera::RadWorldtoViewPort(const double p) {
  return p - mVCSAngleX;
}

//视口转换到世界坐标系（二维）
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p) {
  //此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
  //观察窗口与视口一样的大小。视口与客户区重叠
  // return Vec2d(p.x(), double(mClienRect.height())-p.y());
  //画布坐标系在客户区中心，x向右，y向上。
  return WatchtoWorld(VirtualEquipmenttoWatch(ViewPorttoVirtualEquipment(p)));
}

 double CGDI2DCamera::LengthViewPorttoWorld(const double p) {
  return p * HeightFactorWtoV();
}
double CGDI2DCamera::RadViewPorttoWorld(const double p) {
  return p + mVCSAngleX;
}

//世界坐标系转观察坐标系
Vec2d CGDI2DCamera::WorldtoWatch(const Vec2d& p) {
  double x = p.x() - mVCSX;
  double y = p.y() - mVCSY;
  double angle = -mVCSAngleX;
  return Vec2d(x * cos(angle) - y * sin(angle),
               x * sin(angle) + y * cos(angle));
}
//观察坐标系转虚拟设备坐标系
Vec2i CGDI2DCamera::WatchtoVirtualEquipment(const Vec2d& p) {
  return Vec2i(p.x() / WidthFactorWtoV() + 0.5,
               p.y() / HeightFactorWtoV() + 0.5);
}
//虚拟设备坐标系转设备坐标系
Vec2i CGDI2DCamera::VirtualEquipmenttoViewPort(const Vec2i& p) {
  return Vec2i(p.x(), (nvTop - nvBottom) - p.y());
}

//设备坐标系转虚拟设备坐标系
Vec2i CGDI2DCamera::ViewPorttoVirtualEquipment(const Vec2i& p) {
  return Vec2i(p.x(), (nvTop - nvBottom) - p.y());
}
//虚拟设备坐标系转观察坐标系
Vec2d CGDI2DCamera::VirtualEquipmenttoWatch(const Vec2i& p) {
  return Vec2d(p.x() * WidthFactorWtoV(), p.y() * HeightFactorWtoV());
}
//观察坐标系转世界坐标系
Vec2d CGDI2DCamera::WatchtoWorld(const Vec2d& p) {
  return Vec2d(p.x() * cos(mVCSAngleX) - p.y() * sin(mVCSAngleX) + mVCSX,
               p.x() * sin(mVCSAngleX) + p.y() * cos(mVCSAngleX) + mVCSY);
}

// 观察（二维）（注意在实现中要保持与视口高宽比一致）
void CGDI2DCamera::Move2DCamera(double tx, double ty)//平移观察窗口
{
	mVCSX += tx;
	mVCSY += ty;
}
void CGDI2DCamera::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt)//观察窗口左下角、右上角
{

}
void CGDI2DCamera::Zoom2DCamera(double ratio)//给定观察窗口的缩放比例（
{
	wLeft *= ratio;
	wRight *= ratio;       
	wTop *= ratio;
	wBottom *= ratio;
}
void CGDI2DCamera::Rotate2DCamera(double angle)//转动相机（观察坐标系)
{
	mVCSAngleX += angle;
}

 //设置虚拟设备坐标系
void CGDI2DCamera::setNCS(double x, double y, double angle) {
  mNCSX = x;
  mNCSY = y;
  mNCSAngleX = angle;
}

//设置虚拟设备视口
void CGDI2DCamera::setNCSViewPort(double left,
                                  double bottom,
                                  double right,
                                  double top) {
  //保持原比例大小
  static bool init = false;
  double lastHight = nvTop - nvBottom;
  double lastWidth = nvRight - nvLeft;
  nvLeft = std::min(left, right);
  nvRight = std::max(left, right);
  nvBottom = std::min(bottom, top);
  nvTop = std::max(bottom, top);
  double nowHight = nvTop - nvBottom;
  double nowWidth = nvRight - nvLeft;
  if (!init) {
    init = true;
    return;
  }
  wRight *= nowWidth / lastWidth;
  wLeft *= nowWidth / lastWidth;
  wTop *= nowHight / lastHight;
  wBottom *= nowHight / lastHight;
}
//设置观察坐标系
void CGDI2DCamera::setVCS(double x, double y, double angle) {
  mVCSX = x;
  mVCSY = y;
  mVCSAngleX = angle;
}
//设置观察窗口
void CGDI2DCamera::setVCSWindow(double left,
                                double bottom,
                                double right,
                                double top) {
  wLeft = std::min(left, right);
  wRight = std::max(left, right);
  wBottom = std::min(bottom, top);
  wTop = std::max(bottom, top);
}
//观察窗口宽度与视口宽度的比例?
double CGDI2DCamera::WidthFactorWtoV() const {
  return (wRight - wLeft) / (nvRight - nvLeft);
}
//观察窗口高度与视口高度的比例?
double CGDI2DCamera::HeightFactorWtoV() const {
  return (wTop - wBottom) / (nvTop - nvBottom);
}