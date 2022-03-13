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
  //Ҫ��֤xl<xr, yb<yt
  mViewPort.set(vp.box().minCorner().x(), vp.box().minCorner().y(),
                vp.box().maxCorner().x(), vp.box().maxCorner().y());
  //�Ƿ�Ҫ������۲촰�ڵĵȱ�����
}
void CGCamera::setClientRect(int xl, int yb, int xr, int yt) {
  //Ҫ��֤xl<xr, yb<yt
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
//��������ϵת�����ӿڣ���ά��
Vec2i CGCamera::WorldtoViewPort(const Vec2d& p) {
  //��������ʵ��
  return Vec2i(0, 0);
}
double CGCamera::LengthWorldtoViewPort(const double p) {
  //��������ʵ��
  return 0;
}
double CGCamera::RadWorldtoViewPort(const double p) {
  //��������ʵ��
  return 0;
}
//�ӿ�ת������������ϵ����ά��
Vec2d CGCamera::ViewPorttoWorld(const Vec2i& p) {
  //��������ʵ��
  return Vec2d(0, 0);
}
double CGCamera::LengthViewPorttoWorld(const double p) {
  //��������ʵ��
  return 0;
}
double CGCamera::RadViewPorttoWorld(const double p) {
  //��������ʵ��
  return 0;
}
//���������豸����ϵ
void CGCamera::setNCS(double x, double y, double angle) {
  //��������ʵ��
}
    //���������豸�ӿ�
void CGCamera::setNCSViewPort(double left,
                             double bottom,
                             double right,
                             double top) {
  //��������ʵ��
}
//���ù۲�����ϵ
void CGCamera::setVCS(double x, double y, double angle) {
  //��������ʵ��
}
//���ù۲촰��
void CGCamera::setVCSWindow(double left,
                            double bottom,
                            double right,
                            double top) {
  //��������ʵ��
}
//�۲촰�ڿ�����ӿڿ�ȵı�����
double CGCamera::WidthFactorWtoV() const {
  //��������ʵ��
  return 1.0;  //Ĭ�Ϲ۲촰�ڿ�����ӿڿ����ͬ
}
//�۲촰�ڸ߶����ӿڸ߶ȵı�����
double CGCamera::HeightFactorWtoV() const {
  //��������ʵ��
  return 1.0;  //Ĭ�Ϲ۲촰�ڸ߶����ӿڸ߶���ͬ
}
//�۲죨��ά�����������ӿڸ߿��һ�£�
void CGCamera::Move2DCamera(double tx, double ty)  //Ƶ�ƹ۲촰��
{
  //��������ʵ��
}
void CGCamera::Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt)  //�۲촰�����½ǡ����Ͻ�
{
  //��������ʵ��
}
void CGCamera::Zoom2DCamera(double ratio)  //�����۲촰�ڵ����ű�������
{
  //��������ʵ��
}
void CGCamera::Rotate2DCamera(double angle)  //ת��������۲�����ϵ��
{
  //��������ʵ��
}
void CGCamera::Move3DCamera(double tx, double ty)  //Ƶ�ƹ۲촰��
{}
void CGCamera::Zoom3DCamera(double ratio)  //�����۲촰�ڵ����ű���
{}
void CGCamera::Rotate3DCamera(double angle)  //ת��������۲�����ϵ)
{}
//�������
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