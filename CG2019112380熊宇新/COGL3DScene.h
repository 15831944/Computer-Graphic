#ifndef _COGL3DSCENE_H_INCLUDED
#define _COGL3DSCENE_H_INCLUDED
#pragma once
#include "CGScene.h"
class COGL3DScene : public CGScene {
  DECLARE_SERIAL(COGL3DScene)
 public:
  COGL3DScene();
  virtual ~COGL3DScene();
  //序列化
  virtual void Serialize(CArchive& ar);
  //渲染场景到指定客户区（依赖COGL3DView）
  virtual bool RenderScene(CGView* pView);
  //void robotReset();
  //void rightArmRotate();			   
  //void leftArmRotate();
  //void rightLegRotate();
  //void leftLegRotate();
  //void bodyLeftRotate();
  //void bodyRigRotate();

 // virtual void _3DTranslate(double tx, double ty, double tz);  //平移
  //virtual void _3DRotate(double angle,
  //                       double cx,
  //                       double cy,
  //                       double cz);  //旋转（逆时针为正，度）
  //virtual void _3DScale(double sx, double sy, double sz);  //缩放
};
#endif  // 