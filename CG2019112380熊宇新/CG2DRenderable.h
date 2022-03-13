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
  //序列化
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
  //二维图形对象包围盒
  ABox2d& BoundingABox();        // AABB包围盒，可用于设置
  virtual void ComputeBounds();  //计算包围盒，需要在派生类中实

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

  double mMCSAngleX;  //建模坐标系x轴到世界坐标系x轴的角度，构造函数中构造为0
  double mMCSX, mMCSY;        //建模坐标系原点在世界坐标系的位置
  double mMXRatio, mMYRatio;  //建模坐标系到世界坐标系的比例

  //世界坐标系转换到建模坐标系
  virtual Vec2d WorldtoModel(const Vec2d& p);
  //建模坐标系转换到世界坐标系
  virtual Vec2d ModeltoWorld(const Vec2d& p);
};
#endif  //_CG2DRENDERABLE_H_INCLUDED