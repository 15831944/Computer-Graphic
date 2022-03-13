#ifndef _UIEVENTLISTENER_H_INCLUDED
#define _UIEVENTLISTENER_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
enum CommandType {
  cmdNone = 0,           //无，显示鼠标指针，不交互画图
  cmd2dLineSegment = 1,  //利用起点、终点绘制直线段
  cmd2dLine = 2,         //启用两点绘制无限长直线
  cmd2dRay = 3,       //利用起点、方向（第二点确定）绘制射线
  cmd2dPolyline = 4,  //折线连续相连的直线段形成
  cmd2dCircleCenterRadius = 10,  //圆心和半径（第二点确定）绘制整圆
  cmd2dCricle2PDiameter = 11,  //利用两点形成圆直径绘制整圆
  cmd2dCircle2PSemi =
      12,  //利用两点形成半圆弧（圆弧方向由第二点确定，逆时针方向）
  cmd2dCricle3PCircum = 13,  //输入三点形成外接整圆
  cmd2dCircle3PArc =
      14,  //利用三点形成圆弧（第一点是圆心，第二点是弧起点，第三点弧终点，逆时针
           //方向）
  cmd2dCircle3PFan =
      15,  //利用三点形成扇形（第一点是圆心，第二点是弧起点，第三点弧终点，逆时针
           //方向）
  cmd2dCircle3PExArc = 16,  //利用三点形成外接圆弧
  cmd2dCircle3PExFan = 17,  //利用三点形成外接扇形
  cmd2dEllipse = 30,        //通过包围矩形绘制椭圆
  cmd2dEllipseArc = 31,     //绘制椭圆弧
  cmd2dRectangle = 40,
  cmd2dPolygon = 41,
  cmd2dRegularPolygon = 42,
  cmd2dSeedFill = 43,
  cmd2dTranslate = 44,
  cmd2dRotateOrigin = 45,
  cmd2dClip = 46,
  cmd2dMoveCamera = 47,
  cmd2dRotateCamera = 48,
  cmd2dClock = 49,

  cmd3dMoveCamera = 50,
  cmdUnknown = 1000
};
class UIEventListener : public CGObject {
  friend class CGView;

 public:
  UIEventListener(CGView* pview = nullptr);
  ~UIEventListener();
  virtual int GetType() = 0;  //命令类型
  //鼠标事件（都给出默认实现，派生类根据需要重写）
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonDblClk(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseWheel(UINT nFlags, short zDelta, Pos2i pt);
  virtual int OnMButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnMButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMButtonDblClk(UINT nFlags, const Pos2i& pos);
  virtual int OnRButtonUp(UINT nFlags, const Pos2i& pos);
  virtual int OnRButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnRButtonDblClk(UINT nFlags, const Pos2i& pos);
  //键盘事件
  virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  //取消Esc
  virtual int Cancel() = 0;

 protected:
  int m_nStep;    // 命令操作计数
  CGView* mView;  // 处理事件的窗口
};
#endif  //_UIEVENTLISTENER_H_INCLUDED