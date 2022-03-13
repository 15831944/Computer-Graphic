#include "pch.h"
#include "CGRenderContext.h"
#include "CGView.h"


CGRenderContext::CGRenderContext() {
  mView = nullptr;
  mHWND = 0;
  mHDC = 0;
  mHGLRC = 0;
}
CGRenderContext::CGRenderContext(CGView* pView) {
  mView = pView;
  if (pView!=nullptr) {
    mHWND = pView->GetSafeHwnd();
   // mHDC = ::GetDC(mHWND);
    mHGLRC = 0;
  } else {
    mHWND = 0;
    mHDC = 0;
     mHGLRC = 0;
  }
}
CGRenderContext::~CGRenderContext() {}
void CGRenderContext::setView(CGView* pView) {
  mView = pView;
  if (mView) {
    mHWND = mView->GetSafeHwnd();
    mHDC = ::GetDC(mHWND);
  }
}
CGView* CGRenderContext::getView() const {
  return mView;
}

void CGRenderContext::DDALine(const Vec2i& start,
                              const Vec2i& end,
                              unsigned long color) {
  if (mView == nullptr)
    return;
  int steps;
  int dx = end.x() - start.x();
  int dy = end.y() - start.x();
  if (abs(dx) >= abs(dy))
    steps = abs(dx);
  else
    steps = abs(dy);
  float x = (float)start.x(), y = (float)start.y(), xincre = (float)dx / steps,
        yincre = (float)dy / steps;
  CClientDC dc(mView);
  dc.SetPixel((int)(x + 0.5), (int)(y + 0.5), color);
  for (int i = 1; i <= steps; i++) {
    dc.SetPixel((int)(x + 0.5), (int)(y + 0.5), color);
    x = x + xincre;
    y = y + yincre;
  }
}

void CGRenderContext::MidPointLine(const Vec2i& start,
                                   const Vec2i& end,
                                   unsigned long color) {
  if (mView == nullptr)
    return;
  int d, x, y, delta1, delta2;
  int a = start.y() - end.y();
  int b = end.x() - start.x();
  int cx = (b >= 0 ? 1 : (b = -b, -1));
  int cy = (a <= 0 ? 1 : (a = -1, -1));
  x = start.x();
  y = start.y();
  CClientDC dc(mView);
  dc.SetPixel(x, y, color);
  if (-a <= b) {
    d = 2 * a + b;
    delta1 = 2 * a;
    delta2 = 2 * (a + b);
    while (x != end.x()) {
      if (d < 0) {
        y += cy, d += delta2;
      } else {
        d += delta1;
      }
      x = x + cx;
      dc.SetPixel(x, y, color);
    }
  } else {
    d = 2 * b + a;
    delta1 = 2 * b;
    delta2 = 2 * (a + b);
    while (y != end.y()) {
      if (d < 0) {
        d += delta1;
      } else {
        x += cx, d += delta2;
      }
      y = y + cy;
      dc.SetPixel(x, y, color);
    }
  }
}

void CGRenderContext::BresehamLine(const Vec2i& start,
                                   const Vec2i& end,
                                   unsigned long color) {
  if (mView == nullptr)
    return;
  int x, y;
  x = start.x();
  y = start.y();
  CClientDC dc(mView);
  int dy = abs(end.y() - start.y());
  int dx = abs(end.x() - start.x());
  int s1 = end.x() > start.x() ? 1 : -1;
  int s2 = end.y() > start.y() ? 1 : -1;
  bool flag = false;
  if (dy > dx) {
    int t = dx;
    dx = dy;
    dy = t;
    flag = true;
  }
  int d0 = 2 * dy - dx;
  for (int i = 0; i < dx; i++) {
    dc.SetPixel(x, y, color);
    if (d0 >= 0) {
      if (!flag)
        y += s2;
      else
        x += s1;
      d0 -= 2 * dx;
    }
    if (!flag)
      x += s1;
    else
      y += s2;
    d0 += 2 * dy;
  }
}


