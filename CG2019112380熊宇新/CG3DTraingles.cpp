#include "pch.h"
#include "CG3DTraingles.h"
#include "COGL3DRenderContext.h"

//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DTraingles, CG3DRenderable, 1)
CG3DTraingles::CG3DTraingles()
    : CG3DRenderable(CString("CG3DTraingles")){
  m_Name.Format(_T("三角形-%ld"), sID);
}

CG3DTraingles::CG3DTraingles(const Vec3dArray& Points, int mode)
    : CG3DRenderable(CString("CG3DTraingles")) ,mPoint(Points){
  this->mode = mode;
  m_Name.Format(_T("三角形-%ld"), sID);
}

CG3DTraingles::~CG3DTraingles() {}
//序列化
void CG3DTraingles::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
}

void CG3DTraingles::Render(CGRenderContext* pRC) {
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
    glLineWidth(5);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i <mPoint.size(); i++) {
      glVertex3f(mPoint[i].x(), mPoint[i].y(), mPoint[i].z());
    }
    glEnd();
  } else if(mode==1){
    glDisable(GL_LIGHTING);
    glLineWidth(5);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 1.0);
    for (int i = 0; i < mPoint.size(); i++) {
      glVertex3f(mPoint[i].x(), mPoint[i].y(), mPoint[i].z());
    }
    glEnd();
  } else{
    glDisable(GL_LIGHTING);
    glLineWidth(5);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < mPoint.size(); i++) {
      glVertex3f(mPoint[i].x(), mPoint[i].y(), mPoint[i].z());
    }
    glEnd();
  }

  // glEnable(GL_LIGHTING);
}