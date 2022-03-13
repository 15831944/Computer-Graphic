#pragma once
#include "CG3DRenderable.h"
class CG3DLineSegment : public CG3DRenderable {
  DECLARE_SERIAL(CG3DLineSegment)
 public:
  CG3DLineSegment();
  CG3DLineSegment(const Vec3d& p1, const Vec3d& p2);
  CG3DLineSegment(const CG3DLineSegment& other);
  virtual ~CG3DLineSegment();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec3d mP1, mP2;
};