//中点画圆算法
void CGRenderContext::MidPointCircle(const Vec2i& center, int radius,unsigned long color) {
  if (!mView)
    return;
  int p, addx, addy;
  p = 1 - radius;
  addx = 0;
  addy = radius;
  CClientDC dc(mView);
  dc.SetPixel(center.x() + addx, center.y() + addy, color);
  dc.SetPixel(center.x() - addx, center.y() + addy, color);
  dc.SetPixel(center.x() + addx, center.y() - addy, color);
  dc.SetPixel(center.x() - addx, center.y() - addy, color);
  dc.SetPixel(center.x() + addy, center.y() + addx, color);
  dc.SetPixel(center.x() - addy, center.y() + addx, color);
  dc.SetPixel(center.x() + addy, center.y() - addx, color);
  dc.SetPixel(center.x() - addy, center.y() - addx, color);

  while (addx <= addy) {
    addx++;
    if (p < 0) {
      p += 2 * addx + 3;
    } else {
      addy--;
      p += 2 * (addx - addy) + 5;
    }
    dc.SetPixel(center.x() + addx, center.y() + addy, color);
    dc.SetPixel(center.x() - addx, center.y() + addy, color);
    dc.SetPixel(center.x() + addx, center.y() - addy, color);
    dc.SetPixel(center.x() - addx, center.y() - addy, color);
    dc.SetPixel(center.x() + addy, center.y() + addx, color);
    dc.SetPixel(center.x() - addy, center.y() + addx, color);
    dc.SetPixel(center.x() + addy, center.y() - addx, color);
    dc.SetPixel(center.x() - addy, center.y() - addx, color);
  }
}
void CGRenderContext::BresehamCircle(const Vec2i& center,int radius,unsigned long color) {
  if (!mView)
    return;
  int x, y, d;
  x = 0;
  y = radius;
  d = 2 - 2 * radius;
  CClientDC dc(mView);
  dc.SetPixel(center.x() + x, center.y() + y, color);
  dc.SetPixel(center.x() - x, center.y() + y, color);
  dc.SetPixel(center.x() + x, center.y() - y, color);
  dc.SetPixel(center.x() - x, center.y() - y, color);
  dc.SetPixel(center.x() + y, center.y() + x, color);
  dc.SetPixel(center.x() - y, center.y() + x, color);
  dc.SetPixel(center.x() + y, center.y() - x, color);
  dc.SetPixel(center.x() - y, center.y() - x, color);
  while (x <= y) {
    CClientDC dc(mView);
    dc.SetPixel(center.x() + x, center.y() + y, color);
    dc.SetPixel(center.x() - x, center.y() + y, color);
    dc.SetPixel(center.x() + x, center.y() - y, color);
    dc.SetPixel(center.x() - x, center.y() - y, color);
    dc.SetPixel(center.x() + y, center.y() + x, color);
    dc.SetPixel(center.x() - y, center.y() + x, color);
    dc.SetPixel(center.x() + y, center.y() - x, color);
    dc.SetPixel(center.x() - y, center.y() - x, color);
    if (d < 0) {
      if (2 * (d + y) - 1 <= 0) {
        d = d + 2 * x + 3;
        x++;
      } else {
        d = d + 2 * (x - y + 3);
        x++;
        y--;
      }
    } else if (d == 0) {
      d = d + 2 * (x - y + 3);
      x++;
      y--;
    } else {
      if (2 * (d - x) - 1 <= 0) {
        d = d + 2 * (x - y + 3);
        x++;
        y--;
      } else {
        d = d - 2 * y + 3;
        y--;
      }
    }
  }
}
int dx[] = {0, 0, -1, 1, 1, 1, -1, -1};
int dy[] = {-1, 1, 0, 0, 1, -1, 1, -1};
void CGRenderContext::BoundaryFill4(int x,
                                    int y,
                                    unsigned int fill,
                                    int boundary) {
  if (!mView)
    return;
  ::SetPixel(mHDC, x, y, fill);
  for (int i = 0; i < 4; ++i) {
    int tmpx = x + dx[i];
    int tmpy = y + dy[i];
    int color = ::GetPixel(mHDC, tmpx, tmpy);
    if (color != boundary && (color != fill)) {
      if (x >= 0 && x <= xmax && y >= 0 && y <= ymax)
        BoundaryFill4(tmpx, tmpy, fill, boundary);
    }
  }
}

void CGRenderContext::FloodFill4(int x,
                                 int y,
                                 unsigned int fillColor,
                                 unsigned int oldColor) {
  if (!mView)
    return;
  ::SetPixel(mHDC, x, y, fillColor);
  for (int i = 0; i < 4; ++i) {
    int tmpx = x + dx[i];
    int tmpy = y + dy[i];
    int current;
    current = ::GetPixel(mHDC, tmpx, tmpy);
    if (current == oldColor) {
      if (x >= 0 && x <= xmax && y >= 0 && y <= ymax)
        FloodFill4(tmpx, tmpy, fillColor, oldColor);
    }
  }
}

void CGRenderContext::BoundaryFill8(int x,
                                    int y,
                                    unsigned int fill,
                                    int boundary) {
  if (!mView)
    return;
  ::SetPixel(mHDC, x, y, fill);
  for (int i = 0; i < 8; ++i) {
    int tmpx = x + dx[i];
    int tmpy = y + dy[i];
    int color = ::GetPixel(mHDC, tmpx, tmpy);
    if (color != boundary && (color != fill)) {
      if (x >= 0 && x <= xmax && y >= 0 && y <= ymax)
        BoundaryFill8(tmpx, tmpy, fill, boundary);
    }
  }
}

void CGRenderContext::FloodFill8(int x,
                                 int y,
                                 unsigned int fillColor,
                                 unsigned int oldColor) {
  if (!mView)
    return;
  ::SetPixel(mHDC, x, y, fillColor);
  for (int i = 0; i < 8; ++i) {
    int tmpx = x + dx[i];
    int tmpy = y + dy[i];
    int current;
    current = ::GetPixel(mHDC, tmpx, tmpy);
    if (current == oldColor) {
      if (x >= 0 && x <= xmax && y >= 0 && y <= ymax)
        FloodFill8(tmpx, tmpy, fillColor, oldColor);
    }
  }
}

