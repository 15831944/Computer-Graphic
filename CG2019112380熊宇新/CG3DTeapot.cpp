#include "pch.h"
#include "CG3DTeapot.h"
#include "COGL3DCamera.h"
#include "COGL3DRenderContext.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"


IMPLEMENT_SERIAL(CG3DTeapot, CG3DRenderable, 1)
CG3DTeapot::CG3DTeapot() : CG3DRenderable(CString("CG3DTeapot")) {
  m_Name.Format(_T("茶壶-%ld"), sID);
}
CG3DTeapot::CG3DTeapot(const Vec3f& pos,
                       const Vec3f& matAmbient,
                       const Vec3f& matDiffuse,
                       const Vec3f& matSpecular,
                       const float matShiness)
    : CG3DRenderable(CString("CG3DTeapot")),
      mPos(pos),
      mMatAmbient(matAmbient),
      mMatDiffuse(matDiffuse),
      mMatSpecular(matSpecular),
      mMatShiness(matShiness) {
  m_Name.Format(_T("茶壶-%ld"), sID);
}
CG3DTeapot::CG3DTeapot(const CG3DTeapot& other)
    : CG3DRenderable(CString("CG3DTeapot")) {
  m_Name.Format(_T("茶壶-%ld"), sID);
}
CG3DTeapot::~CG3DTeapot() {}
//序列化
void CG3DTeapot::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mPos.x() << mPos.y() << mPos.z() << mMatAmbient.x() << mMatAmbient.y()
       << mMatAmbient.z() << mMatDiffuse.x() << mMatDiffuse.y()
       << mMatDiffuse.z() << mMatSpecular.x() << mMatSpecular.y()
       << mMatSpecular.z() << mMatShiness;
  } else {
    ar >> mPos.x() >> mPos.y() >> mPos.z() >> mMatAmbient.x() >>
        mMatAmbient.y() >> mMatAmbient.z() >> mMatDiffuse.x() >>
        mMatDiffuse.y() >> mMatDiffuse.z() >> mMatSpecular.x() >>
        mMatSpecular.y() >> mMatSpecular.z() >> mMatShiness;
  }
}
void CG3DTeapot::Render(CGRenderContext* pRC) {
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

  GLfloat mat_ambient[] = {mMatAmbient.x(), mMatAmbient.y(), mMatAmbient.z(),1.0};
  GLfloat mat_diffuse[] = {mMatDiffuse.x(), mMatDiffuse.y(), mMatDiffuse.z(),
                            1.0};
  GLfloat mat_specular[] = {mMatSpecular.x(), mMatSpecular.y(),
                            mMatSpecular.z(), 1.0};
  GLfloat mat_shininess[] = {mMatShiness};
  glShadeModel(GL_SMOOTH);
  glPushMatrix();
  glTranslated(mPos.x(), mPos.y(), mPos.z());
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);  //材料的环境光颜色
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
               mat_diffuse);  //材料的漫反射光颜色
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
               mat_specular);  //材料的镜面反射光颜色
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);  //光亮度
  glutSolidTeapot(50);
  glPopMatrix();
}