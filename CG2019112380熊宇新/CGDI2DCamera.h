#ifndef _CGDI2DCAMERA_H_INCLUDED
#define _CGDI2DCAMERA_H_INCLUDED
#include "CGCamera.h"
#include"afx.h"
class CGDI2DCamera : public CGCamera {
  DECLARE_SERIAL(CGDI2DCamera)
 public:
  CGDI2DCamera();
  CGDI2DCamera(const CString& name);
  virtual ~CGDI2DCamera() = default;
  virtual void Serialize(CArchive& ar);

  //设置虚拟设备坐标系
  virtual void setNCS(double x, double y, double angle);
  //设置虚拟设备视口
  virtual void setNCSViewPort(double left,
                              double bottom,
                              double right,
                              double top);
  //设置观察坐标系
  virtual void setVCS(double x, double y, double angle);
  //设置观察窗口
  virtual void setVCSWindow(double left,
                            double bottom,
                            double right,
                            double top);

  //观察窗口宽度与视口宽度的比例？
  virtual double WidthFactorWtoV() const;
  //观察窗口高度与视口高度的比例？
  virtual double HeightFactorWtoV() const;

  virtual void Move2DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom2DCamera(const Vec2d& lb,const Vec2d& rt);  //观察窗口左下角、右上角
  virtual void Zoom2DCamera(double ratio);  //给定观察窗口的缩放比例（
  virtual void Rotate2DCamera(double angle);  //转动相机（观察坐标系)

  	//世界坐标系转换到视口（二维）
  virtual Vec2i WorldtoViewPort(const Vec2d& p);
  virtual double LengthWorldtoViewPort(const double p);
  virtual double RadWorldtoViewPort(const double p);
  //视口转换到世界坐标系（二维）
  virtual Vec2d ViewPorttoWorld(const Vec2i& p);
  virtual double LengthViewPorttoWorld(const double p);
  virtual double RadViewPorttoWorld(const double p);

    //观察参数
  double mVCSAngleX;  //观察坐标系x轴到世界坐标系x轴的角度，构造函数中构造为0
  double mVCSX, mVCSY;  //视点位置（二维图形认为是观察坐标系原点在世界坐标系中的坐标），构造为0
  double wLeft, wRight, wBottom, wTop;  //观察窗口（在观察坐标系中定义）矩形的左、右、下、上，构造为0
  double nvLeft, nvRight, nvBottom,nvTop;  //虚拟视口（在虚拟设备坐标系中定义）矩形的左右上下
  double mNCSX, mNCSY;  //虚拟设备坐标系原点在视口坐标系中的坐标（默认0，实验中没进一步使用）
  double mNCSAngleX;  //虚拟设备坐标系x轴到视口坐标系x轴的夹角（默认0，实验中没进一步使用）
 protected:
  //世界坐标系转观察坐标系
  virtual Vec2d WorldtoWatch(const Vec2d& p);
  //观察坐标系转虚拟设备坐标系
  virtual Vec2i WatchtoVirtualEquipment(const Vec2d& p);
  //虚拟设备坐标系转设备坐标系
  virtual Vec2i VirtualEquipmenttoViewPort(const Vec2i& p);
  //设备坐标系转虚拟设备坐标系
  virtual Vec2i ViewPorttoVirtualEquipment(const Vec2i& p);
  //虚拟设备坐标系转观察坐标系
  virtual Vec2d VirtualEquipmenttoWatch(const Vec2i& p);
  //观察坐标系转世界坐标系
  virtual Vec2d WatchtoWorld(const Vec2d& p);
 
};
#endif  //_CGDI2DCAMERA_H_INCLUDE