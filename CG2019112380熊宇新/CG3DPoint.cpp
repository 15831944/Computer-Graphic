#include "pch.h"
#include "CG3DPoint.h"
#include "COGL3DRenderContext.h"
//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DPoint, CG3DRenderable, 1)
CG3DPoint::CG3DPoint()
    : CG3DRenderable(CString("CG3DPoint")), mPos(Vec3d(0, 0, 0)) {
  m_Name.Format(_T("点-%ld"), sID);
}
CG3DPoint::CG3DPoint(const Vec3d& c)
    : CG3DRenderable(CString("CG3DPoint")), mPos(c) {
  m_Name.Format(_T("点-%ld"), sID);
}
CG3DPoint::CG3DPoint(const CG3DPoint& other)
    : CG3DRenderable(CString("CG3DPoint")), mPos(other.mPos) {
  m_Name.Format(_T("点-%ld"), sID);
}
CG3DPoint::~CG3DPoint() {}
//序列化
void CG3DPoint::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mPos.x() << mPos.y() << mPos.z();
  } else {
    ar >> mPos.x() >> mPos.y() >> mPos.z();
  }
}
void CG3DPoint::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return;
  if (/* !pRC->IsKindOf(RUNTIME_CLASS(CGDI3DRenderContext))
          &&*/
      !pRC->IsKindOf(RUNTIME_CLASS(COGL3DRenderContext)))  //
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr || !camera->IsKindOf(RUNTIME_CLASS(COGL3DCamera)))
    return;
  
  glTranslated(mPos.x(), mPos.y(), mPos.z());
  GLUquadricObj* objSphere = gluNewQuadric();
  gluSphere(objSphere, 5.0f, 32, 32);
  glTranslated(-mPos.x(), -mPos.y(), -mPos.z());
  gluDeleteQuadric(objSphere);

}