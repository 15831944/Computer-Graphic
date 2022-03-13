#ifndef _CGRENDERABLE_H_INCLUDED
#define _CGRENDERABLE_H_INCLUDED
#include "CGObject.h"
#include"Vector2.h"
#include"Matrix33.h"
#include"AABBox2.h"
class CGScene;
class CGLayer;
class CGGroup;
class CGRenderContext;
class CGRenderable : public CGObject {
  DECLARE_SERIAL(CGRenderable)
 public:
  CGRenderable();
  CGRenderable(const CString& name);
  virtual ~CGRenderable();
  //���л�
  virtual void Serialize(CArchive& ar);
  void setParent(CGRenderable* p);
  CGRenderable* parent() const;
  void setGroup(CGGroup* p);
  CGGroup* group() const;
  void setLayer(CGLayer* lay);
  CGLayer* layer() const;
  void addToScene(CGScene* s);
  CGScene* scene() const;
  // ����״̬���壨Ҳ����ö�����ͣ� 
  static const int statusNormal =0;     //����״̬
  static const int statusSelected = 1;  //ѡ��״̬
  int status() const { return mStatus; }
  void setStatus(int s) { mStatus = s; }

  //�����Χ���Ƿ���Ҫ���¼���
  bool boundsDirty() const { return mBoundsDirty; }
  void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
  ABox2d& BoundingABox() { return ABox2d(); }

 public:
  virtual void Render(CGRenderContext* pRC);

  //��άͼ�ζ���ļ��α任
  virtual void Translate(double tx, double ty);  //ƽ��
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //��ת����ʱ��Ϊ�����ȣ�
  virtual void Scale(double sx, double sy);  //����
  virtual void MirrorXAxis();    //����X��Գƣ���ά����ά��
  virtual void MirrorYAxis();    //����Y��Գƣ���ά����ά��
  virtual void MirrorYeqPosX();  //����y=x�Գƣ���ά����ά��
  virtual void MirrorYeNegPX();  //����y=-x�Գƣ���ά����ά��
  virtual void MirrorOrigin();   //����ԭ��Գƣ���ά����ά��
  virtual void ShearXAxis(double shx);               //��X�����
  virtual void ShearYAxis(double shy);               //��Y�����
  virtual void ShearXYAxis(double shx, double shy);  //��X��Y�����
  virtual void Transform(const Mat3d& mat);  //���α任����˸�������
  virtual bool Clip(double xl,
                    double yb,
                    double xr,
                    double yt,
                    CGRenderContext* pRC);  //���βü�����
  virtual bool Clip(const Vec2dArry& clipWin,
                    CGRenderContext* pRC);  //�������βü�����

    virtual void robotReset();
  virtual void rightArmRotate();
  virtual void leftArmRotate();
  virtual void rightLegRotate();
  virtual void leftLegRotate();
  virtual void bodyLeftRotate();
  virtual void bodyRigRotate();
  virtual void _3DTranslate(double tx, double ty, double tz);  //ƽ��
  virtual void _3DRotate(double angle,
                      double cx,
                      double cy,
                      double cz);  //��ת����ʱ��Ϊ�����ȣ�
  virtual void _3DScale(double sx, double sy, double sz);  //����
 protected:
  CGScene* mScene;  //����ʵ�������ĳ�������������볡��ʱ�Զ��������á�
  CGLayer* mLayer;        //����ʵ��������ͼ��
  CGGroup* mGroup;        //����ʵ��������ͼ��
  CGRenderable* mParent;  //
  CTypedPtrArray<CObArray, CGRenderable*> mChildren;
  bool mBrushUse;
  void setBrushUse(bool use);
  void brushUse() const;
  int mStatus = 0;
  bool mBoundsDirty;  //��Χ���Ƿ��Ѹı�
  
};
#endif  //_CGRENDERABLE_H_INCLUDED