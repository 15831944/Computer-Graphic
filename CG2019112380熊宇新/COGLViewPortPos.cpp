// COGLViewPortPos.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLViewPortPos.h"
#include "afxdialogex.h"


// COGLViewPortPos 对话框

IMPLEMENT_DYNAMIC(COGLViewPortPos, CDialogEx)

COGLViewPortPos::COGLViewPortPos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETVIEWPORT, pParent)
{

}

COGLViewPortPos::~COGLViewPortPos()
{
}

void COGLViewPortPos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COGLViewPortPos, CDialogEx)
ON_BN_CLICKED(IDOK, &COGLViewPortPos::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLViewPortPos::OnBnClickedCancel)
ON_WM_PAINT()
END_MESSAGE_MAP()


// COGLViewPortPos 消息处理程序

void COGLViewPortPos::OnBnClickedOk() {
  getXYZ();
  // TODO: 在此添加控件通知处理程序代码
  CDialogEx::OnOK();
}

void COGLViewPortPos::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  f = false;
  CDialogEx::OnCancel();
}
void COGLViewPortPos::getXYZ() {
  CString str1, str2, str3;
  GetDlgItemText(IDC_EDIT_VIEWPORT_X, str1);
  ::_stscanf_s(str1, _T("%lf"), &x);
  GetDlgItemText(IDC_EDIT_VIEWPORT_Y, str2);
  ::_stscanf_s(str2, _T("%lf"), &y);
  GetDlgItemText(IDC_EDIT_VIEWPORT_Z, str3);
  ::_stscanf_s(str3, _T("%lf"), &z);
  f = true;
}
void COGLViewPortPos::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
  SetDlgItemInt(IDC_EDIT_VIEWPORT_X, 300.0);
  SetDlgItemInt(IDC_EDIT_VIEWPORT_Y, 300.0);
  SetDlgItemInt(IDC_EDIT_VIEWPORT_Z, 1000.0);
}
