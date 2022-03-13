#ifndef _CREATE2DCIRCLE3PARC_H_INCLUDE
#define _CREATE2DCIRCLE3PARC_H_INCLUDE
#pragma once
#include "UIEventListener.h"
//����Բ��
class Create2DCircle3PArc : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DCircle3PArc(CGView* pView = nullptr);
  ~Create2DCircle3PArc();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  Pos2i mCenter;
  Pos2i mStart;
  Pos2i mEnd;
  double Radius;
  Pos2i Upperleft;
  Pos2i Lowerright;
};
#endif  //_CREATE2DCIRCLE3PARC_H_INCLUDE
