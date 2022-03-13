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
  mDefaultCamera = nullptr;  //��Scene��������
}
CGScene::~CGScene() {
  removeAllRenderable();
  if (mDefaultCamera) {
    delete mDefaultCamera;
    mDefaultCamera = nullptr;
  }
}
//���л�
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
//ͼ�ζ���
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
////����Ĭ���ӿڲ���
//bool CGScene::setDefaultViewPort(int xl, int yb, int xr, int yt) {
//  if (mDefaultCamera == nullptr)
//    return false;
//  mDefaultCamera->setViewPortBox(xl, yb, xr, yt);
//  return true;
//}
//��Ⱦ������ָ���ͻ������ͻ������������ӿڣ���ÿ���ӿڶ�Ӧһ�������
bool CGScene::RenderScene(CGView* pView) {
  if (pView == nullptr || !pView->IsKindOf(RUNTIME_CLASS(CGView)))
    return false;
  return true;
}
//����Ĭ���ӿڲ���
bool CGScene::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  if (mDefaultCamera == nullptr)
    return false;
  mDefaultCamera->setViewPortBox(xl, yb, xr, yt);
  //�������ù۲촰�ں������豸����ϵ
  mDefaultCamera->setNCS(0, 0, 0);
  mDefaultCamera->setNCSViewPort(xl, yb, xr, yt);
  //���ù۲촰�ڣ����ĵ�����ε���ʱ���ã�
  // mScene.defaultCamera()->setVCS(0, 0, 0);
  // mDefaultCamera->setVCSWindow((xl - xr) / 2, (yb - yt) / 2, xr / 2, yt / 2);
  return true;
}
//����Ĭ�Ϲ۲촰�ڲ���
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
  return mDefaultCamera->LengthViewPorttoWorld(p);  // ���ö�̬
}
double CGScene::RadViewPortToWorld(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->RadViewPorttoWorld(p);  // ���ö�̬
}
Vec2i CGScene::WorldToViewPort(const Vec2d& p) {
  if (mDefaultCamera == nullptr)
    return Vec2i();
  return mDefaultCamera->WorldtoViewPort(p);
}
double CGScene::LengthWorldToViewPort(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->LengthWorldtoViewPort(p);  //���ö�̬
}
double CGScene::RadWorldToViewPort(const double p) {
  if (mDefaultCamera == nullptr)
    return 0;
  return mDefaultCamera->RadWorldtoViewPort(p);  //���ö�̬
}



CGRenderable* CGScene::getRenderable(unsigned int index) {
  if (index >= mRenderables.GetSize())
    return nullptr;
  return mRenderables.GetAt(index);
}

//ͼ�ζ���ѡȡ������������
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
//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
void CGScene::Translate(double tx, double ty)  //ƽ��
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
                     double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Rotate(angle, cx, cy);
    i++;
  }
}
void CGScene::Scale(double sx, double sy)  //����
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->Scale(sx, sy);
    i++;
  }
}

void CGScene::MirrorXAxis()  //����X��Գƣ���ά����ά��
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorXAxis();
    i++;
  }
}
void CGScene::MirrorYAxis()  //����Y��Գƣ���ά����ά��
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYAxis();
    i++;
  }
}
void CGScene::MirrorYeqPosX()  //����y=x�Գƣ���ά����ά��
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYeqPosX();
    i++;
  }
}
void CGScene::MirrorYeNegPX()  //����y=-x�Գƣ���ά����ά��
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorYeNegPX();
    i++;
  }
}
void CGScene::MirrorOrigin()  //����ԭ��Գƣ���ά����ά��
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->MirrorOrigin();
    i++;
  }
}
void CGScene::ShearXAxis(double shx)  //��X�����
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearXAxis(shx);
    i++;
  }
}
void CGScene::ShearYAxis(double shy)  //��Y�����
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearYAxis(shy);
    i++;
  }
}
void CGScene::ShearXYAxis(double shx, double shy)  //��X��Y�����
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->ShearXYAxis(shx, shy);
    i++;
  }
}
void CGScene::Transform(const Mat3d& mat)  //���α任����˸�������
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
// �۲죨��ά����ע����ʵ����Ҫ�������ӿڸ߿��һ�£�
//Ƶ�ƹ۲촰��
void CGScene::Move2DCamera(double tx, double ty) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Move2DCamera(tx, ty);
}
//�۲촰�����½ǡ����Ͻ�
void CGScene::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Zoom2DCamera(lb, rt);
}
//�����۲촰�ڵ����ű�����
void CGScene::Zoom2DCamera(double ratio) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Zoom2DCamera(ratio);
}
//ת��������۲�����ϵ)
void CGScene::Rotate2DCamera(double angle) {
  if (defaultCamera() == nullptr)
    return;
  defaultCamera()->Rotate2DCamera(angle);
}
//���㳡���İ�Χ�У�����ȫ��
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
 void CGScene::_3DTranslate(double tx, double ty, double tz)  //ƽ��
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
                        double cz)  //��ת����ʱ��Ϊ�����ȣ�
{
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->_3DRotate(angle,cx,cy,cz);
    i++;
  }
}
 void CGScene::_3DScale(double sx, double sy, double sz)  //����
 {
  int i = 0, cnt = mSelections.GetSize();
  while (i < cnt) {
    CGRenderable* s = mSelections.GetAt(i);
    if (s)
      s->_3DScale(sx, sy, sz);
    i++;
  }
}
 void CGScene::Move3DCamera(double tx, double ty)  //Ƶ�ƹ۲촰��
 {}
 void CGScene::Zoom3DCamera(double ratio)  //�����۲촰�ڵ����ű���
 {
   if (defaultCamera() == nullptr)
     return;
   defaultCamera()->Zoom3DCamera(ratio);
 }
 void CGScene::Rotate3DCamera(double angle)  //ת��������۲�����ϵ)
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