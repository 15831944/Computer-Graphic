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
  //���л�
  virtual void Serialize(CArchive& ar);
  //�ӿ�
  virtual void setViewPortBox(int xl, int yb, int xr, int yt);
  virtual void setViewPort(const CGViewPort& vp);
  //�ͻ���
  void setClientRect(int xl, int yb, int xr, int yt);
  void setClientRect(const ABox2i& rc);

  //��������ϵת�����ӿڣ���ά��
  virtual Vec2i WorldtoViewPort(const Vec2d& p);
  virtual double LengthWorldtoViewPort(const double p);
  virtual double RadWorldtoViewPort(const double p);
  //�ӿ�ת������������ϵ����ά��
  virtual Vec2d ViewPorttoWorld(const Vec2i& p);
  virtual double LengthViewPorttoWorld(const double p);
  virtual double RadViewPorttoWorld(const double p);

  //���������豸����ϵ
  virtual void setNCS(double x, double y, double angle);
  //���������豸�ӿ�
  virtual void setNCSViewPort(double left,
                              double bottom,
                              double right,
                              double top);
  //���ù۲�����ϵ
  virtual void setVCS(double x, double y, double angle);
  //���ù۲촰��
  virtual void setVCSWindow(double left,
                            double bottom,
                            double right,
                            double top);
  //�۲촰�ڿ�����ӿڿ�ȵı�����
  virtual double WidthFactorWtoV() const;
  //�۲촰�ڸ߶����ӿڸ߶ȵı�����
  virtual double HeightFactorWtoV() const;
  //�۲죨��ά�����������ӿڸ߿��һ�£�
  virtual void Move2DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //�۲촰�����½ǡ����Ͻ�
  virtual void Zoom2DCamera(double ratio);  //�����۲촰�ڵ����ű�������
  virtual void Rotate2DCamera(double angle);  //ת��������۲�����ϵ


  virtual void Move3DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom3DCamera(double ratio);  //�����۲촰�ڵ����ű���
  virtual void Rotate3DCamera(double angle);  //ת��������۲�����ϵ)
  //virtual void setfocalDis(int dis) {} 
 protected:
  CGViewPort mViewPort;  //�ӿ�
  ABox2i mClienRect;     //��ͼ�ͻ���

 public:
  //��άͼ��
  virtual void InitCamera();
  //�������
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