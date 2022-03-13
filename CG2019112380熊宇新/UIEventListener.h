#ifndef _UIEVENTLISTENER_H_INCLUDED
#define _UIEVENTLISTENER_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
enum CommandType {
  cmdNone = 0,           //�ޣ���ʾ���ָ�룬��������ͼ
  cmd2dLineSegment = 1,  //������㡢�յ����ֱ�߶�
  cmd2dLine = 2,         //��������������޳�ֱ��
  cmd2dRay = 3,       //������㡢���򣨵ڶ���ȷ������������
  cmd2dPolyline = 4,  //��������������ֱ�߶��γ�
  cmd2dCircleCenterRadius = 10,  //Բ�ĺͰ뾶���ڶ���ȷ����������Բ
  cmd2dCricle2PDiameter = 11,  //���������γ�Բֱ��������Բ
  cmd2dCircle2PSemi =
      12,  //���������γɰ�Բ����Բ�������ɵڶ���ȷ������ʱ�뷽��
  cmd2dCricle3PCircum = 13,  //���������γ������Բ
  cmd2dCircle3PArc =
      14,  //���������γ�Բ������һ����Բ�ģ��ڶ����ǻ���㣬�����㻡�յ㣬��ʱ��
           //����
  cmd2dCircle3PFan =
      15,  //���������γ����Σ���һ����Բ�ģ��ڶ����ǻ���㣬�����㻡�յ㣬��ʱ��
           //����
  cmd2dCircle3PExArc = 16,  //���������γ����Բ��
  cmd2dCircle3PExFan = 17,  //���������γ��������
  cmd2dEllipse = 30,        //ͨ����Χ���λ�����Բ
  cmd2dEllipseArc = 31,     //������Բ��
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
  virtual int GetType() = 0;  //��������
  //����¼���������Ĭ��ʵ�֣������������Ҫ��д��
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
  //�����¼�
  virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  //ȡ��Esc
  virtual int Cancel() = 0;

 protected:
  int m_nStep;    // �����������
  CGView* mView;  // �����¼��Ĵ���
};
#endif  //_UIEVENTLISTENER_H_INCLUDED