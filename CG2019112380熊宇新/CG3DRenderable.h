#pragma once
#ifndef _CG3DRENDERABLE_H_INCLUDED
#define _CG3DRENDERABLE_H_INCLUDED
//#include "AABBox3.h"
#include "CGRenderable.h"
class CG3DRenderable : public CGRenderable {
  DECLARE_SERIAL(CG3DRenderable)
 public:
  CG3DRenderable();
  CG3DRenderable(const CString& name);
  virtual ~CG3DRenderable();
  //–Ú¡–ªØ
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  void setDrawStyle(int style) { mDrawStyle = style; }
  int getDrawStyle() const { return mDrawStyle; }

 protected:
  int mDrawStyle;
};
#endif  //_CG3DRENDERABLE_H_INCLUDED