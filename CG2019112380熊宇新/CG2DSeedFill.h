
#include"pch.h"
#include"CG2DRenderable.h"
#include"Vector2.h"
class CG2DSeedFill : public CG2DRenderable {
  DECLARE_SERIAL(CG2DSeedFill)
 public:
  CG2DSeedFill();
  CG2DSeedFill(const Vec2d& seed);

  virtual ~CG2DSeedFill(){}
  //���л�
  virtual void Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
      ar << mSeed.x() << mSeed.y();
    } else {
      ar >> mSeed.x() >> mSeed.y();
    }
  }
  void setBounaryColor(unsigned int color) { mBounaryColor = color; }
  int BounaryColor() const { return mBounaryColor; }
  void setAlog(unsigned int Alog) {

    switch (Alog) {
      case 2:  //����߽�4
        mdir = 4;
        mAlog = true;
        break;
      case 3:  //�����ڵ�4
        mdir = 4;
        mAlog = false;
        break;
      case 4:  //����߽�8
        mdir = 8;
        mAlog = true;
        break;
      case 5:  //�����ڵ�8
        mdir = 8;
        mAlog = false;
        break;
      default:  //������Ĭ�ϵ����ڵ�4
        mdir = 4;
        mAlog = false;
        break;
    }
  }
  int dirnum() const { return mdir; }

 public:
  virtual void Render(CGRenderContext* pRC);

 protected:
  Vec2d mSeed;
  unsigned int mBounaryColor;
  int mdir;
  bool mAlog;
};