#include <queue>
Vec2i d[] = {Vec2i(0, 1), Vec2i(0, -1),  Vec2i(1, 0),  Vec2i(-1, 0),
             Vec2i(1, 1), Vec2i(-1, -1), Vec2i(1, -1), Vec2i(-1, 1)};
void CGRenderContext::SeedFill_Boundary(const Vec2i seed,
                                        unsigned long fill,
                                        unsigned long boundary,
                                        int dir) {
  CClientDC dc(mView);
  RECT rect;
  GetClientRect(*mView, &rect);
  int ymax = abs(rect.bottom - rect.top);
  int xmax = abs(rect.right - rect.left);
  std::queue<Vec2i> q;
  q.push(seed);
  Vec2i e;
  while (!q.empty()) {
    e = q.front();
    q.pop();
    if (e.x() < 0 || e.x() > xmax || e.y() < 0 || e.y() > ymax)
      continue;
    unsigned long thiscolor = GetPixel(dc, e.x(), e.y());
    if (thiscolor == boundary || thiscolor == fill)
      continue;
    SetPixel(dc, e.x(), e.y(), fill);
    for (int i = 0; i < dir; i++)
      q.push(Vec2i(e.x() + d[i].x(), e.y() + d[i].y()));
  }
}
void CGRenderContext::SeedFill_Point(const Vec2i seed,
                                     unsigned long fill,
                                     int dir) {
  CClientDC dc(mView);
  RECT rect;
  GetClientRect(*mView, &rect);
  unsigned long boundary = GetPixel(dc, seed.x(), seed.y());
  if (fill == boundary)
    return;
  int ymax = abs(rect.bottom - rect.top);
  int xmax = abs(rect.right - rect.left);
  std::queue<Vec2i> q;
  q.push(seed);
  Vec2i e;
  while (!q.empty()) {
    e = q.front();
    q.pop();
    if (e.x() < 0 || e.x() > xmax || e.y() < 0 || e.y() > ymax)
      continue;
    if (GetPixel(dc, e.x(), e.y()) != boundary)
      continue;
    SetPixel(dc, e.x(), e.y(), fill);
    for (int i = 0; i < dir; i++) {
      q.push(Vec2i(e.x() + d[i].x(), e.y() + d[i].y()));
    }
  }
}

//直线段裁剪算法编码部分
int EnCode(double x, double y,double xl, double yb,double xr,double yt) {
  int code = 0;
  if (x < xl) {
    code = code | 1;
  }
  if (x > xr) {
    code = code | 2;
  }
  if (y < yb) {
    code = code | 4;
  }
  if (y > yt) {
    code = code | 8;
  }
  return code;
}
//直线段裁剪算法xl,yb,xr,yt对应裁剪窗口的左、下、右、上。s、e输入线段起点终点，rs、re裁剪结果，无则返回false，有则返回true
bool CGRenderContext::CohenSutherlandLineClip(double xl, double yb,double xr,double yt,
                                              const Vec2d& s, const Vec2d& e,Vec2d& rs, Vec2d& re) {
  if (s.x() > xl && s.x() < xr && e.x() > xl && e.x() < xr && s.y() > yb &&
      s.y() < yt && e.y() > yb && e.y() < yt) {
    rs = s;
    re = e;
    return true;
  }
  int code1, code2, code;
  double x = 0, y = 0;
  rs = s, re = e;
  //获取线段两个端点的编码情况
  code1 = EnCode(s.x(), s.y(), xl, yb, xr, yt);
  code2 = EnCode(e.x(), e.y(), xl, yb, xr, yt);
  while (code1 != 0 || code2 != 0)  //直到线段的端点都在窗口内退出循环
  {
    if ((code1 & code2) != 0)  //线段不在窗口内
      return false;
    code = code1;
    if (code1 == 0)  //线段的起点在窗口内
      code = code2;
    if ((1 & code) != 0)  //交点在左边
    {
      x = xl;
      y = rs.y() + (re.y() - rs.y()) * (xl - rs.x()) / (re.x() - rs.x());
    } else if ((2 & code) != 0)  //交点在右边
    {
      x = xr;
      y = rs.y() + (re.y() - rs.y()) * (xr - rs.x()) / (re.x() - rs.x());
    } else if ((4 & code) != 0)  //交点在下边
    {
      y = yb;
      x = rs.x() + (re.x() - rs.x()) * (yb - rs.y()) / (re.y() - rs.y());
    } else if ((8 & code) != 0)  //交点在上边
    {
      y = yt;
      x = rs.x() + (re.x() - rs.x()) * (yt - rs.y()) / (re.y() - rs.y());
    }
    if (code == code1) {
      rs.x() = x;
      rs.y() = y;
      code1 = EnCode(x, y, xl, yb, xr, yt);
    } else {
      re.x() = x;
      re.y() = y;
      code2 = EnCode(x, y, xl, yb, xr, yt);
    }
  }
  return true;
}
///三维图形
bool CGRenderContext::InitRenderContext() {
  return false;
}
void CGRenderContext::SetupRenderContext() {}
void CGRenderContext::Ready() {}
void CGRenderContext::Finish() {}