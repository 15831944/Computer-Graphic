#include "pch.h"
#include "COGL3DRenderContext.h"
#include "Vector2.h"

//#include "CGDI3DRenderContext.h"
#include "CG3DRenderable.h"
#include "CG3DRobot.h"
#include "COGL3DCamera.h"
#include "COGL3DScene.h"
#include "COGL3DView.h"

IMPLEMENT_SERIAL(CG3DRobot, CG3DRenderable, 1)
CG3DRobot::CG3DRobot() : CG3DRenderable(CString("CG3DRobot")) {
  m_Name.Format(_T("������-%ld"), sID);
}

void CG3DRobot::Serialize(CArchive& ar) {
  CG3DRenderable::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}
void CG3DRobot::Render(CGRenderContext* pRC) {
  if (pRC == nullptr || pRC->getView() == nullptr || mScene == nullptr ||
      !pRC->getView()->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return;
  if (/* !pRC->IsKindOf(RUNTIME_CLASS(CGDI3DRenderContext))
          &&*/
      !pRC->IsKindOf(RUNTIME_CLASS(COGL3DRenderContext)))
    return;
  //������������Ƿ������
  CGCamera* camera = mScene->defaultCamera();
  if (camera == nullptr || !camera->IsKindOf(RUNTIME_CLASS(COGL3DCamera)))
    return;
  GLfloat lightAmbient[] = {0.75f, 0.75f, 0.75f, 1.0f};
  GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
   glEnable(GL_LIGHTING);
   glDrawBuffer(GL_BACK);
   glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
   GLfloat lightPos[] = {1, 1, 1, 0.0f};
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
   glEnable(GL_LIGHT1);
  drawALL();
}

void CG3DRobot::drawALL() {
  //�����ɫ
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glRotated(mRotateAngle, 0.0, 1.0, 0.0);
  glTranslated(mtx, mty, mtz);
  glScaled(msx, msy, msz);
  glRotated(mAngle, mrx, mry, mrz);
  drawHead();
  drawBody();
  drawArm();
  drawLeg();
  glPopMatrix();
}

void CG3DRobot::drawHead() {
  glPushMatrix();
  drawBall(40, 0, 100, 0);        //ͷ
  drawSkewed(4, 2, 4, 0, 50, 0);  //����
  glPopMatrix();
}
void CG3DRobot::drawBody() {
  glPushMatrix();
  glTranslated(0, -30, 0);
  glScaled(10.0, 14.0, 5.0);
  glutSolidCube(10);
  glPopMatrix();
}
void CG3DRobot::drawArm() {
  glPushMatrix();
  drawHalfBall(30, -85, 10, 0);             //����
  glRotated(mLeftArmAngle, 1.0, 0.0, 0.0);  //�����ֱ�̧��
  drawSkewed(2.0, 10.0, 2, -85, -30, 0);    //���ֱ�
  drawBall(20, -85, -100, 0);               //����
  glPopMatrix();
  glPushMatrix();
  drawHalfBall(30, 85, 10, 0);               //�Ҽ��
  glRotated(mRightArmAngle, 1.0, 0.0, 0.0);  //�����ֱ�̧��
  drawSkewed(2.0, 10.0, 2, 85, -30, 0);      //���ֱ�
  drawBall(20, 85, -100, 0);                 //����
  glPopMatrix();
}
void CG3DRobot::drawLeg() {
  glPushMatrix();
  drawSkewed(2.5, 6, 2, -30, -130, 0);  //�����
  drawBall(18, -30, -170, 0);           //��ϥ��
  glRotated(mLeftLegAngle, 1.0, 0.0, 0.0);
  drawSkewed(2.0, 6, 2, -30, -200, 0);  //��С��
  drawSkewed(3.0, 2, 3, -30, -240, 0);  //���
  glPopMatrix();
  glPushMatrix();
  drawSkewed(2.5, 6, 2, 30, -130, 0);  //�Ҵ���
  drawBall(18, 30, -170, 0);           //��ϥ��
  glRotated(mRightLegAngle, 1.0, 0.0, 0.0);
  drawSkewed(2.0, 6, 2, 30, -200, 0);  //��С��
  drawSkewed(3.0, 2, 3, 30, -240, 0);  //�ҽ�
  glPopMatrix();
}

//������
void CG3DRobot::drawBall(double R, double x, double y, double z) {
  glPushMatrix();
  glTranslated(x, y, z);
  glutSolidSphere(R, 20, 20);
  glPopMatrix();
}
//������
void CG3DRobot::drawHalfBall(double R, double x, double y, double z) {
  glPushMatrix();
  glTranslated(x, y, z);
  GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
  glClipPlane(GL_CLIP_PLANE0, eqn);
  glEnable(GL_CLIP_PLANE0);
  glutSolidSphere(R, 20, 20);
  glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}
//��������
void CG3DRobot::drawSkewed(double l,
                           double w,
                           double h,
                           double x,
                           double y,
                           double z) {
  glPushMatrix();
  glTranslated(x, y, z);
  glScaled(l, w, h);
  glutSolidCube(10);
  glPopMatrix();
}

//��λ
void CG3DRobot::robotReset() {
  mRotateAngle = 0.0;  //����Ƕ�
  mLeftArmAngle = 0.0, mRightArmAngle = 0.0, mLeftLegAngle = 0.0,
  mRightLegAngle = 0.0;
  //�ֱۺ��ȽǶ�
  mLeftArmDirec = 1, mRightArmDirec = 1, mLeftLegDirec = 1, mRightLegDirec = 1;
  mtx = 0, mty = 0, mtz = 0;                //ƽ����
  msx = 1.0, msy = 1.0, msz = 1.0;          //������
  mrx = 0, mry = 0, mrz = 0, mAngle = 0.0;  //��ת
}
//���ֱ�̧��
void CG3DRobot::rightArmRotate() {
  if (mRightArmDirec) {  //�������ǰ
    mRightArmAngle -= 30.0;
    if (mRightArmAngle <= -90.0)
      mRightArmDirec = 0;  //����תΪ����
  } else {
    mRightArmAngle += 30.0;
    if (mRightArmAngle >= 90.0)
      mRightArmDirec = 1;  //����תΪ��ǰ
  }
}
void CG3DRobot::leftArmRotate() {
  if (mLeftArmDirec) {  //�������ǰ
    mLeftArmAngle -= 30.0;
    if (mLeftArmAngle <= -90.0)
      mLeftArmDirec = 0;  //����תΪ����
  } else {
    mLeftArmAngle += 30.0;
    if (mLeftArmAngle >= 90.0)
      mLeftArmDirec = 1;  //����תΪ��ǰ
  }
}
void CG3DRobot::rightLegRotate() {
  if (mRightLegDirec) {  //�������ǰ
    mRightLegAngle -= 10.0;
    if (mRightLegAngle <= -30.0)
      mRightLegDirec = 0;  //����תΪ����
  } else {
    mRightLegAngle += 10.0;
    if (mRightLegAngle >= 30.0)
      mRightLegDirec = 1;  //����תΪ��ǰ
  }
}
void CG3DRobot::leftLegRotate() {
  if (mLeftLegDirec) {  //�������ǰ
    mLeftLegAngle -= 10.0;
    if (mLeftLegAngle <= -30.0)
      mLeftLegDirec = 0;  //����תΪ����
  } else {
    mLeftLegAngle += 10.0;
    if (mLeftLegAngle >= 30.0)
      mLeftLegDirec = 1;  //����תΪ��ǰ
  }
}

void CG3DRobot::bodyLeftRotate() {
  mRotateAngle -= 30.0;
}
void CG3DRobot::bodyRigRotate() {
  mRotateAngle += 30.0;
}
void CG3DRobot::_3DTranslate(double tx, double ty, double tz)  //ƽ��
{
  mtx += tx;
  mty += ty;
  mtz += tz;
}
void CG3DRobot::_3DRotate(double angle, double cx, double cy, double cz)  //��ת
{
  mAngle += angle;
  mrx = cx;
  mry = cy;
  mrz = cz;
}
void CG3DRobot::_3DScale(double sx, double sy, double sz)  //����
{
  msx *= sx;
  msy *= sy;
  msz *= sz;
}
