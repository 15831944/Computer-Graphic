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
  //自定义内容

  //直线绘制算法
  void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color);               
  void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color);
  void BresehamLine(const Vec2i& start, const Vec2i& end, unsigned long color);

  //圆绘制算法
  void MidPointCircle(const Vec2i& center, int radius, unsigned long color);
  void BresehamCircle(const Vec2i& center, int radius, unsigned long color);

  //点阵边界4
  void BoundaryFill4(int x, int y, unsigned int fill, int boundary);
  //点阵内点4
  void FloodFill4(int x, int y, unsigned int fillColor, unsigned int oldColor);
  //点阵边界8
  void BoundaryFill8(int x, int y, unsigned int fill, int boundary);
  //点阵内点8
  void FloodFill8(int x, int y, unsigned int fillColor, unsigned int oldColor);

  void SeedFill_Boundary(const Vec2i seed,
                         unsigned long fill,
                         unsigned long boundary,
                         int dir);
  void SeedFill_Point(const Vec2i seed, unsigned long fill, int dir);

  //直线段裁剪算法（使用交互命令构造裁剪窗口对选中的线段进行裁剪）
  // Cohen-Sutherland（编码）直线段裁剪
  // xl、yb、xr、yt对应裁剪窗口的左、下、右、上。s、e输入线段起点终点，rs、re裁剪结果，无，则返回false，有则 返回true
  bool CohenSutherlandLineClip(double xl, double yb,double xr,double yt,const Vec2d& s,
                               const Vec2d& e, Vec2d& rs, Vec2d& re);

 protected:
  CGView* mView;
  HWND mHWND;  //通过mView设置
  HDC mHDC;    //通过mView设置
  HGLRC mHGLRC; //通过mView设置
  //

 private:
  int xmax;
  int ymax;

 public:
  //辅助函数
  HWND GetHWND() const { return mHWND; }
  HDC GetHDC() const { return mHDC; }
  HGLRC GetHGLRC() const { return mHGLRC; }
  ///三维图形
  virtual bool InitRenderContext();
  virtual void SetupRenderContext();
  virtual void Ready();
  virtual void Finish();
};
#endif  //_CGRENDERCONTEXT_H_INCLUDED
