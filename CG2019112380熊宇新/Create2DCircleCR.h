#ifndef _CREATE2DCIRCLECENTERRADIUS_H_INCLUDE
#define _CREATE2DCIRCLECENTERRADIUS_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Create2DCircleCR : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DCircleCR(CGView* pView = nullptr);
  ~Create2DCircleCR();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  Pos2i mCenter;
  double Radius;
  Pos2i Upperleft;
  Pos2i Lowerright;
};
#endif  //_CREATE2DCIRCLECENTERRADIUS_H_INCLUDE
