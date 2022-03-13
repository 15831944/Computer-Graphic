#pragma once
#include "CG3DRenderable.h"
#include "Vector3.h"
class CG3DPolygon : public CG3DRenderable {
  DECLARE_SERIAL(CG3DPolygon)
 public:
  CG3DPolygon();
  CG3DPolygon(const Vec3dArray& mPoint, int mode);
  CG3DPolygon(const CG3DPolygon& other);
  virtual ~CG3DPolygon();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec3dArray mPoints;
  int mode;
};