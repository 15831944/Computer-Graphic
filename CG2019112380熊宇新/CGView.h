#ifndef _CGVIEW_H_INCLUDED
#define _CGVIEW_H_INCLUDED
#include <afxwin.h>
#include "Vector2.h"
class CGRenderable;
class UIEventListener;
class CGRenderContext;
class CGView : public CView {
  DECLARE_DYNCREATE(CGView)
 protected:  // 仅从序列化创建
  CGView();
  // 操作
 public:
	 //图层属性
  virtual int LayerIndex();
  //画笔属性
  virtual COLORREF PenColor();
  virtual int PenWidth();
  virtual int PenStyle();
  //画刷属性
  virtual bool UseBrush();
  virtual COLORREF BrushColor();
  virtual int BrushIndex();
  //画线算法
  virtual int LineAlgorithm();
  //圆弧算法
  virtual int CircleAlgorithm();
  virtual bool addRenderable(CGRenderable* r);
  virtual bool delRenderable(CGRenderable* r);
  //填充算法
  virtual int FillAlgorithm();
  virtual int TimeChose();
  //正多边形边数
  int RegularEdges() const;
  //是否勾选正多边形
  bool RegularPolygon() const;
  //边界颜色
  COLORREF BoundColor() const;
  // 内点颜色
  COLORREF FloodColor() const;

  CGRenderContext* GetRenderContext();
  //设置默认视口参数
  virtual bool setDefaultViewPort(int xl, int yb, int xr, int yt);
  //需要在派生类中重写的函数
  virtual bool RenderScene();
  // 实现
 public:
  virtual ~CGView();
  // 重写
 public:
  virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
  virtual void Prompt(const CString& str);
  virtual Vec2d ViewPortToWorld(const Vec2i& p);
  virtual Vec2i WorldToViewPort(const Vec2d& p);
  //二维图形对象的几何变换（针对选择集中的对象）
  virtual void Translate(double tx, double ty);  //平移
  virtual void Rotate(double angle,
                      double cx,
                      double cy);            //旋转（逆时针为正，度）
  virtual void Scale(double sx, double sy);  //缩放
  virtual void ShearXYAxis(double shx, double shy);  //沿X、Y轴错切
  //测试裁剪用（通过通过交互命令类调用，针对选择集中的对象）;
  virtual void Clip(double xl, double yb, double xr, double yt);
  //观察（二维）（注意在实现中要保持与视口高宽比一致）
  virtual void Move2DCamera(double tx, double ty);  //频移观察窗口
  virtual void Zoom2DCamera(const Vec2d& lb,
                            const Vec2d& rt);  //观察窗口左下角、右上角
  virtual void Zoom2DCamera(double ratio);  //给定观察窗口的缩放比例（）
  virtual void Rotate2DCamera(double angle);  //转动相机（观察坐标系）
 protected:
  //渲染环境
  CGRenderContext* m_pRenderContext;
  //交互命令
  UIEventListener* m_pCommand;


};
#endif  //_CGVIEW_H_INCLUDED