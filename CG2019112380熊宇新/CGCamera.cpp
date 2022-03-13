#include "pch.h"
#include "CGCamera.h"

IMPLEMENT_SERIAL(CGCamera, CGObject, 1)
CGCamera::CGCamera() : CGObject(CString("CGCamera")) {}
CGCamera::CGCamera(const CString& name) : CGObject(CString(name)) {}
void CGCamera::Serialize(CArchive& ar) {
  CGObject::Serialize(ar);
  mViewPort.Serialize(ar);
  if (ar.IsStoring()) {
    ar << mClienRect.minCorner().x() << mClienRect.minCorner().y()
       << mClienRect.maxCorner().x() << mClienRect.maxCorner().y();
  } else {
    ar >> mClienRect.minCorner().x() >> mClienRect.minCorner().y() >>
        mClienRect.maxCorner().x() >> mClienRect.maxCorner().y();
  }
}
void CGCamera::setViewPortBox(int xl, int yb, int xr, int yt) {
  mViewPort.set(xl, yb, xr, yt);
}
void CGCamera::setViewPort(const CGViewPort& vp) {
  //要保证xl<xr, yb<yt
  mViewPort.set(vp.box().minCorner().x(), vp.box().minCorner().y(),
                vp.box().maxCorner().x(), vp.box().maxCorner().y());
  //是否要保持与观察窗口的等比例？
}
void CGCamera::setClientRect(int xl, int yb, int xr, int yt) {
  //要保证xl<xr, yb<yt
  if (xl < xr) {
    mClienRect.minCorner().x() = xl;
    mClienRect.maxCorner().x() = xr;
  } else {
    mClienRect.minCorner().x() = xr;
    mClienRect.maxCorner().x() = xl;
  }
  if (yb < yt) {
    mClienRect.minCorner().y() = yb;
    mClienRect.maxCorner().y() = yt;
  } else {
    mClienRect.minCorner().y() = yt;
    mClienRect.maxCorner().y() = yb;
  }
}
void CGCamera::setClientRect(const ABox2i& rc) {
  mClienRect = rc;
}
//世界坐标系转换到视口（二维）
Vec2i CGCamera::WorldtoViewPort(const Vec2d& p) {
  //派生类中实现
  return Vec2i(0, 0);
}
double CGCamera::LengthWorldtoViewPort(const double p) {
  //派生类中实现
  return 0;
}
double CGCamera::RadWorldtoViewPort(const double p) {
  //派生类中实现
  return 0;
}
//视口转换到世界坐标系（二维）
Vec2d CGCamera::ViewPorttoWorld(const Vec2i& p) {
  //派生类中实现
  return Vec2d(0, 0);
}
double CGCamera::LengthViewPorttoWorld(const double p) {
  //派生类中实现
  return 0;
}
double CGCamera::RadViewPorttoWorld(const double p) {
  //派生类中实现
  return 0;
}
//设置虚拟设备坐标系
void CGCamera::setNCS(double x, double y, double angle) {
  //派生类中实现
}
    //设置虚拟设备视口
void CGCamera::setNCSViewPort(double left,
                             double bottom,
                             double right,
                             double top) {
  //派生类中实现
}
//设置观察坐标系
void CGCamera::setVCS(double x, double y, double angle) {
  //派生类中实现
}
//设置观察窗口
void CGCamera::setVCSWindow(double left,
                            double bottom,
                            double right,
                            double top) {
  //派生类中实现
}
//观察窗口宽度与视口宽度的比例？
double CGCamera::WidthFactorWtoV() const {
  //派生类中实现
  return 1.0;  //默认观察窗口宽度与视口宽度相同
}
//观察窗口高度与视口高度的比例？
double CGCamera::HeightFactorWtoV() const {
  //派生类中实现
  return 1.0;  //默认观察窗口高度与视口高度相同
}
//观察（二维）（保持与视口高宽比一致）
void CGCamera::Move2DCamera(double tx, double ty)  //频移观察窗口
{
  //派生类中实现
}
void CGCamera::Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt)  //观察窗口左下角、右上角
{
  //派生类中实现
}
void CGCamera::Zoom2DCamera(double ratio)  //给定观察窗口的缩放比例（）
{
  //派生类中实现
}
void CGCamera::Rotate2DCamera(double angle)  //转动相机（观察坐标系）
{
  //派生类中实现
}
void CGCamera::Move3DCamera(double tx, double ty)  //频移观察窗口
{}
void CGCamera::Zoom3DCamera(double ratio)  //给定观察窗口的缩放比例
{}
void CGCamera::Rotate3DCamera(double angle)  //转动相机（观察坐标系)
{}
//相机参数
void CGCamera::InitCamera() {}
void CGCamera::setEyePos(double eyex, double eyey, double eyez) {}
void CGCamera::setEyeRef(double refx, double refy, double refz) {}
void CGCamera::setEyeUp(double upx, double upy, double upz) {}
void CGCamera::getEyePos(double& eyex, double& eyey, double& eyez) {}
void CGCamera::getEyeRef(double& refx, double& refy, double& refz) {}
void CGCamera::getEyeUp(double& upx, double& upy, double& upz) {}
void CGCamera::setVCSVolume(double vleft,
                            double vbottom,
                            double vright,
                            double vtop,
                            double vnear,
                            double vfar) {}
void CGCamera::getVCSVolume(double& vleft,
                            double& vbottom,
                            double& vright,
                            double& vtop,
                            double& vnear,
                            double& vfar) {}
void CGCamera::Projection(int mode) {}