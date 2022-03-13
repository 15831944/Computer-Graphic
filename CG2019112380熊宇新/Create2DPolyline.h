#ifndef _CREATE2DPolyline_H_INCLUDE
#define _CREATE2DPolyline_H_INCLUDE
#pragma once
#include "UIEventListener.h"

class Create2DPolyline : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DPolyline(CGView* pView = nullptr);
  ~Create2DPolyline();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int OnRButtonDown(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  CPoint m_ArrayPoint[255];  //��¼ÿ�����ߵ�
  int m_PolyCount;           //���ߵĵ�ļ���
  CPoint m_ptPolyFirst;      //�����е�һ����
  CPoint m_ptPolyLast;       //���������һ����
  CPoint m_PointOld;         //��Ƥ���е����һ����
};
#endif  //_CREATE2DPolyLine_H_INCLUDE
