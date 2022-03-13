#include "pch.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"

CGDI2DRenderContext::CGDI2DRenderContext() {}
CGDI2DRenderContext::CGDI2DRenderContext(CGDI2DView* pView)
    : CGRenderContext(pView) {}
CGDI2DRenderContext::~CGDI2DRenderContext() {}