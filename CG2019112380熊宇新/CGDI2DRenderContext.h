#ifndef _CGDI2DRENDERCONTEXT_H_INCLUDED
#define _CGDI2DRENDERCONTEXT_H_INCLUDED
#include "CGRenderContext.h"
class CGDI2DView;
class CGDI2DRenderContext : public CGRenderContext {
 public:
  CGDI2DRenderContext();
  CGDI2DRenderContext(CGDI2DView* pView);
  virtual ~CGDI2DRenderContext();
  //自定义内容
 protected:
};
#endif  //_CGDI2DRENDERCONTEXT_H_INCLUDED