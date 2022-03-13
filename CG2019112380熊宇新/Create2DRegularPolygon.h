#ifndef _CREATE2DREGULARPOLYGON_H_INCLUDE
#define _CREATE2DREGULARPOLYGON_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Create2DRegularPolygon : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DRegularPolygon(CGView* pView = nullptr);
  ~Create2DRegularPolygon();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  CPoint m_ArrayPoint[255];  //��¼ÿ�����ߵ�
  int m_PolyCount;           //���ߵĵ�ļ���
  CPoint mCenter;            //����������м�ĵ�
  double angle;
  int flag;
};

#endif  //_CREATE2DREGULARPOLYGON_H_INCLUDE