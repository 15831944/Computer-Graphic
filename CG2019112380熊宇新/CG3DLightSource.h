#pragma once
#include "CG3DRenderable.h"
#include "Vector3.h"
class CG3DLightSource : public CG3DRenderable {
    DECLARE_SERIAL(CG3DLightSource)
   public:
    CG3DLightSource();
    CG3DLightSource(const int kind,
                    const Vec3d& ambient,
                    const Vec3d& diffuse,
                    const Vec3d& specular,
                    const Vec3d& pos);
    CG3DLightSource(const int kind,
                    const Vec3d& ambient,
                    const Vec3d& diffuse,
                    const Vec3d& specular,
                    const Vec3d& pos,
                    const Vec3d& spot_direction,
                    const double spot_cutoff,
                    const double spot_exponent);
    CG3DLightSource(const CG3DLightSource& other);
    virtual ~CG3DLightSource();
    //–Ú¡–ªØ
    virtual void Serialize(CArchive& ar);

   public:
    virtual void Render(CGRenderContext* pRC);

   protected:
    Vec3d mPos,mAmbient,mdiffuse,mSpecular;
    Vec3d mSpotDirection;
    double mSpotCutoff, mSpotExponent;
    int mKind;
};
