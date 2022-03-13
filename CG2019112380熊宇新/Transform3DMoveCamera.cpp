   #include "pch.h"
#include "COGL3DView.h"
#include "Transform3DMoveCamera.h"

Transform3DMoveCamera::Transform3DMoveCamera(CGView* pview /* = nullptr*/)
    : UIEventListener(pview) {
  m_nStep = 0;
  mPoint.x() = 0;
  mPoint.y() = 0;
  mLButtonDown = false;
}
Transform3DMoveCamera::~Transform3DMoveCamera() {}
int Transform3DMoveCamera::GetType()  //ÃüÁîÀàÐÍ
{
  return cmd3dMoveCamera;
}
int Transform3DMoveCamera::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  mLButtonDown = true;
  mPoint.x() = pos.x();
  mPoint.y() = pos.y();
  return 0;
}
int Transform3DMoveCamera::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
  mLButtonDown = false;
  return 0;
}
int Transform3DMoveCamera::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr || mLButtonDown == false)
    return -1;
  float yaw, pitch;
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  yaw = (pos.x() - mPoint.x()) / 2;

  pitch = -1 * (pos.y() - mPoint.y()) / 2;

  mPoint.x() = pos.x();
  mPoint.y() = pos.y();
  return 0;
}
int Transform3DMoveCamera::Cancel() {
  if (mView == nullptr)
    return -1;
  m_nStep = 0;
  mView->Prompt(_T("¾ÍÐ÷"));
  return 0;
}
