#ifndef _CG2DSCENE_H_INCLUDED
#define _CG2DSCENE_H_INCLUDED
#include "CGScene.h"
class CGDI2DScene : public CGScene {
  DECLARE_SERIAL(CGDI2DScene)
 public:
  CGDI2DScene();
  virtual ~CGDI2DScene();
  //���л�
  virtual void Serialize(CArchive& ar);
  //��Ⱦ������ָ���ͻ���������CGDI2DView��
  virtual bool RenderScene(CGView* pView);

 protected:
};
#endif  //_CG2DSCENE_H_INCLUDED
