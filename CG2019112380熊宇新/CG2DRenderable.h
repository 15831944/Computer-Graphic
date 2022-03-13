#ifndef _CG2DRENDERABLE_H_INCLUDED
#define _CG2DRENDERABLE_H_INCLUDED
#include "CGRenderable.h"
#include"AABBox2.h"
class CG2DRenderable : public CGRenderable {
  DECLARE_SERIAL(CG2DRenderable)
 public:
  CG2DRenderable();
  CG2DRenderable(const CString& name);
  virtual ~CG2DRenderable();
  //���л�
  virtual void Serialize(CArchive& ar);
  void setPenColor(COLORREF color);
  COLORREF penColor() const;
  void setPenWidth(int width);
  int penWidth() const;
  void setPenStyle(int style);
  int penStyle() const;
  void setBrushColor(COLORREF color);
  COLORREF brushColor() const;
  void setBrushIndex(int index);
  int brushIndex() const;
  void setTimeChose(int choice);
  int timeChose() const;
  //��άͼ�ζ����Χ��
  ABox2d& BoundingABox();        // AABB��Χ�У�����������
  virtual void ComputeBounds();  //�����Χ�У���Ҫ����������ʵ

 public:
  virtual void Render(CGRenderContext* pRC);
  bool mBrushUse;
  void setBrushUse(bool use);
  bool brushUse() const;
 protected:
  COLORREF mPenColor;
  int mPenWidth;
  int mPenStyle;
  COLORREF mBrushColor;
  int mBrushIndex; 
  int mTimeChose;
  ABox2d mABox;

  double mMCSAngleX;  //��ģ����ϵx�ᵽ��������ϵx��ĽǶȣ����캯���й���Ϊ0
  double mMCSX, mMCSY;        //��ģ����ϵԭ������������ϵ��λ��
  double mMXRatio, mMYRatio;  //��ģ����ϵ����������ϵ�ı���

  //��������ϵת������ģ����ϵ
  virtual Vec2d WorldtoModel(const Vec2d& p);
  //��ģ����ϵת������������ϵ
  virtual Vec2d ModeltoWorld(const Vec2d& p);
};
#endif  //_CG2DRENDERABLE_H_INCLUDED