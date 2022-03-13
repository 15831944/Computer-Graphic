#ifndef _RECTCLIP2DRENDERABLE_H_INCLUDED
#define _RECTCLIP2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
class Transform2DClip : public UIEventListener {
  friend class CGDI2DView;

 public:
  Transform2DClip(CGView* pview = nullptr);
  ~Transform2DClip();
  virtual int GetType();  //��������
  //����¼�( ������Ĭ��ʵ�֣������������Ҫ��д)
  //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
  virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
  virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
  //ȡ��Esc
  virtual int Cancel();

 protected:
  Pos2i mStart;
  Pos2i mEnd;
};
#endif  //_RECTCLIP2DRENDERABLE_H_INCLUDED
