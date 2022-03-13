#ifndef _CREATE2DLINE_H_INCLUDE
#define _CREATE2DLINE_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Create2DLine : public UIEventListener {
  friend class CGDI2DView;

 public:
  Create2DLine(CGView* pView = nullptr);
  ~Create2DLine();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
  Pos2i mTemp;
};
#endif
