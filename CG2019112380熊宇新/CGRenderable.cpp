#include "pch.h"
#include "CGRenderable.h"


IMPLEMENT_SERIAL(CGRenderable, CGObject, 1)
CGRenderable::CGRenderable()
    : CGObject(CString("CGRenderable")),
      mScene(nullptr),
      mLayer(nullptr),
      mGroup(nullptr),
      mParent(nullptr) {
  mBoundsDirty = true;
}
CGRenderable::CGRenderable(const CString& name)
    : CGObject(CString(name)),
      mScene(nullptr),
      mLayer(nullptr),
      mGroup(nullptr),
      mParent(nullptr) {
  mBoundsDirty = true;
}
CGRenderable::~CGRenderable() {}
void CGRenderable::setParent(CGRenderable* p) {
  mParent = p;
}
CGRenderable* CGRenderable::parent() const {
  return mParent;
}
void CGRenderable::setGroup(CGGroup* p) {
  mGroup = p;
}
CGGroup* CGRenderable::group() const {
  return mGroup;
}
void CGRenderable::setLayer(CGLayer* lay) {
  mLayer = lay;
}
CGLayer* CGRenderable::layer() const {
  return mLayer;
}
void CGRenderable::addToScene(CGScene* s) {
  mScene = s;
}
CGScene* CGRenderable::scene() const {
  return mScene;
}
//序列化
void CGRenderable::Serialize(CArchive& ar) {
  CGObject::Serialize(ar);
}
void CGRenderable::Render(CGRenderContext* pRC) {
  //派生类中实现
}
//二维图形对象的几何变换
void CGRenderable::Translate(double tx, double ty)  //平移
{
  //派生类中实现
}
void CGRenderable::Rotate(double angle,
                          double cx,
                          double cy)  //旋转（逆时针为正，度）
{
  //派生类中实现
}
void CGRenderable::Scale(double sx, double sy)  //缩放
{
  //派生类中实现
}
void CGRenderable::MirrorXAxis()  //关于X轴对称（二维、三维）
{
  //派生类中实现
}
void CGRenderable::MirrorYAxis()  //关于Y轴对称（二维、三维）
{
  //派生类中实现
}
void CGRenderable::MirrorYeqPosX()  //关于y=x对称（二维、三维）
{
  //派生类中实现
}
void CGRenderable::MirrorYeNegPX()  //关于y=-x对称（二维、三维）
{
  //派生类中实现
}
void CGRenderable::MirrorOrigin()  //关于原点对称（二维、三维）
{
  //派生类中实现
}
void CGRenderable::ShearXAxis(double shx)  //沿X轴错切
{
  //派生类中实现
}
void CGRenderable::ShearYAxis(double shy)  //沿Y轴错切
{
  //派生类中实现
}
void CGRenderable::ShearXYAxis(double shx, double shy)  //沿X、Y轴错切
{
  //派生类中实现
}
void CGRenderable::Transform(const Mat3d& mat)  //几何变换（左乘给定矩阵）
{
  //派生类中实现
}
bool CGRenderable::Clip(double xl, double yb, double xr,
                        double yt,CGRenderContext* pRC)  //矩形裁剪窗口
{
  return false;
}
//任意多边形裁剪窗口
bool CGRenderable::Clip(const Vec2dArry& clipWin, CGRenderContext* pRC) {
  return false;
}  

void CGRenderable::robotReset() {}
void CGRenderable::rightArmRotate() {}
void CGRenderable::leftArmRotate() {}
void CGRenderable::rightLegRotate() {}
void CGRenderable::leftLegRotate() {}
void CGRenderable::bodyLeftRotate() {}
void CGRenderable::bodyRigRotate() {}
  void CGRenderable::_3DTranslate(double tx, double ty,double tz)  //平移
{
  //派生类中实现
}
void CGRenderable::_3DRotate(double angle,
                          double cx,
                          double cy,double cz)  //旋转（逆时针为正，度）
{
  //派生类中实现
}
void CGRenderable::_3DScale(double sx, double sy,double sz)  //缩放
{
  //派生类中实现
}