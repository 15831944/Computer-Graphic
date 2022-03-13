#include "pch.h"
#include "Create2DLine.h"
#include "CG2DLine.h"
#include "CGDI2DView.h"

Create2DLine::Create2DLine(CGView* pview /* = nullptr*/)
    : UIEventListener(pview), mStart(0, 0), mEnd(0, 0) {
  m_nStep = 0;
}
Create2DLine::~Create2DLine() {}
int Create2DLine::GetType()  //��������
{
  return cmd2dLine;
}
int Create2DLine::OnLButtonDown(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  m_nStep++;         //ÿ�ε���������ʱ�������������һ
  if (m_nStep == 1)  //��һ�ε�������������¼���
  {
    mStart = mEnd = mTemp = pos;
    mView->Prompt(_T("������ֱ�ߵ��յ�"));
  } else if (m_nStep == 2) {
    //���������Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(mTemp.x(), mTemp.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x����仯С����ֱ��
      {
        mTemp.x() = mStart.x();
        mEnd.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          mTemp.y() = rectDlg.Height();
          mEnd.y() = 0;
        } else {
          mTemp.y() = 0;
          mEnd.y() = rectDlg.Height();
        }
      } else  // x����仯��ˮƽ��
      {
        mTemp.y() = mStart.y();
        mEnd.y() = mStart.y();
        if (pos.x() <= mStart.x()) {
          mTemp.x() = rectDlg.Width();
          mEnd.x() = 0;
        } else {
          mTemp.x() = 0;
          mEnd.x() = rectDlg.Width();
        }
      }
    } else {
      if (mStart.x() == pos.x()) {
        mTemp.x() = mStart.x();
        mEnd.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          mTemp.y() = rectDlg.Height();
          mEnd.y() = 0;
        } else {
          mTemp.y() = 0;
          mEnd.y() = rectDlg.Height();
        }
      } else {
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
        if (pos.x() <= mStart.x()) {
          mEnd.x() = 0;
          mTemp.x() = rectDlg.Width();

        } else {
          mEnd.x() = rectDlg.Width();
          mTemp.x() = 0;
        }
        mTemp.y() = k * mTemp.x() - k * mStart.x() + mStart.y();
        mEnd.y() = k * mEnd.x() - k * mStart.x() + mStart.y();
      }
    }
    //��ȡ��㡢�յ��Ӧ�ĳ�������
    Vec2d start = mView->ViewPortToWorld(mTemp);
    Vec2d end = mView->ViewPortToWorld(mEnd);
    //�����߶β���ӵ�����
    CG2DLine* pLine = new CG2DLine(start, end);
    pLine->setPenColor(mView->PenColor());  //��̬
    pLine->setPenWidth(mView->PenWidth());
    pLine->setPenStyle(mView->PenStyle());
    mView->addRenderable(pLine);
    mView->Invalidate();
    mView->UpdateWindow();
    m_nStep = 0;  //��Ϊ0����д��ʼ�����߶�
    mView->Prompt(_T("������ֱ�ߵ����"));
  } else {
  }
  return 0;
}
int Create2DLine::OnMouseMove(UINT nFlags, const Pos2i& pos) {
  if (mView == nullptr)
    return -1;
  CRect rectDlg;
  mView->GetClientRect(rectDlg);
  if (m_nStep == 0) {
    mView->Prompt(_T("������ֱ�ߵ����"));
  } else if (m_nStep == 1) {
    Pos2i preEndPos, curEndPos, preTempPos, curTempPos;
    preTempPos = mTemp;
    preEndPos = mEnd;
    //�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
    if (nFlags & MK_SHIFT) {
      if (abs(pos.x() - mStart.x()) <=
          abs(pos.y() - mStart.y()))  // x����仯С����ֱ��
      {
        curTempPos.x() = mStart.x();
        curEndPos.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          curTempPos.y() = rectDlg.Height();
          curEndPos.y() = 0;
        } else {
          curTempPos.y() = 0;
          curEndPos.y() = rectDlg.Height();
        }
      } else  //ˮƽ��
      {
        curTempPos.y() = mStart.y();
        curEndPos.y() = mStart.y();
        if (pos.x() <= mStart.x()) {
          curTempPos.x() = rectDlg.Width();
          curEndPos.x() = 0;
        } else {
          curTempPos.x() = 0;
          curEndPos.x() = rectDlg.Width();
        }
      }
    } else {
      if (mStart.x() == pos.x()) {
        curTempPos.x() = mStart.x();
        curEndPos.x() = mStart.x();
        if (pos.y() <= mStart.y()) {
          curTempPos.y() = rectDlg.Height();
          curEndPos.y() = 0;
        } else {
          curTempPos.y() = 0;
          curEndPos.y() = rectDlg.Height();
        }
      } else {
        double k = ((double)pos.y() - (double)mStart.y()) /
                   ((double)pos.x() - (double)mStart.x());
        if (pos.x() <= mStart.x()) {
          curEndPos.x() = 0;
          curTempPos.x() = rectDlg.Width();

        } else {
          curEndPos.x() = rectDlg.Width();
          curTempPos.x() = 0;
        }
        curTempPos.y() = k * curTempPos.x() - k * mStart.x() + mStart.y();
        curEndPos.y() = k * curEndPos.x() - k * mStart.x() + mStart.y();
      }
    }
    //�����ϴε���Ƥ��
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(preTempPos.x(), preTempPos.y()));
    dc.LineTo(CPoint(preEndPos.x(), preEndPos.y()));
    //�����µ���Ƥ��
    dc.MoveTo(CPoint(curTempPos.x(), curTempPos.y()));
    dc.LineTo(CPoint(curEndPos.x(), curEndPos.y()));
    dc.SelectObject(pOldPen);
    mEnd = curEndPos;  //��¼����λ��
    mTemp = curTempPos;
  } else {
  }
  return 0;
}
int Create2DLine::Cancel() {
  if (mView == nullptr)
    return -1;
  if (m_nStep == 1)  //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
  {
    CClientDC dc(mView);
    CPen pen(mView->PenStyle(), mView->PenWidth(), mView->PenColor());
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.SetROP2(R2_NOTXORPEN);
    dc.MoveTo(CPoint(mTemp.x(), mTemp.y()));
    dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
    dc.SelectObject(pOldPen);
  }
  m_nStep = 0;
  mView->Prompt(_T("����"));
  return 0;
}