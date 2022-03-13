#pragma once
#include "CG3DRenderable.h"
class CG3DTeapot : public CG3DRenderable {
  DECLARE_SERIAL(CG3DTeapot)
 public:
  CG3DTeapot();
  CG3DTeapot(const Vec3f& pos,
             const Vec3f& matAmbient,
             const Vec3f& matDiffuse,
             const Vec3f& matSpecular,
             const float matShiness);
  CG3DTeapot(const CG3DTeapot& other);
  virtual ~CG3DTeapot();
  //���л�
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec3f mPos;  //���λ��
  Vec3f mMatAmbient; //���ϻ�����
  Vec3f mMatDiffuse; //�����������
  Vec3f mMatSpecular; //���ϵľ��淴���
  float mMatShiness;	//���ϵľ���ָ��

};
