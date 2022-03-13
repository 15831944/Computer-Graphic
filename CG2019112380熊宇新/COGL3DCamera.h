#ifndef _COGL3DCAMERA_H_INCLUDED
#define _COGL3DCAMERA_H_INCLUDED
#pragma once
#include "CGCamera.h"
#include"Vector3.h"
class COGL3DCamera : public CGCamera {
  DECLARE_SERIAL(COGL3DCamera)
 public:
  COGL3DCamera();
  COGL3DCamera(const CString& name);
  virtual ~COGL3DCamera() = default;
  virtual void Serialize(CArchive& ar);

 protected:
  Vec3d mEyePos;                                     //视点位置
  Vec3d mEyeRef;                                     //观察参照
  Vec3d mEyeUp;                                      //向上方向
  double wLeft, wRight, wBottom, wTop, wNear, wFar;  //观察体（三维）
  //double mFocalDistance = 1.0;
 public:
  virtual void InitCamera();
  //设置观察参数
  //视点
  virtual void setEyePos(double eyex, double eyey, double eyez);
  virtual void setEyeRef(double refx, double refy, double refz);
  virtual void setEyeUp(double upx, double upy, double upz);
  virtual void getEyePos(double& eyex, double& eyey, double& eyez);
  virtual void getEyeRef(double& refx, double& refy, double& refz);
  virtual void getEyeUp(double& upx, double& upy, double& upz);
  //观察体
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
  //视口（覆盖，保持高宽比）
  void setViewPortBox(int xl, int yb, int xr, int yt);
  //void setfocalDis(int dis) { mFocalDistance = dis; }
  //取景定义，设置渲染模式下的投影变换
  // mode=0为正交投影（三维），mode=1为透视投影，mode=2或其他为正交投影（二维）
  virtual void Projection(int mode =0 );
  virtual void Move3DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom3DCamera(double ratio);  //给定观察窗口的缩放比例

};
#endif  //_COGL3DCAMERA_H_INCLUDED
