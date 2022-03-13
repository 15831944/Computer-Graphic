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
//��������ϵת�����ӿڣ���ά��
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p) {
  //�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
  //�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
   //return Vec2i(int(p.x()), int(-p.y())+ mClienRect.height());
  //��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
  return VirtualEquipmenttoViewPort(WatchtoVirtualEquipment(WorldtoWatch(p)));
}

double CGDI2DCamera::LengthWorldtoViewPort(const double p) {
  return p / HeightFactorWtoV();
}
double CGDI2DCamera::RadWorldtoViewPort(const double p) {
  return p - mVCSAngleX;
}

//�ӿ�ת������������ϵ����ά��
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p) {
  //�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
  //�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
  // return Vec2d(p.x(), double(mClienRect.height())-p.y());
  //��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
  return WatchtoWorld(VirtualEquipmenttoWatch(ViewPorttoVirtualEquipment(p)));
}

 double CGDI2DCamera::LengthViewPorttoWorld(const double p) {
  return p * HeightFactorWtoV();
}
double CGDI2DCamera::RadViewPorttoWorld(const double p) {
  return p + mVCSAngleX;
}

//��������ϵת�۲�����ϵ
Vec2d CGDI2DCamera::WorldtoWatch(const Vec2d& p) {
  double x = p.x() - mVCSX;
  double y = p.y() - mVCSY;
  double angle = -mVCSAngleX;
  return Vec2d(x * cos(angle) - y * sin(angle),
               x * sin(angle) + y * cos(angle));
}
//�۲�����ϵת�����豸����ϵ
Vec2i CGDI2DCamera::WatchtoVirtualEquipment(const Vec2d& p) {
  return Vec2i(p.x() / WidthFactorWtoV() + 0.5,
               p.y() / HeightFactorWtoV() + 0.5);
}
//�����豸����ϵת�豸����ϵ
Vec2i CGDI2DCamera::VirtualEquipmenttoViewPort(const Vec2i& p) {
  return Vec2i(p.x(), (nvTop - nvBottom) - p.y());
}

//�豸����ϵת�����豸����ϵ
Vec2i CGDI2DCamera::ViewPorttoVirtualEquipment(const Vec2i& p) {
  return Vec2i(p.x(), (nvTop - nvBottom) - p.y());
}
//�����豸����ϵת�۲�����ϵ
Vec2d CGDI2DCamera::VirtualEquipmenttoWatch(const Vec2i& p) {
  return Vec2d(p.x() * WidthFactorWtoV(), p.y() * HeightFactorWtoV());
}
//�۲�����ϵת��������ϵ
Vec2d CGDI2DCamera::WatchtoWorld(const Vec2d& p) {
  return Vec2d(p.x() * cos(mVCSAngleX) - p.y() * sin(mVCSAngleX) + mVCSX,
               p.x() * sin(mVCSAngleX) + p.y() * cos(mVCSAngleX) + mVCSY);
}

// �۲죨��ά����ע����ʵ����Ҫ�������ӿڸ߿��һ�£�
void CGDI2DCamera::Move2DCamera(double tx, double ty)//ƽ�ƹ۲촰��
{
	mVCSX += tx;
	mVCSY += ty;
}
void CGDI2DCamera::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt)//�۲촰�����½ǡ����Ͻ�
{

}
void CGDI2DCamera::Zoom2DCamera(double ratio)//�����۲촰�ڵ����ű�����
{
	wLeft *= ratio;
	wRight *= ratio;       
	wTop *= ratio;
	wBottom *= ratio;
}
void CGDI2DCamera::Rotate2DCamera(double angle)//ת��������۲�����ϵ)
{
	mVCSAngleX += angle;
}

 //���������豸����ϵ
void CGDI2DCamera::setNCS(double x, double y, double angle) {
  mNCSX = x;
  mNCSY = y;
  mNCSAngleX = angle;
}

//���������豸�ӿ�
void CGDI2DCamera::setNCSViewPort(double left,
                                  double bottom,
                                  double right,
                                  double top) {
  //����ԭ������С
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
//���ù۲�����ϵ
void CGDI2DCamera::setVCS(double x, double y, double angle) {
  mVCSX = x;
  mVCSY = y;
  mVCSAngleX = angle;
}
//���ù۲촰��
void CGDI2DCamera::setVCSWindow(double left,
                                double bottom,
                                double right,
                                double top) {
  wLeft = std::min(left, right);
  wRight = std::max(left, right);
  wBottom = std::min(bottom, top);
  wTop = std::max(bottom, top);
}
//�۲촰�ڿ�����ӿڿ�ȵı���?
double CGDI2DCamera::WidthFactorWtoV() const {
  return (wRight - wLeft) / (nvRight - nvLeft);
}
//�۲촰�ڸ߶����ӿڸ߶ȵı���?
double CGDI2DCamera::HeightFactorWtoV() const {
  return (wTop - wBottom) / (nvTop - nvBottom);
}