#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGGroup.h"
#include "CGLayer.h"
#include "CGRenderable.h"
#include"CGRenderContext.h"
#include "CGView.h"

#include"CG3DRobot.h"

IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene() : CGObject(CString("CGScene")) {
  mDefaultCamera = nullptr;  //由Scene派生构建
}
CGScene::~CGScene() {
  removeAllRenderable();
  if (mDefaultCamera) {
    delete mDefaultCamera;
    mDefaultCamera = nullptr;
  }
}
//序列化
void CGScene::Serialize(CArchive& ar) {
  CGObject::Serialize(ar);
  mLayers.Serialize(ar);
  mGroups.Serialize(ar);

  if (mDefaultCamera)
    mDefaultCamera->Serialize(ar);
  mCameras.Serialize(ar);

  mRenderables.Serialize(ar);

  if (ar.IsStoring()) {
  
  } else {
    int cnt = mRenderables.GetCount();
    for (int i = 0; i < cnt; i++) {
      mRenderables.GetAt(i)->addToScene(this);
    }
  }
}
//图形对象
bool CGScene::addRenderable(CGRenderable* pr) {
  if (pr == nullptr || !pr->IsKindOf(RUNTIME_CLASS(CGRenderable)))
    return false;
  mRenderables.Add(pr);
  pr->addToScene(this);
  return true;
}
CGRenderable* CGScene::detachRenderable(CGRenderable* r) {
  if (r) {
    r->addToScene(nullptr);
    int i = 0, cnt = mRenderables.GetSize();
    while (i < cnt) {
      if (mRenderables.GetAt(i) == r) {
        mRenderables.RemoveAt(i);
      }
      i++;
    }
  }
  return r;
}
bool CGScene::delRenderable(CGRenderable* pr) {
  if (pr == nullptr)
    return false;
  int i = 0, cnt = mRenderables.GetSize();
  while (i < cnt) {
    if (mRenderables.GetAt(i) == pr) {
      delete mRenderables.GetAt(i);
      mRenderables.RemoveAt(i);
      return true;
    }
    i++;
  }
  return false;
}
void CGScene::removeAllRenderable() {
  int i = 0, cnt = mRenderables.GetSize();
  while (i < cnt) {
    delete mRenderables.GetAt(i++);
  }
  mRenderables.RemoveAll();
}
CGCamera* CGScene::defaultCamera() const {
  return mDefaultCamera;
}
////设置默认视口参数
//bool CGScene::setDefaultViewPort(int xl, int yb, int xr, int yt) {
//  if (mDefaultCamera == nullptr)
//    return false;
//  mDefaultCamera->setViewPortBox(xl, yb, xr, yt);
//  return true;
//}
//渲染场景到指定客户区（客户区包含若干视口），每个视口对应一个相机。
bool CGScene::RenderScene(CGView* pView) {
  if (pView == nullptr || !pView->IsKindOf(RUNTIME_CLASS(CGView)))
    return false;
  return true;
}
//设置默认视口参数
bool CGScene::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  if (mDefaultCamera == nullptr)
    return false;
  mDefaultCamera->setViewPortBox(xl, yb, xr, yt);
  //增加设置观察窗口和虚拟设备坐标系
  mDefaultCamera->setNCS(0, 0, 0);
  mDefaultCamera->setNCSViewPort(xl, yb, xr, yt);
  //设置观察窗口（在文档类初次调用时设置）
  // mScene.defaultCamera()->setVCS(0, 0, 0);
  // mDefaultCamera->setVCSWindow((xl - xr) / 2, (yb - yt) / 2, xr / 2, yt / 2);
  return true;
}
//设置默认观察窗口参数
bool CGScene::setDefaultWindow(double xl, double yb, double xr, double yt) {
  if (mDefaultCamera == nullptr)
    return false;
  if (xr > 1 && yt > 1)
    mDefaultCamera->setVCSWindow(xl, yb, xr, yt);
  return true;
}

Vec2d CGScene::ViewPortToWorld(const Vec2i& p) {
  if (mDefaultCamera == nullptr)
    return Vec2d();
  return mDefaultCamera->ViewPorttoWorld(p);
}
double CGScene::LengthViewPortToWorld(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->LengthViewPorttoWorld(p);  // 利用多态
}
double CGScene::RadViewPortToWorld(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->RadViewPorttoWorld(p);  // 利用多态
}
Vec2i CGScene::WorldToViewPort(const Vec2d& p) {
  if (mDefaultCamera == nullptr)
    return Vec2i();
  return mDefaultCamera->WorldtoViewPort(p);
}
double CGScene::LengthWorldToViewPort(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->LengthWorldtoViewPort(p);  //利用多态
}
double CGScene::RadWorldToViewPort(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->RadWorldtoViewPort(p);  //利用多态
}



CGRenderable* CGScene::getRenderable(unsigned int index) {
  if (index >= mRenderables.GetSize())
    return nullptr;
  return mRenderables.GetAt(index);
}

