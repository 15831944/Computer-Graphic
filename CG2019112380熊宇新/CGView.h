#ifndef _CGVIEW_H_INCLUDED
#define _CGVIEW_H_INCLUDED
#include <afxwin.h>
#include "Vector2.h"
class CGRenderable;
class UIEventListener;
class CGRenderContext;
class CGView : public CView {
  DECLARE_DYNCREATE(CGView)
 protected:  // �������л�����
  CGView();
  // ����
 public:
	 //ͼ������
  virtual int LayerIndex();
  //��������
  virtual COLORREF PenColor();
  virtual int PenWidth();
  virtual int PenStyle();
  //��ˢ����
  virtual bool UseBrush();
  virtual COLORREF BrushColor();
  virtual int BrushIndex();
  //�����㷨
  virtual int LineAlgorithm();
  //Բ���㷨
  virtual int CircleAlgorithm();
  virtual bool addRenderable(CGRenderable* r);
  virtual bool delRenderable(CGRenderable* r);
  //����㷨
  virtual int FillAlgorithm();
  virtual int TimeChose();
  //������α���
  int RegularEdges() const;
  //�Ƿ�ѡ�������
  bool RegularPolygon() const;
  //�߽���ɫ
  COLORREF BoundColor() const;
  // �ڵ���ɫ
  COLORREF FloodColor() const;

  CGRenderContext* GetRenderContext();
  //����Ĭ���ӿڲ���
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //��Ҫ������������д�ĺ���
  virtual bool RenderScene();
  // ʵ��
 public:
  virtual ~CGView();
  // ��д
 public:
  virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
  virtual void Prompt(const CString& str);
  virtual Vec2d ViewPortToWorld(const Vec2i& p);
  virtual Vec2i WorldToViewPort(const Vec2d& p);
  //��άͼ�ζ���ļ��α任�����ѡ���еĶ���
  virtual void Translate(double tx, double ty);  //ƽ��
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //��ת����ʱ��Ϊ�����ȣ�
  virtual void Scale(double sx, double sy);  //����
  virtual void ShearXYAxis(double shx, double shy);  //��X��Y�����
  //���Բü��ã�ͨ��ͨ��������������ã����ѡ���еĶ���;
  virtual void Clip(double xl, double yb, double xr, double yt);
  //�۲죨��ά����ע����ʵ����Ҫ�������ӿڸ߿��һ�£�
  virtual void Move2DCamera(double tx, double ty);  //Ƶ�ƹ۲촰��
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //�۲촰�����½ǡ����Ͻ�
  virtual void Zoom2DCamera(double ratio);  //�����۲촰�ڵ����ű�������
  virtual void Rotate2DCamera(double angle);  //ת��������۲�����ϵ��
 protected:
  //��Ⱦ����
  CGRenderContext* m_pRenderContext;
  //��������
  UIEventListener* m_pCommand;


};
#endif  //_CGVIEW_H_INCLUDED