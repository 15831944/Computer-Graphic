#ifndef _COGL3DSCENE_H_INCLUDED
#define _COGL3DSCENE_H_INCLUDED
#pragma once
#include "CGScene.h"
class COGL3DScene : public CGScene {
  DECLARE_SERIAL(COGL3DScene)
 public:
  COGL3DScene();
  virtual ~COGL3DScene();
  //���л�
  virtual void Serialize(CArchive& ar);
  //��Ⱦ������ָ���ͻ���������COGL3DView��
  virtual bool RenderScene(CGView* pView);
  //void robotReset();
  //void rightArmRotate();			   
  //void leftArmRotate();
  //void rightLegRotate();
  //void leftLegRotate();
  //void bodyLeftRotate();
  //void bodyRigRotate();

 // virtual void _3DTranslate(double tx, double ty, double tz);  //ƽ��
  //virtual void _3DRotate(double angle,
  //                       double cx,
  //                       double cy,
  //                       double cz);  //��ת����ʱ��Ϊ�����ȣ�
  //virtual void _3DScale(double sx, double sy, double sz);  //����
};
#endif  // 