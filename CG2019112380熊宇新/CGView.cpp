#include "pch.h"
#include "CGView.h"
#include"CGRenderable.h"
#include"CGRenderContext.h"
#include"UIEventListener.h"

IMPLEMENT_DYNCREATE(CGView, CView)
CGView::CGView() {
  m_pRenderContext = nullptr;  // �������г�ʼ�� new CGRenderContext(this);
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
  //��������ʵ��
}
CGRenderContext* CGView::GetRenderContext() {
  return m_pRenderContext;
}
//����Ĭ���ӿڲ���
bool CGView::setDefaultViewPort(int xl, int yb, int xr, int yt) {
  //��������ʵ��
  return false;
}
bool CGView::RenderScene() {
  //��������ʵ��
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

//ͼ������
int CGView::LayerIndex() {
  //��������ʵ��
  return 0;
}
//��������
COLORREF CGView::PenColor() {
  //��������ʵ��
  return RGB(0, 0, 0);
}
int CGView::PenWidth() {
  //��������ʵ��
  return 1;
}
int CGView::PenStyle() {
  //��������ʵ��
  return PS_SOLID;
}
//��ˢ����
bool CGView::UseBrush() {
  //��������ʵ��
  return false;
}
COLORREF CGView::BrushColor() {
  //��������ʵ��
  return RGB(255, 255, 255);
}
int CGView::BrushIndex() {
  //��������ʵ��
  return 0;
}
//�����㷨
int CGView::LineAlgorithm() {
  //��������ʵ��
  return 0;
}
//Բ���㷨
int CGView::CircleAlgorithm() {
  //��������ʵ��
  return 0;
}
//ͼ�ζ�����ӵ�����
bool CGView::addRenderable(CGRenderable* r) {
  //��������ʵ��
  return false;
}
bool CGView::delRenderable(CGRenderable* r) {
  //��������ʵ��
  return false;
}
//����㷨
int CGView::FillAlgorithm() {
  //��������ʵ��
  return 0;
}
int CGView::TimeChose() {
  //��������ʵ��
  return 0;
}
//�Ƿ�ѡ�������
bool CGView::RegularPolygon() const {
  //��������ʵ��
  return false;
}
//������α���
int CGView::RegularEdges() const {
  //��������ʵ��
  return 3;
}
//��������ı߽���ɫ
COLORREF CGView::BoundColor() const {
  //��������ʵ��
  return RGB(0, 0, 0);
}
//����������ڵ���ɫ
COLORREF CGView::FloodColor() const {
  //��������ʵ��
  return RGB(255, 255, 255);
}

//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
void CGView::Translate(double tx, double ty)  //ƽ��
{
  //��������ʵ��
}
void CGView::Rotate(double angle,
                    double cx,
                    double cy)  //��ת����ʱ��Ϊ�����ȣ�
{
  //��������ʵ��
}
void CGView::Scale(double sx, double sy)  //����
{
  //��������ʵ��
}
void CGView::ShearXYAxis(double shx, double shy)  //��X��Y�����
{
  //��������ʵ��
}
void CGView::Clip(double xl, double yb, double xr, double yt) {

}
// �۲죨��ά����ע����ʵ����Ҫ�������ӿڸ߿��һ�£�
void CGView::Move2DCamera(double tx, double ty)  //Ƶ�ƹ۲촰��
{
  //��������ʵ��
}
void CGView::Zoom2DCamera(const Vec2d& lb,
                          const Vec2d& rt)  //�۲촰�����½ǡ�����
{
  //��������ʵ��
}
void CGView::Zoom2DCamera(double ratio)  //�����۲촰�ڵ����ű�����
{
  //��������ʵ��
}
void CGView::Rotate2DCamera(double angle)  //ת��������۲�����ϵ)
{
  //��������ʵ��
}