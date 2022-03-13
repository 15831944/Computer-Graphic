#include "pch.h"
#include "COGL3DCamera.h"
#include "Vector3.h"

IMPLEMENT_SERIAL(COGL3DCamera, CGCamera, 1)
COGL3DCamera::COGL3DCamera()
    : CGCamera(CString("COGL3DCamera")),
      wLeft(-120.0),
      wBottom(-120.0),
      wRight(120.0),
      wTop(120.0),
      wFar(100000.0),
      wNear(1000.0),
      mEyePos(300.0, 300.0, 1000.0),
      mEyeRef(0.0, 0.0, 0.0),
      mEyeUp(0.0, 1.0, 0.0)  //观察坐标系
{}
COGL3DCamera::COGL3DCamera(const CString& name)
    : CGCamera(CString(name)),
      wLeft(-120.0),
      wBottom(-120.0),
      wRight(120.0),
      wTop(120.0),
      wFar(100000.0),
      wNear(1000.0),
      mEyePos(300.0, 300.0, 1000.0),
      mEyeRef(0.0, 0.0, 0.0),
      mEyeUp(0.0, 1.0, 0.0)  //观察坐标系
{}
void COGL3DCamera::Serialize(CArchive& ar) {
  CGCamera::Serialize(ar);
  if (ar.IsStoring()) {
    ar << mEyePos.x() << mEyePos.y() << mEyePos.z();
    ar << mEyeRef.x() << mEyeRef.y() << mEyeRef.z();
    ar << mEyeUp.x() << mEyeUp.y() << mEyeUp.z();
    ar << wLeft << wRight << wBottom << wTop << wNear << wFar;
  } else {
    ar >> mEyePos.x() >> mEyePos.y() >> mEyePos.z();
    ar >> mEyeRef.x() >> mEyeRef.y() >> mEyeRef.z();
    ar >> mEyeUp.x() >> mEyeUp.y() >> mEyeUp.z();
    ar >> wLeft >> wRight >> wBottom >> wTop >> wNear >> wFar;
  }
}
void COGL3DCamera::InitCamera() {
  wLeft = -120.0;
  wBottom = -120.0;
  wRight = 120.0;
  wTop = 120.0;
  wFar = 10000.0;
  wNear = 100.0;
  mEyePos.x() = 0.0;
  mEyePos.y() = 0.0;
  mEyePos.z() = 1000.0;
  mEyeRef.x() = 0.0;
  mEyeRef.y() = 0.0;
  mEyeRef.z() = 0.0;
  mEyeUp.x() = 0.0;
  mEyeUp.y() = 1.0;
  mEyeUp.z() = 0.0;
}
void COGL3DCamera::setEyePos(double eyex, double eyey, double eyez) {
  mEyePos.x() = eyex;
  mEyePos.y() = eyey;
  mEyePos.z() = eyez;
}
void COGL3DCamera::setEyeRef(double refx, double refy, double refz) {
  mEyeRef.x() = refx;
  mEyeRef.y() = refy;
  mEyeRef.z() = refz;
}
void COGL3DCamera::setEyeUp(double upx, double upy, double upz) {
  mEyeUp.x() = upx;
  mEyeUp.y() = upy;
  mEyeUp.z() = upz;
}
void COGL3DCamera::getEyePos(double& eyex, double& eyey, double& eyez) {
  eyex = mEyePos.x();
  eyey = mEyePos.y();
  eyez = mEyePos.z();
}
void COGL3DCamera::getEyeRef(double& refx, double& refy, double& refz) {
  refx = mEyeRef.x();
  refy = mEyeRef.y();
  refz = mEyeRef.z();
}
void COGL3DCamera::getEyeUp(double& upx, double& upy, double& upz) {
  upx = mEyeUp.x();
  upy = mEyeUp.y();
  upz = mEyeUp.z();
}
void COGL3DCamera::setVCSVolume(double vleft,
                                double vbottom,
                                double vright,
                                double vtop,
                                double vnear,
                                double vfar) {
  double w = vright - vleft;
  double h = vtop - vbottom;
  double aspect = double(mViewPort.width()) / double(mViewPort.height());
  w = aspect * h;
  wBottom = vbottom;
  wTop = vtop;
  wLeft = -w / 2;
  wRight = w / 2;
  wNear = vnear;
  wFar = vfar;
}
void COGL3DCamera::getVCSVolume(double& vleft,
                                double& vbottom,
                                double& vright,
                                double& vtop,
                                double& vnear,
                                double& vfar) {
  vleft = wLeft;
  vbottom = wBottom;
  vright = wRight;
  vtop = wTop;
  vnear = wNear;
  vfar = wFar;
}
//视口（覆盖，保持高宽比）
void COGL3DCamera::setViewPortBox(int xl, int yb, int xr, int yt) {
  mViewPort.set(xl, yb, xr, yt);
  GLsizei width, height;
  GLdouble aspect;
  width = xr - xl;
  height = yt - yb;
  if (height == 0)
    height = 1;
  if (width == 0)
    width = 1;
  aspect = (GLdouble)width / (GLdouble)height;
  glViewport(xl, yb, width, height);
  double h = wTop - wBottom;
  double w = wRight - wLeft;
  if (width <= height) {
    h = w / aspect;
    wBottom = -h / 2;
    wTop = h / 2;
    wRight = w / 2;
    wLeft = -w / 2;
  } else {
    w = h * aspect;
    wRight = w / 2;
    wLeft = -w / 2;
    wBottom = -h / 2;
    wTop = h / 2;
  }
}
//取景定义，设置渲染模式下的投影变换
void COGL3DCamera::Projection(int mode /* = 0*/) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glRenderMode(GL_RENDER);
  if (mode == 0)
    glOrtho(wLeft, wRight, wBottom, wTop, wNear, wFar);
  else if (mode == 1)
    glFrustum(wLeft, wRight, wBottom, wTop, wNear, wFar);
  else
    gluOrtho2D(wLeft, wRight, wBottom, wTop);
  // gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNear, wFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(mEyePos.x(), mEyePos.y(), mEyePos.z(), mEyeRef.x(), mEyeRef.y(),
            mEyeRef.z(), mEyeUp.x(), mEyeUp.y(), mEyeUp.z());
}
void COGL3DCamera::Move3DCamera(double tx, double ty)  //频移观察窗口
{

}
void COGL3DCamera::Zoom3DCamera(double ratio)  //给定观察窗口的缩放比例
{
  wBottom *= ratio;
  wTop *=ratio;
  wLeft *=ratio ;
  wRight *=ratio;
  wNear *=ratio;
  wFar *=ratio;
}
