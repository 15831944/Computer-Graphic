#include "pch.h"
#include "COGL3DScene.h"
#include "CG3DRenderable.h"
#include "CG3DRobot.h"
#include "COGL3DCamera.h"
#include "COGL3DRenderContext.h"
#include "COGL3DView.h"


IMPLEMENT_SERIAL(COGL3DScene, CGScene, 1)
COGL3DScene::COGL3DScene() {
  mDefaultCamera = new COGL3DCamera();  //��ʼ��Ĭ�����
  mDefaultCamera->InitCamera();
}
COGL3DScene::~COGL3DScene() {
  if (mDefaultCamera) {
    delete mDefaultCamera;
    mDefaultCamera = nullptr;
  }
}
//���л�
void COGL3DScene::Serialize(CArchive& ar) {
  CGScene::Serialize(ar);
  if (ar.IsStoring()) {
  } else {
  }
}

//��Ⱦ������ָ���ͻ���������COGL3DView��
bool COGL3DScene::RenderScene(CGView* pView) {
  if (pView == nullptr || !pView->IsKindOf(RUNTIME_CLASS(COGL3DView)))
    return false;
  CRect rc;
  pView->GetClientRect(&rc);
  mDefaultCamera->setClientRect(0, 0, rc.Width(), rc.Height());   //�ͻ���
  mDefaultCamera->setViewPortBox(0, 0, rc.Width(), rc.Height());  //�ӿ�
  //���Դ���
  // mDefaultCamera->setViewWindowBox(0, 0, rc.Width(), rc.Height());
  //���Ƴ��������ж���
  COGL3DView* pv = dynamic_cast<COGL3DView*>(pView);
  if (pv != nullptr) {
    CGRenderContext* pRC = pv->GetRenderContext();
    if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(COGL3DRenderContext)))
      return false;
    COGL3DRenderContext* pRenderContext =
        dynamic_cast<COGL3DRenderContext*>(pRC);
    if (pRenderContext == nullptr)
      return false;
    // pRenderContext->setView(pView); //����View
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
    // //���ϵĻ�������ɫ glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
    // mat_diffuse);   //���ϵ����������ɫ glMaterialfv(GL_FRONT_AND_BACK,
    // GL_SPECULAR, mat_specular); //���ϵľ��淴�����ɫ
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess); //������
    // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);  //���ϵķ������ɫ
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
    // glTranslatef(0.0f, 0.0f, -60.0f);  // ����    1.5 ��λ����������Ļ    6.0
    // glRotatef(90.0f, 1.0f, 0.0f,0.0f);  //
    // ��Y����ת���������Ƕȿ������óɱ������н������ƣ� glBegin(GL_TRIANGLES);
    // //��ʼ���ƽ������ĸ����� glColor3f(1.0f, 0.0f, 0.0f);     // ��ɫ
    // glVertex3f(0.0f, 100.0f, 0.0f);  // �����ε��϶���    (ǰ����)
    // glColor3f(0.0f, 1.0f, 0.0f);     // ��ɫ
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // �����ε����¶���    (ǰ����)
    // glColor3f(0.0f, 0.0f, 1.0f);           // ��ɫ
    // glVertex3f(100.0f, -100.0f, 100.0f);  // �����ε����¶���    (ǰ����)
    // glColor3f(1.0f, 0.0f, 0.0f);          // ��ɫ
    // glVertex3f(0.0f, 100.0f, 0.0f);  // �����ε��϶���    (�Ҳ���)
    // glColor3f(0.0f, 0.0f, 1.0f);     // ��ɫ
    // glVertex3f(100.0f, -100.0f, 100.0f);  // �����ε����¶���    (�Ҳ���)
    // glColor3f(0.0f, 1.0f, 0.0f);          // ��ɫ
    // glVertex3f(100.0f, -100.0f, -100.0f);  // �����ε����¶���    (�Ҳ���)
    // glColor3f(1.0f, 0.0f, 0.0f);           // ��ɫ
    // glVertex3f(0.0f, 100.0f, 0.0f);  // �����ε��϶���    (�����)
    // glColor3f(0.0f, 1.0f, 0.0f);     // ��ɫ
    // glVertex3f(100.0f, -100.0f, -100.0f);  // �����ε����¶���    (�����)
    // glColor3f(0.0f, 0.0f, 1.0f);           // ��ɫ
    // glVertex3f(-100.0f, -100.0f, -100.0f);  //�����ε����¶���    (�����)
    // glColor3f(1.0f, 0.0f, 0.0f);            // ��ɫ
    // glVertex3f(0.0f, 100.0f, 0.0f);  // �����ε��϶���    (�����)
    // glColor3f(0.0f, 0.0f, 1.0f);     // ��ɫ
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // �����ε����¶���    (�����)
    // glColor3f(0.0f, 1.0f, 0.0f);            // ��ɫ
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // �����ε����¶���    (�����)
    // glEnd();                               //���������ƽ���

    // glPushMatrix();
    // glTranslatef(3.0f, 0.0f, -1.0f); // ��������������Ļ
    // glRotatef(15.0f, 0.5f, -1.0f, 0.0f);
    //��XYZ������ת�����壨�Ƕȿ������óɱ������н������ƣ�
    // glBegin(GL_QUADS);//��ʼ����������
    // glColor3f(0.0f, 1.0f, 0.0f);
    // glVertex3f(100.0f, 100.0f, -100.0f);   // �ı��ε����϶���    (����)
    // glVertex3f(-100.0f, 100.0f, -100.0f);  // �ı��ε����϶���    (����)
    // glVertex3f(-100.0f, 100.0f, 100.0f);   // �ı��ε����¶���    (����)
    // glVertex3f(100.0f, 100.0f, 100.0f);    // �ı��ε����¶���    (����)

    // glColor3f(1.0f, 0.5f, 0.0f);           // ��ɫ�ĳɳ�ɫ
    // glVertex3f(100.0f, -100.0f, 100.0f);   // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, -100.0f, 100.0f);  // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // �ı��ε����¶���(����)
    // glVertex3f(100.0f, -100.0f, -100.0f);   // �ı��ε����¶���(����)

    // glColor3f(1.0f, 0.0f, 0.0f);            // ��ɫ�ĳɺ�ɫ
    // glVertex3f(100.0f, 100.0f, 100.0f);     // �ı��ε����϶���(ǰ��)
    // glVertex3f(-100.0f, 100.0f, 100.0f);    // �ı��ε����϶���(ǰ��)
    // glVertex3f(-100.0f, -100.0f, 100.0f);   // �ı��ε����¶���(ǰ��)
    // glVertex3f(100.0f, -100.0f, 100.0f);    // �ı��ε����¶���(ǰ��)

    // glColor3f(1.0f, 1.0f, 0.0f);            // ��ɫ�ĳɻ�ɫ
    // glVertex3f(100.0f, -100.0f, -100.0f);   // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, 100.0f, -100.0f);   // �ı��ε����¶���(����)
    // glVertex3f(100.0f, 100.0f, -100.0f);    // �ı��ε����¶���(����)

    // glColor3f(0.0f, 0.0f, 1.0f);            // ��ɫ�ĳ���ɫ
    // glVertex3f(-100.0f, 100.0f, 100.0f);    // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, 100.0f, -100.0f);   // �ı��ε����϶���(����)
    // glVertex3f(-100.0f, -100.0f, -100.0f);  // �ı��ε����¶���(����)
    // glVertex3f(-100.0f, -100.0f, 100.0f);   // �ı��ε����¶���(����)
    // glColor3f(1.0f, 0.0f, 1.0f);            // ��ɫ�ĳ�������ɫ
    // glVertex3f(100.0f, 100.0f, -100.0f);    // �ı��ε����϶���(����)
    // glVertex3f(100.0f, 100.0f, 100.0f);     // �ı��ε����϶���(����)
    // glVertex3f(100.0f, -100.0f, 100.0f);    // �ı��ε����¶���(����)
    // glVertex3f(100.0f, -100.0f, -100.0f);   // �ı��ε����¶���(����)
    // glEnd();                                // ��������ƽ���
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
// void COGL3DScene::_3DTranslate(double tx, double ty, double tz)  //ƽ��
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DTranslate(tx, ty, tz);
//}
//void COGL3DScene::_3DRotate(double angle,
//                            double cx,
//                            double cy,
//                            double cz)  //��ת����ʱ��Ϊ�����ȣ�
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DRotate(angle, cx, cy, cz);
//}
//void COGL3DScene::_3DScale(double sx, double sy, double sz)  //����
//{
//  CG3DRobot* probot = new CG3DRobot();
//  probot->_3DScale(sx, sy, sz);
//}