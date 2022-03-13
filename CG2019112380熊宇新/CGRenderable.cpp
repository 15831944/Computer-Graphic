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
//���л�
void CGRenderable::Serialize(CArchive& ar) {
  CGObject::Serialize(ar);
}
void CGRenderable::Render(CGRenderContext* pRC) {
  //��������ʵ��
}
//��άͼ�ζ���ļ��α任
void CGRenderable::Translate(double tx, double ty)  //ƽ��
{
  //��������ʵ��
}
void CGRenderable::Rotate(double angle,
                          double cx,
                          double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  //��������ʵ��
}
void CGRenderable::Scale(double sx, double sy)  //����
{
  //��������ʵ��
}
void CGRenderable::MirrorXAxis()  //����X��Գƣ���ά����ά��
{
  //��������ʵ��
}
void CGRenderable::MirrorYAxis()  //����Y��Գƣ���ά����ά��
{
  //��������ʵ��
}
void CGRenderable::MirrorYeqPosX()  //����y=x�Գƣ���ά����ά��
{
  //��������ʵ��
}
void CGRenderable::MirrorYeNegPX()  //����y=-x�Գƣ���ά����ά��
{
  //��������ʵ��
}
void CGRenderable::MirrorOrigin()  //����ԭ��Գƣ���ά����ά��
{
  //��������ʵ��
}
void CGRenderable::ShearXAxis(double shx)  //��X�����
{
  //��������ʵ��
}
void CGRenderable::ShearYAxis(double shy)  //��Y�����
{
  //��������ʵ��
}
void CGRenderable::ShearXYAxis(double shx, double shy)  //��X��Y�����
{
  //��������ʵ��
}
void CGRenderable::Transform(const Mat3d& mat)  //���α任����˸�������
{
  //��������ʵ��
}
bool CGRenderable::Clip(double xl, double yb, double xr,
                        double yt,CGRenderContext* pRC)  //���βü�����
{
  return false;
}
//�������βü�����
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
  void CGRenderable::_3DTranslate(double tx, double ty,double tz)  //ƽ��
{
  //��������ʵ��
}
void CGRenderable::_3DRotate(double angle,
                          double cx,
                          double cy,double cz)  //��ת����ʱ��Ϊ�����ȣ�
{
  //��������ʵ��
}
void CGRenderable::_3DScale(double sx, double sy,double sz)  //����
{
  //��������ʵ��
}