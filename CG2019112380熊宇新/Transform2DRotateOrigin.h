#ifndef _TRANSFORM2DROTATEORIGIN_H_INCLUDE
#define _TRANSFORM2DROTATEORIGIN_H_INCLUDE
#pragma once
#include "UIEventListener.h"
class Transform2DRotateOrigin : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DRotateOrigin(CGView* pView = nullptr);
  ~Transform2DRotateOrigin();

  virtual int GetType();  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ��
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();
  //��ȡ�������γɵĽǶ�
  double GetAngle(Vec2d& mCenter, Vec2d& mStart, Vec2d& mEnd);

 protected:
  Pos2i mStart;
  Pos2i mEnd;
  bool mLButtonDown;
};

#endif  //_TRANSFORM2DROTATEORIGIN_H_INCLUDE