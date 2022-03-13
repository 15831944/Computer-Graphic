// COGLDrawPointDlg.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLDrawPointDlg.h"
#include "afxdialogex.h"


// COGLDrawPointDlg 对话框

IMPLEMENT_DYNAMIC(COGLDrawPointDlg, CDialogEx)

COGLDrawPointDlg::COGLDrawPointDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_3DDOT, pParent)
{

}

COGLDrawPointDlg::~COGLDrawPointDlg()
{
}

void COGLDrawPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COGLDrawPointDlg, CDialogEx)
ON_BN_CLICKED(ID_DOT_OK, &COGLDrawPointDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLDrawPointDlg::OnBnClickedCancel)
ON_WM_PAINT()
END_MESSAGE_MAP()


// COGLDrawPointDlg 消息处理程序

void COGLDrawPointDlg::OnBnClickedOk() {
  // TODO: 在此添加控件通知处理程序代码
  getXYZ();
  CDialogEx::OnOK();
}

void COGLDrawPointDlg::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  f = false;
  CDialogEx::OnCancel();
}

void COGLDrawPointDlg::getXYZ() {
  CString str1, str2, str3;
  GetDlgItemText(IDC_EDIT_X, str1);
  ::_stscanf_s(str1, _T("%lf"), &x);
  GetDlgItemText(IDC_EDIT_Y, str2);
  ::_stscanf_s(str2, _T("%lf"), &y);
  GetDlgItemText(IDC_EDIT_Z, str3);
  ::_stscanf_s(str3, _T("%lf"), &z);
  f = true;
}

void COGLDrawPointDlg::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
  SetDlgItemInt(IDC_EDIT_X, 0.0);
  SetDlgItemInt(IDC_EDIT_Y, 0.0);
  SetDlgItemInt(IDC_EDIT_Z, 0.0);
}
