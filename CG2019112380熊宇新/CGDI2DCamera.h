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

  virtual void Move2DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom2DCamera(const Vec2d& lb,const Vec2d& rt);  //�۲촰�����½ǡ����Ͻ�
  virtual void Zoom2DCamera(double ratio);  //�����۲촰�ڵ����ű�����
  virtual void Rotate2DCamera(double angle);  //ת��������۲�����ϵ)

  	//��������ϵת�����ӿڣ���ά��
  virtual Vec2i WorldtoViewPort(const Vec2d& p);
  virtual double LengthWorldtoViewPort(const double p);
  virtual double RadWorldtoViewPort(const double p);
  //�ӿ�ת������������ϵ����ά��
  virtual Vec2d ViewPorttoWorld(const Vec2i& p);
  virtual double LengthViewPorttoWorld(const double p);
  virtual double RadViewPorttoWorld(const double p);

    //�۲����
  double mVCSAngleX;  //�۲�����ϵx�ᵽ��������ϵx��ĽǶȣ����캯���й���Ϊ0
  double mVCSX, mVCSY;  //�ӵ�λ�ã���άͼ����Ϊ�ǹ۲�����ϵԭ������������ϵ�е����꣩������Ϊ0
  double wLeft, wRight, wBottom, wTop;  //�۲촰�ڣ��ڹ۲�����ϵ�ж��壩���ε����ҡ��¡��ϣ�����Ϊ0
  double nvLeft, nvRight, nvBottom,nvTop;  //�����ӿڣ��������豸����ϵ�ж��壩���ε���������
  double mNCSX, mNCSY;  //�����豸����ϵԭ�����ӿ�����ϵ�е����꣨Ĭ��0��ʵ����û��һ��ʹ�ã�
  double mNCSAngleX;  //�����豸����ϵx�ᵽ�ӿ�����ϵx��ļнǣ�Ĭ��0��ʵ����û��һ��ʹ�ã�
 protected:
  //��������ϵת�۲�����ϵ
  virtual Vec2d WorldtoWatch(const Vec2d& p);
  //�۲�����ϵת�����豸����ϵ
  virtual Vec2i WatchtoVirtualEquipment(const Vec2d& p);
  //�����豸����ϵת�豸����ϵ
  virtual Vec2i VirtualEquipmenttoViewPort(const Vec2i& p);
  //�豸����ϵת�����豸����ϵ
  virtual Vec2i ViewPorttoVirtualEquipment(const Vec2i& p);
  //�����豸����ϵת�۲�����ϵ
  virtual Vec2d VirtualEquipmenttoWatch(const Vec2i& p);
  //�۲�����ϵת��������ϵ
  virtual Vec2d WatchtoWorld(const Vec2d& p);
 
};
#endif  //_CGDI2DCAMERA_H_INCLUDE