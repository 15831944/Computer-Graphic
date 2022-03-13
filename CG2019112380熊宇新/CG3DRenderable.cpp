#include "pch.h"
#include "CG3DRenderable.h"

IMPLEMENT_SERIAL(CG3DRenderable, CGRenderable, 1)
CG3DRenderable::CG3DRenderable() : CGRenderable(CString("CG3DRenderable")) {}
CG3DRenderable::CG3DRenderable(const CString& name)
    : CGRenderable(CString(name)) {}
CG3DRenderable::~CG3DRenderable() {}
//序列化
void CG3DRenderable::Serialize(CArchive& ar) {
  CGRenderable::Serialize(ar);
  if (ar.IsStoring()) {
    // ar << ;
  } else {
    // ar >> ;
  }
}
void CG3DRenderable::Render(CGRenderContext* pRC) {
  //派生类中实现
}