#include "pch.h"
#include "CGView.h"
#include"CGRenderable.h"
#include"CGRenderContext.h"
#include"UIEventListener.h"

IMPLEMENT_DYNCREATE(CGView, CView)
CGView::CGView() {
  m_pRenderContext = nullptr;  // 派生类中初始化 new CGRenderContext(this);
  m_pCommand = nullptr;
}
CGView::~CGView() {
  if (m_pRenderContext != nullptr) {
    delete m_pRenderContext;
    m_pRenderContext = nullptr;
  }
  if (m_pCommand != nullptr) {
    m_pCommand->Cancel();
    delete m_pCommand;
    m_pCommand = nullptr;
  }
}
void CGView::OnDraw(CDC* pDC) {
  //派生类中实现
}
CGRenderContext* CGView::GetRenderContext() {
  return m_pRenderContext;
}
//设置默认视口参数
bool CGView::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  //派生类中实现
  return false;
}
bool CGView::RenderScene() {
  //派生类中实现
  return false;
}

void CGView::Prompt(const CString& str) {
  UNUSED(str);
}

Vec2d CGView::ViewPortToWorld(const Vec2i& p) {
  return Vec2d();
}

Vec2i CGView::WorldToViewPort(const Vec2d& p) {
  return Vec2i();
}

//图层属性
int CGView::LayerIndex() {
  //派生类中实现
  return 0;
}
//画笔属性
COLORREF CGView::PenColor() {
  //派生类中实现
  return RGB(0, 0, 0);
}
int CGView::PenWidth() {
  //派生类中实现
  return 1;
}
int CGView::PenStyle() {
  //派生类中实现
  return PS_SOLID;
}
//画刷属性
bool CGView::UseBrush() {
  //派生类中实现
  return false;
}
COLORREF CGView::BrushColor() {
  //派生类中实现
  return RGB(255, 255, 255);
}
int CGView::BrushIndex() {
  //派生类中实现
  return 0;
}
//画线算法
int CGView::LineAlgorithm() {
  //派生类中实现
  return 0;
}
//圆弧算法
int CGView::CircleAlgorithm() {
  //派生类中实现
  return 0;
}
//图形对象添加到场景
bool CGView::addRenderable(CGRenderable* r) {
  //派生类中实现
  return false;
}
bool CGView::delRenderable(CGRenderable* r) {
  //派生类中实现
  return false;
}
//填充算法
int CGView::FillAlgorithm() {
  //派生类中实现
  return 0;
}
int CGView::TimeChose() {
  //派生类中实现
  return 0;
}
//是否勾选正多边形
bool CGView::RegularPolygon() const {
  //派生类中实现
  return false;
}
//正多边形边数
int CGView::RegularEdges() const {
  //派生类中实现
  return 3;
}
//点阵区域的边界颜色
COLORREF CGView::BoundColor() const {
  //派生类中实现
  return RGB(0, 0, 0);
}
//点阵区域的内点颜色
COLORREF CGView::FloodColor() const {
  //派生类中实现
  return RGB(255, 255, 255);
}

//二维图形对象的几何变换（针对选择集中的对象）
void CGView::Translate(double tx, double ty)  //平移
{
  //派生类中实现
}
void CGView::Rotate(double angle,
                    double cx,
                    double cy)  //旋转（逆时针为正，度）
{
  //派生类中实现
}
void CGView::Scale(double sx, double sy)  //缩放
{
  //派生类中实现
}
void CGView::ShearXYAxis(double shx, double shy)  //沿X、Y轴错切
{
  //派生类中实现
}
void CGView::Clip(double xl, double yb, double xr, double yt) {

}
// 观察（二维）（注意在实现中要保持与视口高宽比一致）
void CGView::Move2DCamera(double tx, double ty)  //频移观察窗口
{
  //派生类中实现
}
void CGView::Zoom2DCamera(const Vec2d& lb,
                          const Vec2d& rt)  //观察窗口左下角、右上
{
  //派生类中实现
}
void CGView::Zoom2DCamera(double ratio)  //给定观察窗口的缩放比例（
{
  //派生类中实现
}
void CGView::Rotate2DCamera(double angle)  //转动相机（观察坐标系)
{
  //派生类中实现
}