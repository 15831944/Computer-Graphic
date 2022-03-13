#pragma once
#include "CG3DRenderable.h"
class CG3DQuads : public CG3DRenderable {
  DECLARE_SERIAL(CG3DQuads)
 public:
  CG3DQuads();
  CG3DQuads(const Vec3dArray& mPoint,int mode);
  CG3DQuads(const CG3DQuads& other);
  virtual ~CG3DQuads();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  int mode;
  Vec3dArray mPoints;
};
