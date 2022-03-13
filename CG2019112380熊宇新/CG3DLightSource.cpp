
#include "pch.h"
#include "CG3DLightSource.h"
#include "CGRenderable.h"
#include "COGL3DCamera.h"
#include "COGL3DRenderContext.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"


IMPLEMENT_SERIAL(CG3DLightSource, CG3DRenderable, 1)
CG3DLightSource::CG3DLightSource()
    : CG3DRenderable(CString("CG3DLightSource")), mPos(Vec3d(0, 0, 0)) {
  m_Name.Format(_T("光源-%ld"), sID);
}
CG3DLightSource::CG3DLightSource(const int kind,
                                 const Vec3d& ambient,
                                 const Vec3d& diffuse,
                                 const Vec3d& specular,
                                 const Vec3d& pos)
    : CG3DRenderable(CString("CG3DLightSource")),
      mKind(kind),
      mAmbient(ambient),
      mdiffuse(diffuse),
      mSpecular(specular),
      mPos(pos) {
  if (mKind == 0) {
    m_Name.Format(_T("平行光源-%ld"), sID);
  } else if (mKind == 1) {
    m_Name.Format(_T("点光源-%ld"), sID);
  }
}
CG3DLightSource::CG3DLightSource(const int kind,
                                 const Vec3d& ambient,
                                 const Vec3d& diffuse,
                                 const Vec3d& specular,
                                 const Vec3d& pos,
                                 const Vec3d& spot_direction,
                                 const double spot_cutoff,
                                 const double spot_exponent)
    : CG3DRenderable(CString("CG3DLightSource")),
      mKind(kind),
      mAmbient(ambient),
      mdiffuse(diffuse),
      mSpecular(specular),
      mPos(pos),
      mSpotDirection(spot_direction),
      mSpotCutoff(spot_cutoff),
      mSpotExponent(spot_exponent) {
  m_Name.Format(_T("聚光灯光源-%ld"), sID);
}
CG3DLightSource::CG3DLightSource(const CG3DLightSource& other)
    : CG3DRenderable(CString("CG3DLightSource")), mPos(other.mPos) {
  m_Name.Format(_T("光源-%ld"), sID);
}
CG3DLightSource::~CG3DLightSource() {}
//序列化
void CG3DLightSource::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mPos.x() << mPos.y() << mPos.z() << mAmbient.x() << mAmbient.y()
       << mAmbient.z() << mdiffuse.x() << mdiffuse.y() << mdiffuse.z()
       << mSpecular.x() << mSpecular.y() << mSpecular.z();
  } else {
    ar >> mPos.x() >> mPos.y() >> mPos.z() >> mAmbient.x() >> mAmbient.y() >>
        mAmbient.z() >> mdiffuse.x() >> mdiffuse.y() >> mdiffuse.z() >>
        mSpecular.x() >> mSpecular.y() >> mSpecular.z();
  }
}
void CG3DLightSource::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return;
  if (!pRC->IsKindOf(RUNTIME_CLASS(COGL3DRenderContext)))
    return;
  //检查所属场景是否有相机
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr || !camera->IsKindOf(RUNTIME_CLASS(COGL3DCamera)))
    return;

  // GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
  // GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
  // GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
  // GLfloat position[] = {100, 100, 1000, 0.0};  //位置

  if (mKind == 0) {  //平行光
    GLfloat ambient[] = {mAmbient.x(), mAmbient.y(), mAmbient.z(), 1.0};
    GLfloat diffuse[] = {mdiffuse.x(), mdiffuse.y(), mdiffuse.z(), 1.0};
    GLfloat specular[] = {mSpecular.x(), mSpecular.y(), mSpecular.z(), 1.0};
    GLfloat position[] = {mPos.x(), mPos.y(), mPos.z(), 0.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);    //环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);    //漫反射光
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);  //镜面光
    glLightfv(GL_LIGHT1, GL_POSITION, position);  //设置光源位置
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
  } else if (mKind == 1) {  //点光
    GLfloat ambient[] = {mAmbient.x(), mAmbient.y(), mAmbient.z(), 1.0};
    GLfloat diffuse[] = {mdiffuse.x(), mdiffuse.y(), mdiffuse.z(), 1.0};
    GLfloat specular[] = {mSpecular.x(), mSpecular.y(), mSpecular.z(), 1.0};
    GLfloat position[] = {mPos.x(), mPos.y(), mPos.z(), 1.0};
    GLfloat constant[] = {1.0};
    GLfloat linear[] = {0.0014};
    GLfloat quadratic[] = {0.00007};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);    //环境光
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);    //漫反射光
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);  //镜面光
    glLightfv(GL_LIGHT0, GL_POSITION, position);  //设置光源位置
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constant);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, linear);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadratic);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
  } else {  //聚光灯
    GLfloat ambient[] = {mAmbient.x(), mAmbient.y(), mAmbient.z(), 1.0};
    GLfloat diffuse[] = {mdiffuse.x(), mdiffuse.y(), mdiffuse.z(), 1.0};
    GLfloat specular[] = {mSpecular.x(), mSpecular.y(), mSpecular.z(), 1.0};
    GLfloat position[] = {mPos.x(), mPos.y(), mPos.z(), 1.0};
    //GLfloat direction[] = {-1.0, -1.0, 0.0};
    GLfloat angle[] = {30.0};
    GLfloat exponent[] = {5.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);         //环境光
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);         //漫反射光
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);       //镜面光
    glLightfv(GL_LIGHT2, GL_POSITION, position);       //设置光源位置
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, angle);       //设置聚光截至角
    glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, exponent);  //设置聚光指数
    //glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);
  }
}