//图形对象选取（按对象名）
CGRenderable* CGScene::RenderableSelectedByName(const CString& name) {
  int i = 0, cnt = mRenderables.GetSize();
  while (i < cnt) {
    CGRenderable* r = mRenderables.GetAt(i);
    if (r && r->Name() == name && r->status() != CGRenderable::statusSelected) {
      r->setStatus(CGRenderable::statusSelected);
      mSelections.Add(r);
      return r;
    }
    i++;
  }
  return nullptr;
}
bool CGScene::RenderableUnselectByName(const CString& name) {
  int i = 0, cnt = mRenderables.GetSize();
  while (i < cnt) {
    CGRenderable* r = mRenderables.GetAt(i);
    if (r && r->Name() == name) {
      return RenderableUnselect(r);
    }
    i++;
  }
  return false;
}
bool CGScene::RenderableUnselect(CGRenderable* r) {
  if (r)
    r->setStatus(CGRenderable::statusNormal);
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s == r) {
      mSelections.RemoveAt(i);
      return true;
    }
    i++;
  }
  return false;
}
void CGScene::RenderableUnselectAll() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->setStatus(CGRenderable::statusNormal);
    i++;
  }
  mSelections.RemoveAll();
}
//二维图形对象的几何变换（针对选择集中的对象）
void CGScene::Translate(double tx, double ty)  //平移
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Translate(tx, ty);
    i++;
  }
}
void CGScene::Rotate(double angle,
                     double cx,
                     double cy)  //旋转（逆时针为正，度）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Rotate(angle, cx, cy);
    i++;
  }
}
void CGScene::Scale(double sx, double sy)  //缩放
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Scale(sx, sy);
    i++;
  }
}

void CGScene::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorXAxis();
    i++;
  }
}
void CGScene::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYAxis();
    i++;
  }
}
void CGScene::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYeqPosX();
    i++;
  }
}
void CGScene::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYeNegPX();
    i++;
  }
}
void CGScene::MirrorOrigin()  //关于原点对称（二维、三维）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorOrigin();
    i++;
  }
}
void CGScene::ShearXAxis(double shx)  //沿X轴错切
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearXAxis(shx);
    i++;
  }
}
void CGScene::ShearYAxis(double shy)  //沿Y轴错切
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearYAxis(shy);
    i++;
  }
}
void CGScene::ShearXYAxis(double shx, double shy)  //沿X、Y轴错切
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearXYAxis(shx, shy);
    i++;
  }
}
void CGScene::Transform(const Mat3d& mat)  //几何变换（左乘给定矩阵）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Transform(mat);
    i++;
  }
}
void CGScene::Clip(double xl,
                   double yb,
                   double xr,
                   double yt,
                   CGRenderContext* pRC) {
  if (pRC == nullptr)
    return;
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Clip(xl, yb, xr, yt, pRC);
    i++;
  }
}
// 观察（二维）（注意在实现中要保持与视口高宽比一致）
//频移观察窗口
void CGScene::Move2DCamera(double tx, double ty) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Move2DCamera(tx, ty);
}
//观察窗口左下角、右上角
void CGScene::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Zoom2DCamera(lb, rt);
}
//给定观察窗口的缩放比例（
void CGScene::Zoom2DCamera(double ratio) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Zoom2DCamera(ratio);
}
//转动相机（观察坐标系)
void CGScene::Rotate2DCamera(double angle) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Rotate2DCamera(angle);
}
//计算场景的包围盒，用于全显
ABox2d CGScene::ComputeBounds() {
  ABox2d rtn;
  int i = 0;
  int cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    rtn.operator+=(s->BoundingABox());
    i++;
  }
  return rtn;
}
void CGScene::robotReset() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->robotReset();
    i++;
  }
}
void CGScene::rightArmRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->rightArmRotate();
    i++;
  }
}
void CGScene::leftArmRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->leftArmRotate();
    i++;
  }
}
void CGScene::rightLegRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->rightLegRotate();
     i++;
  }
}
void CGScene::leftLegRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->leftLegRotate();
     i++;
  }
}
void CGScene::bodyLeftRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->bodyLeftRotate();
      i++;
  }
}
void CGScene::bodyRigRotate() {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->bodyRigRotate();
     i++;
  }
}
 void CGScene::_3DTranslate(double tx, double ty, double tz)  //平移
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->_3DTranslate(tx, ty, tz);
    i++;
  }
}
 void CGScene::_3DRotate(double angle,
                        double cx,
                        double cy,
                        double cz)  //旋转（逆时针为正，度）
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->_3DRotate(angle,cx,cy,cz);
    i++;
  }
}
 void CGScene::_3DScale(double sx, double sy, double sz)  //缩放
 {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->_3DScale(sx, sy, sz);
    i++;
  }
}
 void CGScene::Move3DCamera(double tx, double ty)  //频移观察窗口
 {}
 void CGScene::Zoom3DCamera(double ratio)  //给定观察窗口的缩放比例
 {
   if (defaultCamera() == nullptr)
     return;
   defaultCamera()->Zoom3DCamera(ratio);
 }
 void CGScene::Rotate3DCamera(double angle)  //转动相机（观察坐标系)
 {

 }
 void CGScene::setProjection(int mode) {
   projectionMode = mode;
 }

 void CGScene::setEyePos(double eyex, double eyey, double eyez) {
   if (defaultCamera() == nullptr)
     return;
   defaultCamera()->setEyePos(eyex, eyey, eyez);
 }
 //void CGScene::setfocalDis(int dis) {
 //  if (defaultCamera() == nullptr)
 //    return;
 //  defaultCamera()->setfocalDis(dis);
 //}