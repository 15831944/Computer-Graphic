#pragma once
#include "CG3DRenderable.h"
#include "Vector3.h"
class CG3DTraingles : public CG3DRenderable {
  DECLARE_SERIAL(CG3DTraingles)
 public:
  CG3DTraingles();
  CG3DTraingles(const Vec3dArray& Point,int mode);
  CG3DTraingles(const CG3DTraingles& other);
  virtual ~CG3DTraingles();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  int mode;
  Vec3dArray mPoint;
};
