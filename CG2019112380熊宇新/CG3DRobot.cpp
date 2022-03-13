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
  m_Name.Format(_T("机器人-%ld"), sID);
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
  //检查所属场景是否有相机
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
  //定义白色
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
  drawBall(40, 0, 100, 0);        //头
  drawSkewed(4, 2, 4, 0, 50, 0);  //脖子
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
  drawHalfBall(30, -85, 10, 0);             //左肩膀
  glRotated(mLeftArmAngle, 1.0, 0.0, 0.0);  //控制手臂抬起
  drawSkewed(2.0, 10.0, 2, -85, -30, 0);    //左手臂
  drawBall(20, -85, -100, 0);               //左手
  glPopMatrix();
  glPushMatrix();
  drawHalfBall(30, 85, 10, 0);               //右肩膀
  glRotated(mRightArmAngle, 1.0, 0.0, 0.0);  //控制手臂抬起
  drawSkewed(2.0, 10.0, 2, 85, -30, 0);      //右手臂
  drawBall(20, 85, -100, 0);                 //右手
  glPopMatrix();
}
void CG3DRobot::drawLeg() {
  glPushMatrix();
  drawSkewed(2.5, 6, 2, -30, -130, 0);  //左大腿
  drawBall(18, -30, -170, 0);           //左膝盖
  glRotated(mLeftLegAngle, 1.0, 0.0, 0.0);
  drawSkewed(2.0, 6, 2, -30, -200, 0);  //左小腿
  drawSkewed(3.0, 2, 3, -30, -240, 0);  //左脚
  glPopMatrix();
  glPushMatrix();
  drawSkewed(2.5, 6, 2, 30, -130, 0);  //右大腿
  drawBall(18, 30, -170, 0);           //右膝盖
  glRotated(mRightLegAngle, 1.0, 0.0, 0.0);
  drawSkewed(2.0, 6, 2, 30, -200, 0);  //右小腿
  drawSkewed(3.0, 2, 3, 30, -240, 0);  //右脚
  glPopMatrix();
}

//画球体
void CG3DRobot::drawBall(double R, double x, double y, double z) {
  glPushMatrix();
  glTranslated(x, y, z);
  glutSolidSphere(R, 20, 20);
  glPopMatrix();
}
//画半球
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
//画长方体
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

//复位
void CG3DRobot::robotReset() {
  mRotateAngle = 0.0;  //身体角度
  mLeftArmAngle = 0.0, mRightArmAngle = 0.0, mLeftLegAngle = 0.0,
  mRightLegAngle = 0.0;
  //手臂和腿角度
  mLeftArmDirec = 1, mRightArmDirec = 1, mLeftLegDirec = 1, mRightLegDirec = 1;
  mtx = 0, mty = 0, mtz = 0;                //平移量
  msx = 1.0, msy = 1.0, msz = 1.0;          //缩放量
  mrx = 0, mry = 0, mrz = 0, mAngle = 0.0;  //旋转
}
//左手臂抬起
void CG3DRobot::rightArmRotate() {
  if (mRightArmDirec) {  //如果方向朝前
    mRightArmAngle -= 30.0;
    if (mRightArmAngle <= -90.0)
      mRightArmDirec = 0;  //方向转为朝后
  } else {
    mRightArmAngle += 30.0;
    if (mRightArmAngle >= 90.0)
      mRightArmDirec = 1;  //方向转为朝前
  }
}
void CG3DRobot::leftArmRotate() {
  if (mLeftArmDirec) {  //如果方向朝前
    mLeftArmAngle -= 30.0;
    if (mLeftArmAngle <= -90.0)
      mLeftArmDirec = 0;  //方向转为朝后
  } else {
    mLeftArmAngle += 30.0;
    if (mLeftArmAngle >= 90.0)
      mLeftArmDirec = 1;  //方向转为朝前
  }
}
void CG3DRobot::rightLegRotate() {
  if (mRightLegDirec) {  //如果方向朝前
    mRightLegAngle -= 10.0;
    if (mRightLegAngle <= -30.0)
      mRightLegDirec = 0;  //方向转为朝后
  } else {
    mRightLegAngle += 10.0;
    if (mRightLegAngle >= 30.0)
      mRightLegDirec = 1;  //方向转为朝前
  }
}
void CG3DRobot::leftLegRotate() {
  if (mLeftLegDirec) {  //如果方向朝前
    mLeftLegAngle -= 10.0;
    if (mLeftLegAngle <= -30.0)
      mLeftLegDirec = 0;  //方向转为朝后
  } else {
    mLeftLegAngle += 10.0;
    if (mLeftLegAngle >= 30.0)
      mLeftLegDirec = 1;  //方向转为朝前
  }
}

void CG3DRobot::bodyLeftRotate() {
  mRotateAngle -= 30.0;
}
void CG3DRobot::bodyRigRotate() {
  mRotateAngle += 30.0;
}
void CG3DRobot::_3DTranslate(double tx, double ty, double tz)  //平移
{
  mtx += tx;
  mty += ty;
  mtz += tz;
}
void CG3DRobot::_3DRotate(double angle, double cx, double cy, double cz)  //旋转
{
  mAngle += angle;
  mrx = cx;
  mry = cy;
  mrz = cz;
}
void CG3DRobot::_3DScale(double sx, double sy, double sz)  //缩放
{
  msx *= sx;
  msy *= sy;
  msz *= sz;
}
