#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "CGObject.h"
#include "Matrix33.h"
#include "Vector2.h"
#include"AABBox2.h"
class CGRenderable;
class CGLayer;
class CGCamera;
class CGView;
class CGGroup;
class CGRenderContext;
class CGScene : public CGObject {
  DECLARE_SERIAL(CGScene)
 public:
  CGScene();
  virtual ~CGScene();
  virtual void Serialize(CArchive& ar);

  CGRenderable* getRenderable(unsigned int index);


  //图形对象
  bool addRenderable(CGRenderable*);
  CGRenderable* detachRenderable(CGRenderable*);
  bool delRenderable(CGRenderable*);
  void removeAllRenderable();
  CGCamera* defaultCamera() const;
  //图形对象选取（按对象名）
  CGRenderable* RenderableSelectedByName(const CString& name);
  bool RenderableUnselectByName(const CString& name);
  bool RenderableUnselect(CGRenderable* r);
  void RenderableUnselectAll();

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
  //测试裁剪用（通过文档类调用）;
  virtual void Clip(double xl,
                    double yb,
                    double xr,
                    double yt,
                    CGRenderContext* pRC);

  //设置默认视口参数
  bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  // 设置默认观察窗口参数
  bool setDefaultWindow(double xl, double yb, double xr, double yt);
  //渲染场景到指定客户区（客户区包含若干视口），每个视口对应一个相机。
  virtual bool RenderScene(CGView* pView);  //应派生类中重写
  //观察（二维）（注意在实现中要保持与视口高宽比一致）
  virtual void Move2DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //观察窗口左下角、右上角
  virtual void Zoom2DCamera(double ratio);  //给定观察窗口的缩放比例（）
  virtual void Rotate2DCamera(double angle);  //转动相机（观察坐标系）
  virtual ABox2d ComputeBounds();  //计算场景的包围盒，用于全显

  	//根据视口坐标获取对应场景坐标（二维）–调用默认相机函数ViewtoWorld
  Vec2d ViewPortToWorld(const Vec2i& p);
  double LengthViewPortToWorld(const double p);
  double RadViewPortToWorld(const double p);
  Vec2i WorldToViewPort(const Vec2d& p);
  double LengthWorldToViewPort(const double p);
  double RadWorldToViewPort(const double p);

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
   virtual void Move3DCamera(double tx, double ty);         //频移观察窗口
   virtual void Zoom3DCamera(double ratio);  //给定观察窗口的缩放比例
   virtual void Rotate3DCamera(double angle);  //转动相机（观察坐标系)
   virtual void setProjection(int mode);
  /* virtual void setfocalDis(int dis);*/
   virtual void setEyePos(double eyex, double eyey, double eyez);

  protected:
   int projectionMode = 0;

 protected:
  //图形对象选择集
  CTypedPtrArray<CObArray, CGRenderable*> mSelections;
  //图层对象列表（命名对象，不能重名）
  CMapStringToOb mLayers;
  // CTypedPtrArray<CObArray, CGLayer*> mLayers;
  //图块对象列表（命名对象，不能重名）
  CMapStringToOb mGroups;
  // CTypedPtrArray<CObArray, CGGroup*> mGroups;
  //默认相机
  CGCamera* mDefaultCamera;
  //其他相机（命名对象，不能重名）
  CMapStringToOb mCameras;
  // CTypedPtrArray<CObArray, CGCamera*> mCameras;
  //图形对象列表
  // CMapStringToOb mRenderables; 
  //用于检查是否重名
  CTypedPtrArray<CObArray, CGRenderable*> mRenderables;
};
#endif  //_CGSCENE_H_INCLUDED