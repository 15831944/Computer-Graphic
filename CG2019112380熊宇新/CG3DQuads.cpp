#include "pch.h"
#include "CG3DQuads.h"
#include "COGL3DRenderContext.h"
//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DQuads, CG3DRenderable, 1)
CG3DQuads::CG3DQuads() : CG3DRenderable(CString("CG3DQuads")) {
  m_Name.Format(_T("四边形-%ld"), sID);
}

CG3DQuads::CG3DQuads(const Vec3dArray& Points, int mode)
    : CG3DRenderable(CString("CG3DQuads")), mPoints(Points) {
  this->mode = mode;
  m_Name.Format(_T("四边形-%ld"), sID);
}

CG3DQuads::~CG3DQuads() {}
//序列化
void CG3DQuads::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
}

void CG3DQuads::Render(CGRenderContext* pRC) {
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

  if (mode == 0) {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
   glColor3f(1.0, 1.0, 0.0);
    for (int i = 0; i < mPoints.size(); i++) {
      glVertex3f(mPoints[i].x(), mPoints[i].y(), mPoints[i].z());
    }
    glEnd();
  } else if (mode == 1) {
    glDisable(GL_LIGHTING);
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0, 1.0, 1.0);
    for (int i = 0; i < mPoints.size(); i++) {
      glVertex3f(mPoints[i].x(), mPoints[i].y(), mPoints[i].z());
    }
    glEnd();
  } 
}