#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "CGObject.h"
#include "Matrix33.h"
#include "Vector2.h"
#include"AABBox2.h"
class CGRenderable;
class CGLayer;
class CGCamera;
class CGView;
class CGGroup;
class CGRenderContext;
class CGScene : public CGObject {
  DECLARE_SERIAL(CGScene)
 public:
  CGScene();
  virtual ~CGScene();
  virtual void Serialize(CArchive& ar);

  CGRenderable* getRenderable(unsigned int index);


  //ͼ�ζ���
  bool addRenderable(CGRenderable*);
  CGRenderable* detachRenderable(CGRenderable*);
  bool delRenderable(CGRenderable*);
  void removeAllRenderable();
  CGCamera* defaultCamera() const;
  //ͼ�ζ���ѡȡ������������
  CGRenderable* RenderableSelectedByName(const CString& name);
  bool RenderableUnselectByName(const CString& name);
  bool RenderableUnselect(CGRenderable* r);
  void RenderableUnselectAll();

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
  //���Բü��ã�ͨ���ĵ�����ã�;
  virtual void Clip(double xl,
                    double yb,
                    double xr,
                    double yt,
                    CGRenderContext* pRC);

  //����Ĭ���ӿڲ���
  bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  // ����Ĭ�Ϲ۲촰�ڲ���
  bool setDefaultWindow(double xl, double yb, double xr, double yt);
  //��Ⱦ������ָ���ͻ������ͻ������������ӿڣ���ÿ���ӿڶ�Ӧһ�������
  virtual bool RenderScene(CGView* pView);  //Ӧ����������д
  //�۲죨��ά����ע����ʵ����Ҫ�������ӿڸ߿��һ�£�
  virtual void Move2DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //�۲촰�����½ǡ����Ͻ�
  virtual void Zoom2DCamera(double ratio);  //�����۲촰�ڵ����ű�������
  virtual void Rotate2DCamera(double angle);  //ת��������۲�����ϵ��
  virtual ABox2d ComputeBounds();  //���㳡���İ�Χ�У�����ȫ��

  	//�����ӿ������ȡ��Ӧ�������꣨��ά���C����Ĭ���������ViewtoWorld
  Vec2d ViewPortToWorld(const Vec2i& p);
  double LengthViewPortToWorld(const double p);
  double RadViewPortToWorld(const double p);
  Vec2i WorldToViewPort(const Vec2d& p);
  double LengthWorldToViewPort(const double p);
  double RadWorldToViewPort(const double p);

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
   virtual void Move3DCamera(double tx, double ty);         //Ƶ�ƹ۲촰��
   virtual void Zoom3DCamera(double ratio);  //�����۲촰�ڵ����ű���
   virtual void Rotate3DCamera(double angle);  //ת��������۲�����ϵ)
   virtual void setProjection(int mode);
  /* virtual void setfocalDis(int dis);*/
   virtual void setEyePos(double eyex, double eyey, double eyez);

  protected:
   int projectionMode = 0;

 protected:
  //ͼ�ζ���ѡ��
  CTypedPtrArray<CObArray, CGRenderable*> mSelections;
  //ͼ������б��������󣬲���������
  CMapStringToOb mLayers;
  // CTypedPtrArray<CObArray, CGLayer*> mLayers;
  //ͼ������б��������󣬲���������
  CMapStringToOb mGroups;
  // CTypedPtrArray<CObArray, CGGroup*> mGroups;
  //Ĭ�����
  CGCamera* mDefaultCamera;
  //����������������󣬲���������
  CMapStringToOb mCameras;
  // CTypedPtrArray<CObArray, CGCamera*> mCameras;
  //ͼ�ζ����б�
  // CMapStringToOb mRenderables; 
  //���ڼ���Ƿ�����
  CTypedPtrArray<CObArray, CGRenderable*> mRenderables;
};
#endif  //_CGSCENE_H_INCLUDED