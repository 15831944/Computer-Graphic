#include "pch.h"
#include "COGL3DRenderContext.h"
#include "COGL3DView.h"

COGL3DRenderContext::COGL3DRenderContext() {
  bShading = false;
  bLighting = false;
  mPalette = 0;
  mBackgroundColor = RGB(0, 0, 0);
  mBackgroundDepth = 100;
}
COGL3DRenderContext::COGL3DRenderContext(COGL3DView* pView)
    : CGRenderContext(pView) {
  bShading = false;
  bLighting = false;
  mPalette = 0;
  mBackgroundColor = RGB(0, 0, 0);
  mBackgroundDepth = 10000;
  // bSelectionMode = false;
}
COGL3DRenderContext::~COGL3DRenderContext() {
  if (mPalette)
    DeleteObject(mPalette);
  ::wglMakeCurrent(NULL, NULL);
  ::wglDeleteContext(mHGLRC);
}
bool COGL3DRenderContext::SetupPixelFormat(void) {
  if (mHWND == 0)
    return false;
  if (mHDC == 0)
    mHDC = ::GetDC(mHWND);
  if (mHDC == 0)
    return false;
  PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),  // pfd结构的大小
      1,                              // 版本号
      PFD_DRAW_TO_WINDOW |            // 支持在窗口中绘图
          PFD_SUPPORT_OPENGL |        // 支持 OpenGL
          PFD_DOUBLEBUFFER,           // 双缓存模式
      PFD_TYPE_RGBA,                  // RGBA 颜色模式
      24,                             // 24 位颜色深度
      0,
      0,
      0,
      0,
      0,
      0,  // 忽略颜色位
      0,  // 没有非透明度缓存
      0,  // 忽略移位位
      0,  // 无累加缓存
      0,
      0,
      0,
      0,               // 忽略累加位
      32,              // 32 位深度缓存
      0,               // 无模板缓存
      0,               // 无辅助缓存
      PFD_MAIN_PLANE,  // 主层
      0,               // 保留
      0,
      0,
      0  // 忽略层,可见性和损毁掩模
  };
  int iPixelFormat;
  // 为设备描述表得到最匹配的像素格式
  if ((iPixelFormat = ChoosePixelFormat(mHDC, &pfd)) == 0) {
    AfxMessageBox(_T("ChoosePixelFormat Failed"), NULL, MB_OK);
    return false;
  }
  // 设置最匹配的像素格式为当前的像素格式
  if (SetPixelFormat(mHDC, iPixelFormat, &pfd) == FALSE) {
    AfxMessageBox(_T("SetPixelFormat Failed"), NULL, MB_OK);
    return false;
  }
  if (pfd.dwFlags & PFD_NEED_PALETTE)
    SetLogicalPalette();  //设置逻辑调色板
  return true;
}
void COGL3DRenderContext::SetLogicalPalette(void) {
  struct {
    WORD Version;
    WORD NumberOfEntries;
    PALETTEENTRY aEntries[256];
  } logicalPalette = {0x300, 256};
  BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
  BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
  BYTE blues[] = {0, 85, 170, 255};
  for (int colorNum = 0; colorNum < 256; ++colorNum) {
    logicalPalette.aEntries[colorNum].peRed = reds[colorNum & 0x07];
    logicalPalette.aEntries[colorNum].peGreen =
        greens[(colorNum >> 0x03) & 0x07];
    logicalPalette.aEntries[colorNum].peBlue = blues[(colorNum >> 0x06) & 0x03];
    logicalPalette.aEntries[colorNum].peFlags = 0;
  }
  mPalette = CreatePalette((LOGPALETTE*)&logicalPalette);
}
bool COGL3DRenderContext::InitRenderContext() {
  if (!SetupPixelFormat())
    return false;
  mHGLRC = ::wglCreateContext(mHDC);
  ::wglMakeCurrent(mHDC, mHGLRC);
  SetupRenderContext();
  //::wglMakeCurrent(NULL, NULL);
  return mHGLRC != 0;
}
void COGL3DRenderContext::SetupRenderContext() {
  bShading = true;
  GLfloat lightAmbient[] = {0.75f, 0.75f, 0.75f, 1.0f};
  GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  //glEnable(GL_LIGHTING);
  //glDrawBuffer(GL_BACK);
  //glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  //GLfloat lightPos[] = {1, 1, 1, 0.0f};
  //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  //glEnable(GL_LIGHT0);
}
void COGL3DRenderContext::Ready() {
  wglMakeCurrent(mHDC, mHGLRC);
  ClearBackground();
  OnShading();
}
void COGL3DRenderContext::Finish() {
  glFlush();
  SwapBuffers(mHDC);
  wglMakeCurrent(mHDC, NULL);
}
void COGL3DRenderContext::ClearBackground() {
  GLclampf r, g, b;
  r = (GLclampf)GetRValue(mBackgroundColor) / 255.0;
  g = (GLclampf)GetGValue(mBackgroundColor) / 255.0;
  b = (GLclampf)GetBValue(mBackgroundColor) / 255.0;
  glClearColor(r, g, b, 0.0f);
  glClearDepth(mBackgroundDepth);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void COGL3DRenderContext::OnShading() {
  if (bShading) {
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    // glPolygonMode第一个参数可以GL_FRONT、GL_BACK、GL_FRONT_AND_BACK
    // glPolygonMode第二个参数可以GL_POINT、GL_LINE、GL_FILL
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
}
void COGL3DRenderContext::Shading(bool shading) {
  bShading = shading;
}
bool COGL3DRenderContext::IsShading() {
  return bShading;
}
void COGL3DRenderContext::Lighting(bool lighting) {
  if (bLighting)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);
}
bool COGL3DRenderContext::IsLighting() {
  GLboolean bLighting;
  glGetBooleanv(GL_LIGHTING, &bLighting);
  return bLighting;
}