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
  Vec3d mEyePos;                                     //�ӵ�λ��
  Vec3d mEyeRef;                                     //�۲����
  Vec3d mEyeUp;                                      //���Ϸ���
  double wLeft, wRight, wBottom, wTop, wNear, wFar;  //�۲��壨��ά��
  //double mFocalDistance = 1.0;
 public:
  virtual void InitCamera();
  //���ù۲����
  //�ӵ�
  virtual void setEyePos(double eyex, double eyey, double eyez);
  virtual void setEyeRef(double refx, double refy, double refz);
  virtual void setEyeUp(double upx, double upy, double upz);
  virtual void getEyePos(double& eyex, double& eyey, double& eyez);
  virtual void getEyeRef(double& refx, double& refy, double& refz);
  virtual void getEyeUp(double& upx, double& upy, double& upz);
  //�۲���
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
  //�ӿڣ����ǣ����ָ߿�ȣ�
  void setViewPortBox(int xl, int yb, int xr, int yt);
  //void setfocalDis(int dis) { mFocalDistance = dis; }
  //ȡ�����壬������Ⱦģʽ�µ�ͶӰ�任
  // mode=0Ϊ����ͶӰ����ά����mode=1Ϊ͸��ͶӰ��mode=2������Ϊ����ͶӰ����ά��
  virtual void Projection(int mode =0 );
  virtual void Move3DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom3DCamera(double ratio);  //�����۲촰�ڵ����ű���

};
#endif  //_COGL3DCAMERA_H_INCLUDED
