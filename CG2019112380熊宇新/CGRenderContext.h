#ifndef _CGRENDERCONTEXT_H_INCLUDED
#define _CGRENDERCONTEXT_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
class CGView;
class CGRenderContext : public CGObject {
 public:
  CGRenderContext();
  CGRenderContext(CGView* pView);
  virtual ~CGRenderContext();
  void setView(CGView* pView);
  CGView* getView() const;
  //�Զ�������

  //ֱ�߻����㷨
  void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color);               
  void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color);
  void BresehamLine(const Vec2i& start, const Vec2i& end, unsigned long color);

  //Բ�����㷨
  void MidPointCircle(const Vec2i& center, int radius, unsigned long color);
  void BresehamCircle(const Vec2i& center, int radius, unsigned long color);

  //����߽�4
  void BoundaryFill4(int x, int y, unsigned int fill, int boundary);
  //�����ڵ�4
  void FloodFill4(int x, int y, unsigned int fillColor, unsigned int oldColor);
  //����߽�8
  void BoundaryFill8(int x, int y, unsigned int fill, int boundary);
  //�����ڵ�8
  void FloodFill8(int x, int y, unsigned int fillColor, unsigned int oldColor);

  void SeedFill_Boundary(const Vec2i seed,
                         unsigned long fill,
                         unsigned long boundary,
                         int dir);
  void SeedFill_Point(const Vec2i seed, unsigned long fill, int dir);

  //ֱ�߶βü��㷨��ʹ�ý��������ü����ڶ�ѡ�е��߶ν��вü���
  // Cohen-Sutherland�����룩ֱ�߶βü�
  // xl��yb��xr��yt��Ӧ�ü����ڵ����¡��ҡ��ϡ�s��e�����߶�����յ㣬rs��re�ü�������ޣ��򷵻�false������ ����true
  bool CohenSutherlandLineClip(double xl, double yb,double xr,double yt,const Vec2d& s,
                               const Vec2d& e, Vec2d& rs, Vec2d& re);

 protected:
  CGView* mView;
  HWND mHWND;  //ͨ��mView����
  HDC mHDC;    //ͨ��mView����
  HGLRC mHGLRC; //ͨ��mView����
  //

 private:
  int xmax;
  int ymax;

 public:
  //��������
  HWND GetHWND() const { return mHWND; }
  HDC GetHDC() const { return mHDC; }
  HGLRC GetHGLRC() const { return mHGLRC; }
  ///��άͼ��
  virtual bool InitRenderContext();
  virtual void SetupRenderContext();
  virtual void Ready();
  virtual void Finish();
};
#endif  //_CGRENDERCONTEXT_H_INCLUDED
