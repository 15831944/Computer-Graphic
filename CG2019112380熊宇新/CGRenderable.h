#ifndef _CGRENDERABLE_H_INCLUDED
#define _CGRENDERABLE_H_INCLUDED
#include "CGObject.h"
#include"Vector2.h"
#include"Matrix33.h"
#include"AABBox2.h"
class CGScene;
class CGLayer;
class CGGroup;
class CGRenderContext;
class CGRenderable : public CGObject {
  DECLARE_SERIAL(CGRenderable)
 public:
  CGRenderable();
  CGRenderable(const CString& name);
  virtual ~CGRenderable();
  //序列化
  virtual void Serialize(CArchive& ar);
  void setParent(CGRenderable* p);
  CGRenderable* parent() const;
  void setGroup(CGGroup* p);
  CGGroup* group() const;
  void setLayer(CGLayer* lay);
  CGLayer* layer() const;
  void addToScene(CGScene* s);
  CGScene* scene() const;
  // 对象状态定义（也可用枚举类型） 
  static const int statusNormal =0;     //正常状态
  static const int statusSelected = 1;  //选中状态
  int status() const { return mStatus; }
  void setStatus(int s) { mStatus = s; }

  //对象包围盒是否需要重新计算
  bool boundsDirty() const { return mBoundsDirty; }
  void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
  ABox2d& BoundingABox() { return ABox2d(); }

 public:
  virtual void Render(CGRenderContext* pRC);

  //二维图形对象的几何变换
  virtual void Translate(double tx, double ty);  //平移
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //旋转（逆时针为正，度）
  virtual void Scale(double sx, double sy);  //缩放
  virtual void MirrorXAxis();    //关于X轴对称（二维、三维）
  virtual void MirrorYAxis();    //关于Y轴对称（二维、三维）
  virtual void MirrorYeqPosX();  //关于y=x对称（二维、三维）
  virtual void MirrorYeNegPX();  //关于y=-x对称（二维、三维）
  virtual void MirrorOrigin();   //关于原点对称（二维、三维）
  virtual void ShearXAxis(double shx);               //沿X轴错切
  virtual void ShearYAxis(double shy);               //沿Y轴错切
  virtual void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切
  virtual void Transform(const Mat3d& mat);  //几何变换（左乘给定矩阵）
  virtual bool Clip(double xl,
                    double yb,
                    double xr,
                    double yt,
                    CGRenderContext* pRC);  //矩形裁剪窗口
  virtual bool Clip(const Vec2dArry& clipWin,
                    CGRenderContext* pRC);  //任意多边形裁剪窗口

    virtual void robotReset();
  virtual void rightArmRotate();
  virtual void leftArmRotate();
  virtual void rightLegRotate();
  virtual void leftLegRotate();
  virtual void bodyLeftRotate();
  virtual void bodyRigRotate();
  virtual void _3DTranslate(double tx, double ty, double tz);  //平移
  virtual void _3DRotate(double angle,
                      double cx,
                      double cy,
                      double cz);  //旋转（逆时针为正，度）
  virtual void _3DScale(double sx, double sy, double sz);  //缩放
 protected:
  CGScene* mScene;  //对象实例所属的场景，当对象加入场景时自动进行设置。
  CGLayer* mLayer;        //对象实例所属的图层
  CGGroup* mGroup;        //对象实例所属的图块
  CGRenderable* mParent;  //
  CTypedPtrArray<CObArray, CGRenderable*> mChildren;
  bool mBrushUse;
  void setBrushUse(bool use);
  void brushUse() const;
  int mStatus = 0;
  bool mBoundsDirty;  //包围盒是否已改变
  
};
#endif  //_CGRENDERABLE_H_INCLUDED