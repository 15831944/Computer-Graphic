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
  //序列化
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec3f mPos;  //茶壶位置
  Vec3f mMatAmbient; //材料环境光
  Vec3f mMatDiffuse; //材料漫反射光
  Vec3f mMatSpecular; //材料的镜面反射光
  float mMatShiness;	//材料的镜面指数

};
