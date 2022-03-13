#pragma once
#include "CG3DRenderable.h"
#include "Vector3.h"
class CG3DPoint : public CG3DRenderable {
  DECLARE_SERIAL(CG3DPoint)
 public:
  CG3DPoint();
  CG3DPoint(const Vec3d& p);
  CG3DPoint(const CG3DPoint& other);
  virtual ~CG3DPoint();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec3d mPos;
};