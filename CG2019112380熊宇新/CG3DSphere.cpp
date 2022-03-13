#include "pch.h"
#include "CG3DSphere.h"
#include "COGL3DRenderContext.h"
#include "Vector2.h"

//#include "CGDI3DRenderContext.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"
IMPLEMENT_SERIAL(CG3DSphere, CG3DRenderable, 1)
CG3DSphere::CG3DSphere()
    : CG3DRenderable(CString("CG3DSphere")),
      mCenter(0, 0, 0),
      mRadius(50),
      mSlice(10),
      mStacks(10) {
  m_Name.Format(_T("����-%ld"), sID);
}
CG3DSphere::CG3DSphere(Vec3d center, double r, int slice, int stacks)
    : CG3DRenderable(CString("CG3DSphere")),
      mCenter(center),
      mRadius(r),
      mSlice(slice),
      mStacks(stacks) {
  m_Name.Format(_T("����-%ld"), sID);
}
CG3DSphere::CG3DSphere(const CG3DSphere& other)
    : CG3DRenderable(CString("CG3DSphere")),
      mCenter(other.mCenter),
      mRadius(other.mRadius),
      mSlice(other.mSlice),
      mStacks(other.mStacks) {
  m_Name.Format(_T("����-%ld"), sID);
}
CG3DSphere::~CG3DSphere() {}
//���л�
void CG3DSphere::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mCenter.x() << mCenter.y() << mCenter.z() << mRadius << mSlice
       << mStacks;
  } else {
    ar >> mCenter.x() >> mCenter.y() >> mCenter.z() >> mRadius >> mSlice >>
        mStacks;
  }
}
void CG3DSphere::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return;

  //������������Ƿ������
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr || !camera->IsKindOf(RUNTIME_CLASS(COGL3DCamera)))
    return;

  int choice = getDrawStyle();
  if (choice == 0) {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 1.0, 0.0);
    glTranslated(mCenter.x(), mCenter.y(), mCenter.z());
    glRotated(90, 1, 0, 0);
    wireSphere(mRadius, mSlice, mStacks);
    glPopMatrix();
  } else {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.0, 0.0, 1.0);
    glTranslated(mCenter.x(), mCenter.y(), mCenter.z());
    glRotated(90, 1, 0, 0);
    solidSphere(mRadius, mSlice, mStacks);
    glPopMatrix();
  }
}

void CG3DSphere::wireSphere(double radius, double slices, double stacks) {
  glDisable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  double step_z = acos(-1) / stacks;       // z����ÿ�β����ĽǶ�
  double step_xy = 2 * acos(-1) / slices;  // x,yƽ��ÿ�β����ĽǶ�
  double x[4], y[4], z[4];  

  double zAngle = 0.0;  //��ʼ�Ƕ�
  double xyAngle = 0.0;
  int i = 0, j = 0;
  glBegin(GL_QUADS);
  for (i = 0; i < stacks; i++) {
    zAngle = i * step_z;  //ÿ�β���zStep
    for (j = 0; j < slices; j++) {
      xyAngle = j * step_xy;                            //ÿ�β���xyStep
      x[0] = radius * sin(zAngle) * cos(xyAngle);  //��һ��ƽ��Ķ�������
      y[0] = radius * sin(zAngle) * sin(xyAngle);
      z[0] = radius * cos(zAngle);
      x[1] =
          radius * sin(zAngle + step_z) * cos(xyAngle);  //��һ��ƽ��Ķ�������
      y[1] = radius * sin(zAngle + step_z) * sin(xyAngle);
      z[1] = radius * cos(zAngle + step_z);
      x[2] = radius * sin(zAngle + step_z) * cos(xyAngle + step_xy);
      y[2] = radius * sin(zAngle + step_z) * sin(xyAngle + step_xy);
      z[2] = radius * cos(zAngle + step_z);
      x[3] = radius * sin(zAngle) * cos(xyAngle + step_xy);
      y[3] = radius * sin(zAngle) * sin(xyAngle + step_xy);
      z[3] = radius * cos(zAngle);  //�õ�һ��ƽ���4����������
      for (int k = 0; k < 4; k++) {
        glVertex3f(0 + x[k], 0 + y[k], 0 + z[k]);  //�������ƽ��
      }
    }  
  }    
  glEnd();

}
void CG3DSphere::solidSphere(double radius, double slices, double stacks) {
  glDisable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  double step_z = acos(-1) / stacks;       // z����ÿ�β����ĽǶ�
  double step_xy = 2 * acos(-1) / slices;  // x,yƽ��ÿ�β����ĽǶ�
  double x[4], y[4], z[4];

  double zAngle = 0.0;  //��ʼ�Ƕ�
  double xyAngle = 0.0;
  int i = 0, j = 0;
  glBegin(GL_QUADS);
  for (i = 0; i < stacks; i++) {
    zAngle = i * step_z;  //ÿ�β���zStep
    for (j = 0; j < slices; j++) {
      xyAngle = j * step_xy;                       //ÿ�β���xyStep
      x[0] = radius * sin(zAngle) * cos(xyAngle);  //��һ��ƽ��Ķ�������
      y[0] = radius * sin(zAngle) * sin(xyAngle);
      z[0] = radius * cos(zAngle);
      x[1] =
          radius * sin(zAngle + step_z) * cos(xyAngle);  //��һ��ƽ��Ķ�������
      y[1] = radius * sin(zAngle + step_z) * sin(xyAngle);
      z[1] = radius * cos(zAngle + step_z);
      x[2] = radius * sin(zAngle + step_z) * cos(xyAngle + step_xy);
      y[2] = radius * sin(zAngle + step_z) * sin(xyAngle + step_xy);
      z[2] = radius * cos(zAngle + step_z);
      x[3] = radius * sin(zAngle) * cos(xyAngle + step_xy);
      y[3] = radius * sin(zAngle) * sin(xyAngle + step_xy);
      z[3] = radius * cos(zAngle);  //�õ�һ��ƽ���4����������
      for (int k = 0; k < 4; k++) {
        glVertex3f(0 + x[k], 0 + y[k], 0 + z[k]);  //�������ƽ��
      }
    }
  }
  glEnd();
}