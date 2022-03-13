#ifndef _CG3DSPHERE_H_INCLUDED
#define _CG3DSPHERE_H_INCLUDED
#include "CG3DRenderable.h"
#include "Vector3.h"
/// <summary>
/// «ÚÃÂ
/// </summary>
class CG3DSphere : public CG3DRenderable {
  DECLARE_SERIAL(CG3DSphere)
 public:
  CG3DSphere();
  CG3DSphere(Vec3d center,double r,int slice,int stacks);
  CG3DSphere(const CG3DSphere& other);
  virtual ~CG3DSphere();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  void wireSphere(double radius, double slices, double stacks);
  void solidSphere(double radius, double slices, double stacks);
 protected:
  double mRadius;
  int mSlice;
  int mStacks;
  Vec3d mCenter;
};
#endif  //_CG3DSPHERE_H_INCLUDED
