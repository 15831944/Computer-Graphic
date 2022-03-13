#ifndef _CGCAMERA_H_INCLUDED
#define _CGCAMERA_H_INCLUDED
#include "AABBox2.h"
#include "CGViewPort.h"
class CGCamera : public CGObject {
  DECLARE_SERIAL(CGCamera)
 public:
  CGCamera();
  CGCamera(const CString& name);
  virtual ~CGCamera() = default;
  //序列化
  virtual void Serialize(CArchive& ar);
  //视口
  virtual void setViewPortBox(int xl, int yb, int xr, int yt);
  virtual void setViewPort(const CGViewPort& vp);
  //客户区
  void setClientRect(int xl, int yb, int xr, int yt);
  void setClientRect(const ABox2i& rc);

  //世界坐标系转换到视口（二维）
  virtual Vec2i WorldtoViewPort(const Vec2d& p);
  virtual double LengthWorldtoViewPort(const double p);
  virtual double RadWorldtoViewPort(const double p);
  //视口转换到世界坐标系（二维）
  virtual Vec2d ViewPorttoWorld(const Vec2i& p);
  virtual double LengthViewPorttoWorld(const double p);
  virtual double RadViewPorttoWorld(const double p);

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
  //观察（二维）（保持与视口高宽比一致）
  virtual void Move2DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //观察窗口左下角、右上角
  virtual void Zoom2DCamera(double ratio);  //给定观察窗口的缩放比例（）
  virtual void Rotate2DCamera(double angle);  //转动相机（观察坐标系


  virtual void Move3DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom3DCamera(double ratio);  //给定观察窗口的缩放比例
  virtual void Rotate3DCamera(double angle);  //转动相机（观察坐标系)
  //virtual void setfocalDis(int dis) {} 
 protected:
  CGViewPort mViewPort;  //视口
  ABox2i mClienRect;     //视图客户区

 public:
  //三维图形
  virtual void InitCamera();
  //相机参数
  virtual void setEyePos(double eyex, double eyey, double eyez);
  virtual void setEyeRef(double refx, double refy, double refz);
  virtual void setEyeUp(double upx, double upy, double upz);
  virtual void getEyePos(double& eyex, double& eyey, double& eyez);
  virtual void getEyeRef(double& refx, double& refy, double& refz);
  virtual void getEyeUp(double& upx, double& upy, double& upz);
  virtual void setVCSVolume(double vleft,
                            double vbottom,
                            double vright,
                            double vtop,
                            double vnear,
                            double vfar);
  virtual void getVCSVolume(double& vleft,
                            double& vbottom,
                            double& vright,
                            double& vtop,
                            double& vnear,
                            double& vfar);
  virtual void Projection(int mode = 0);
};
#endif  //_CGCAMERA_H_INCLUDED