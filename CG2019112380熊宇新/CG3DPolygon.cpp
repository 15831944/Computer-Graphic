#include "pch.h"
#include "CG3DPolygon.h"
#include "COGL3DRenderContext.h"

//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DPolygon, CG3DRenderable, 1)
CG3DPolygon::CG3DPolygon()
    : CG3DRenderable(CString("CG3DPolygon")), mPoints() {
  m_Name.Format(_T("折线-%ld"), sID);
}
CG3DPolygon::CG3DPolygon(const Vec3dArray& mPoint,int mode)
    : CG3DRenderable(CString("CG3DPolygon")), mPoints(mPoint),mode(mode) {
  m_Name.Format(_T("折线-%ld"), sID);
}
CG3DPolygon::CG3DPolygon(const CG3DPolygon& other)
    : CG3DRenderable(CString("CG3DPolygon")), mPoints(other.mPoints) {
  m_Name.Format(_T("折线-%ld"), sID);
}
CG3DPolygon::~CG3DPolygon() {}
//序列化
void CG3DPolygon::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}

void CG3DPolygon::Render(CGRenderContext* pRC) {
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
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 1.0);
    for (int i = 0; i < mPoints.size(); i++) {
      glVertex3f(mPoints[i].x(), mPoints[i].y(), mPoints[i].z());
    }
    glEnd();
  } else if(mode==1 ){
    glDisable(GL_LIGHTING);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < mPoints.size(); i++) {
      glVertex3f(mPoints[i].x(), mPoints[i].y(), mPoints[i].z());
    }
    glEnd();
  } else {
    glDisable(GL_LIGHTING);
    glLineWidth(3);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    for (int i = 0; i < mPoints.size(); i++) {
      glVertex3f(mPoints[i].x(), mPoints[i].y(), mPoints[i].z());
    }
    glEnd();
  }
}