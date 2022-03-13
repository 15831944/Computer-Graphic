#ifndef _CREATE2DCIRCLE3PCircum_H_INCLUDE
#define _CREATE2DCIRCLE3PCircum_H_INCLUDE
#pragma once
#include "UIEventListener.h"
//���㻭Բ
class Create2DCircle3P : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DCircle3P(CGView* pView = nullptr);
  ~Create2DCircle3P();

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
  Pos2i mStart;
  Pos2i mMiddle;
  Pos2i mEnd;
  Pos2i Upperleft;
  Pos2i Lowerright;
  int flag = -1;
};
#endif  //_CREATE2DCIRCLE3PCircum_H_INCLUDE