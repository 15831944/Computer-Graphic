// COGLDrawLinesegDlg.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLDrawLinesegDlg.h"
#include "afxdialogex.h"


// COGLDrawLinesegDlg 对话框

IMPLEMENT_DYNAMIC(COGLDrawLinesegDlg, CDialogEx)

COGLDrawLinesegDlg::COGLDrawLinesegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_3DLINESEGMENT, pParent)
{

}

COGLDrawLinesegDlg::~COGLDrawLinesegDlg()
{
}

void COGLDrawLinesegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COGLDrawLinesegDlg, CDialogEx)
ON_BN_CLICKED(IDOK, &COGLDrawLinesegDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLDrawLinesegDlg::OnBnClickedCancel)
ON_WM_PAINT()
END_MESSAGE_MAP()


// COGLDrawLinesegDlg 消息处理程序

void COGLDrawLinesegDlg::OnBnClickedOk() {
  // TODO: 在此添加控件通知处理程序代码
  getV1V2();
  CDialogEx::OnOK();
}

void COGLDrawLinesegDlg::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  CDialogEx::OnCancel();
}

void COGLDrawLinesegDlg::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
  SetDlgItemInt(IDC_EDIT_X1, 0.0);
  SetDlgItemInt(IDC_EDIT_Y1, 0.0);
  SetDlgItemInt(IDC_EDIT_Z1, 0.0);
  SetDlgItemInt(IDC_EDIT_X2, 100.0);
  SetDlgItemInt(IDC_EDIT_Y2, 100.0);
  SetDlgItemInt(IDC_EDIT_Z2, 100.0);
}

void COGLDrawLinesegDlg::getV1V2() {
  CString str1, str2, str3;
  GetDlgItemText(IDC_EDIT_X1, str1);
  ::_stscanf_s(str1, _T("%lf"), &x1);
  GetDlgItemText(IDC_EDIT_Y1, str2);
  ::_stscanf_s(str2, _T("%lf"), &y1);
  GetDlgItemText(IDC_EDIT_Z1, str3);
  ::_stscanf_s(str3, _T("%lf"), &z1);

  CString str4, str5, str6;
     GetDlgItemText(IDC_EDIT_X2, str4);
  ::_stscanf_s(str4, _T("%lf"), &x2);
  GetDlgItemText(IDC_EDIT_Y2, str5);
  ::_stscanf_s(str5, _T("%lf"), &y2);
  GetDlgItemText(IDC_EDIT_Z2, str6);
  ::_stscanf_s(str6, _T("%lf"), &z2);
  f = true;
}
