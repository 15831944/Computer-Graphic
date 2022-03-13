#include "pch.h"
#include "COGL3DScene.h"
#include "CG3DRenderable.h"
#include "CG3DRobot.h"
#include "COGL3DCamera.h"
#include "COGL3DRenderContext.h"
#include "COGL3DView.h"


IMPLEMENT_SERIAL(COGL3DScene, CGScene, 1)
COGL3DScene::COGL3DScene() {
  mDefaultCamera = new COGL3DCamera();  //初始化默认相机
  mDefaultCamera->InitCamera();
}
COGL3DScene::~COGL3DScene() {
  if (mDefaultCamera) {
    delete mDefaultCamera;
    mDefaultCamera = nullptr;
  }
}
//序列化
void COGL3DScene::Serialize(CArchive& ar) {
  CGScene::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}

//渲染场景到指定客户区（依赖COGL3DView）
bool COGL3DScene::RenderScene(CGView* pView) {
  if (pView == nullptr || !pView->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return false;
  CRect rc;
  pView->GetClientRect(&rc);
  mDefaultCamera->setClientRect(0, 0, rc.Width(), rc.Height());   //客户区
  mDefaultCamera->setViewPortBox(0, 0, rc.Width(), rc.Height());  //视口
  //测试窗口
  // mDefaultCamera->setViewWindowBox(0, 0, rc.Width(), rc.Height());
  //绘制场景中所有对象
  COGL3DView* pv = dynamic_cast<COGL3DView*>(pView);
  if (pv != nullptr) {
    CGRenderContext* pRC = pv->GetRenderContext();
    if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(COGL3DRenderContext)))
      return false;
    COGL3DRenderContext* pRenderContext =
        dynamic_cast<COGL3DRenderContext*>(pRC);
    if (pRenderContext == nullptr)
      return false;
    // pRenderContext->setView(pView); //设置View
    int i = 0, cnt = mRenderables.GetSize();
    pRenderContext->Ready();
    mDefaultCamera->Projection(projectionMode);
    

    while (i < cnt) {
      CGRenderable* r = mRenderables.GetAt(i);
      if (r != nullptr) {
        if (r->status() == CGRenderable::statusSelected) {
        }
        r->Render(pRenderContext);
      }
      i++;
    }

    // GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    // GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    // GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    // GLfloat mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
    // GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat no_shininess[] = {0.0};
    // GLfloat low_shininess[] = {5.0};
    // GLfloat high_shininess[] = {100.0};
    // GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
    // glShadeModel(GL_SMOOTH);
    // glPushMatrix();
    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_color);
    // //材料的环境光颜色 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
    // mat_diffuse);   //材料的漫反射光颜色 glMaterialfv(GL_FRONT_AND_BACK,
    // GL_SPECULAR, mat_specular); //材料的镜面反射光颜色
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess); //光亮度
    // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);  //材料的辐射光颜色
    // glutSolidTeapot(50);
    // glPopMatrix();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(250, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 500, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 500);
    glEnd();

    // glPopMatrix();
    // glPushMatrix();
    // glTranslatef(15.0f, 0.0f, 0.0f);
    // glTranslatef(0.0f, 0.0f, -60.0f);  // 左移    1.5 单位，并移入屏幕    6.0
    // glRotatef(90.0f, 1.0f, 0.0f,0.0f);  //
    // 绕Y轴旋转金字塔（角度可以设置成变量进行交互控制） glBegin(GL_TRIANGLES);
    // //开始绘制金字塔的各个面 glColor3f(1.0f, 0.0f, 0.0f);     // 红色
    // glVertex3f(0.0f, 100.0f, 0.0f);  // 三角形的上顶点    (前侧面)
    // glColor3f(0.0f, 1.0f, 0.0f);     // 绿色
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // 三角形的左下顶点    (前侧面)
    // glColor3f(0.0f, 0.0f, 1.0f);           // 蓝色
    // glVertex3f(100.0f, -100.0f, 100.0f);  // 三角形的右下顶点    (前侧面)
    // glColor3f(1.0f, 0.0f, 0.0f);          // 红色
    // glVertex3f(0.0f, 100.0f, 0.0f);  // 三角形的上顶点    (右侧面)
    // glColor3f(0.0f, 0.0f, 1.0f);     // 蓝色
    // glVertex3f(100.0f, -100.0f, 100.0f);  // 三角形的左下顶点    (右侧面)
    // glColor3f(0.0f, 1.0f, 0.0f);          // 绿色
    // glVertex3f(100.0f, -100.0f, -100.0f);  // 三角形的右下顶点    (右侧面)
    // glColor3f(1.0f, 0.0f, 0.0f);           // 红色
    // glVertex3f(0.0f, 100.0f, 0.0f);  // 三角形的上顶点    (后侧面)
    // glColor3f(0.0f, 1.0f, 0.0f);     // 绿色
    // glVertex3f(100.0f, -100.0f, -100.0f);  // 三角形的左下顶点    (后侧面)
    // glColor3f(0.0f, 0.0f, 1.0f);           // 蓝色
    // glVertex3f(-100.0f, -100.0f, -100.0f);  //三角形的右下顶点    (后侧面)
    // glColor3f(1.0f, 0.0f, 0.0f);            // 红色
    // glVertex3f(0.0f, 100.0f, 0.0f);  // 三角形的上顶点    (左侧面)
    // glColor3f(0.0f, 0.0f, 1.0f);     // 蓝色
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // 三角形的左下顶点    (左侧面)
    // glColor3f(0.0f, 1.0f, 0.0f);            // 绿色
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // 三角形的右下顶点    (左侧面)
    // glEnd();                               //金字塔绘制结束

    // glPushMatrix();
    // glTranslatef(3.0f, 0.0f, -1.0f); // 先右移再移入屏幕
    // glRotatef(15.0f, 0.5f, -1.0f, 0.0f);
    //在XYZ轴上旋转立方体（角度可以设置成变量进行交互控制）
    // glBegin(GL_QUADS);//开始绘制立方体
    // glColor3f(0.0f, 1.0f, 0.0f);
    // glVertex3f(100.0f, 100.0f, -100.0f);   // 四边形的右上顶点    (顶面)
    // glVertex3f(-100.0f, 100.0f, -100.0f);  // 四边形的左上顶点    (顶面)
    // glVertex3f(-100.0f, 100.0f, 100.0f);   // 四边形的左下顶点    (顶面)
    // glVertex3f(100.0f, 100.0f, 100.0f);    // 四边形的右下顶点    (顶面)

    // glColor3f(1.0f, 0.5f, 0.0f);           // 颜色改成橙色
    // glVertex3f(100.0f, -100.0f, 100.0f);   // 四边形的右上顶点(底面)
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // 四边形的左上顶点(底面)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // 四边形的左下顶点(底面)
    // glVertex3f(100.0f, -100.0f, -100.0f);   // 四边形的右下顶点(底面)

    // glColor3f(1.0f, 0.0f, 0.0f);            // 颜色改成红色
    // glVertex3f(100.0f, 100.0f, 100.0f);     // 四边形的右上顶点(前面)
    // glVertex3f(-100.0f, 100.0f, 100.0f);    // 四边形的左上顶点(前面)
    // glVertex3f(-100.0f, -100.0f, 100.0f);   // 四边形的左下顶点(前面)
    // glVertex3f(100.0f, -100.0f, 100.0f);    // 四边形的右下顶点(前面)

    // glColor3f(1.0f, 1.0f, 0.0f);            // 颜色改成黄色
    // glVertex3f(100.0f, -100.0f, -100.0f);   // 四边形的右上顶点(后面)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // 四边形的左上顶点(后面)
    // glVertex3f(-100.0f, 100.0f, -100.0f);   // 四边形的左下顶点(后面)
    // glVertex3f(100.0f, 100.0f, -100.0f);    // 四边形的右下顶点(后面)

    // glColor3f(0.0f, 0.0f, 1.0f);            // 颜色改成蓝色
    // glVertex3f(-100.0f, 100.0f, 100.0f);    // 四边形的右上顶点(左面)
    // glVertex3f(-100.0f, 100.0f, -100.0f);   // 四边形的左上顶点(左面)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // 四边形的左下顶点(左面)
    // glVertex3f(-100.0f, -100.0f, 100.0f);   // 四边形的右下顶点(左面)
    // glColor3f(1.0f, 0.0f, 1.0f);            // 颜色改成紫罗兰色
    // glVertex3f(100.0f, 100.0f, -100.0f);    // 四边形的右上顶点(右面)
    // glVertex3f(100.0f, 100.0f, 100.0f);     // 四边形的左上顶点(右面)
    // glVertex3f(100.0f, -100.0f, 100.0f);    // 四边形的左下顶点(右面)
    // glVertex3f(100.0f, -100.0f, -100.0f);   // 四边形的右下顶点(右面)
    // glEnd();                                // 立方体绘制结束
    pRenderContext->Finish();
  }
  return true;
}

//void COGL3DScene::robotReset() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->robotReset();
//}
//void COGL3DScene::rightArmRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->rightArmRotate();
//}
//void COGL3DScene::leftArmRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->leftArmRotate();
//}
//void COGL3DScene::rightLegRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->rightLegRotate();
//}
//void COGL3DScene::leftLegRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->leftLegRotate();
//}
//void COGL3DScene::bodyLeftRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->bodyLeftRotate();
//}
//void COGL3DScene::bodyRigRotate() {
//  CG3DRobot* probot = new CG3DRobot();
//  probot->bodyRigRotate();
//}
// void COGL3DScene::_3DTranslate(double tx, double ty, double tz)  //平移
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DTranslate(tx, ty, tz);
//}
//void COGL3DScene::_3DRotate(double angle,
//                            double cx,
//                            double cy,
//                            double cz)  //旋转（逆时针为正，度）
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DRotate(angle, cx, cy, cz);
//}
//void COGL3DScene::_3DScale(double sx, double sy, double sz)  //缩放
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DScale(sx, sy, sz);
//}