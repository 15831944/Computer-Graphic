#include "pch.h"
#include "CG3DLineSegment.h"
#include "COGL3DRenderContext.h"

//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DLineSegment, CG3DRenderable, 1)
CG3DLineSegment::CG3DLineSegment()
    : CG3DRenderable(CString("CG3DLineSegment")),
      mP1(Vec3d(0, 0, 0)),
      mP2(Vec3d(0, 0, 0)) {
  m_Name.Format(_T("线段-%ld"), sID);
}
CG3DLineSegment::CG3DLineSegment(const Vec3d& p1, const Vec3d& p2)
    : CG3DRenderable(CString("CG3DLineSegment")), mP1(p1), mP2(p2) {
  m_Name.Format(_T("线段-%ld"), sID);
}
CG3DLineSegment::CG3DLineSegment(const CG3DLineSegment& other)
    : CG3DRenderable(CString("CG3DLineSegment")),
      mP1(other.mP1),
      mP2(other.mP2) {
  m_Name.Format(_T("线段-%ld"), sID);
}
CG3DLineSegment::~CG3DLineSegment() {}
//序列化
void CG3DLineSegment::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mP1.x() << mP1.y() << mP1.z() << mP2.x() << mP2.y() << mP2.z();
  } else {
    ar >> mP1.x() >> mP1.y() >> mP1.z() >> mP2.x() >> mP2.y() >> mP2.z();
  }
}

void CG3DLineSegment::Render(CGRenderContext* pRC) {
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

  glDisable(GL_LIGHTING);
  glLineWidth(5);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(mP1.x(), mP1.y(), mP1.z());
  glVertex3f(mP2.x(), mP2.y(), mP2.z());
  glEnd();
  //glEnable(GL_LIGHTING);
}