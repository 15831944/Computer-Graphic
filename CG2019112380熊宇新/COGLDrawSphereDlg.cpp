// COGLDrawSphereDlg.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLDrawSphereDlg.h"
#include "afxdialogex.h"


// COGLDrawSphereDlg 对话框

IMPLEMENT_DYNAMIC(COGLDrawSphereDlg, CDialogEx)

COGLDrawSphereDlg::COGLDrawSphereDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_3DSPHERE, pParent)
{

}

COGLDrawSphereDlg::~COGLDrawSphereDlg()
{
}

void COGLDrawSphereDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}													 


BEGIN_MESSAGE_MAP(COGLDrawSphereDlg, CDialogEx)
ON_BN_CLICKED(IDOK, &COGLDrawSphereDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLDrawSphereDlg::OnBnClickedCancel)
ON_WM_PAINT()
END_MESSAGE_MAP()


// COGLDrawSphereDlg 消息处理程序

void COGLDrawSphereDlg::OnBnClickedOk() {
  // TODO: 在此添加控件通知处理程序代码
  getData();
  CDialogEx::OnOK();
}

void COGLDrawSphereDlg::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  CDialogEx::OnCancel();
}

void COGLDrawSphereDlg::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
  SetDlgItemInt(IDC_EDIT_SPHEREX, 0.0);
  SetDlgItemInt(IDC_EDIT_SPHEREY, 0.0);
  SetDlgItemInt(IDC_EDIT_SPHEREZ, 0.0);
  SetDlgItemInt(IDC_EDIT_SPHERE_RADIUS, 100);
  SetDlgItemInt(IDC_EDIT_SLICE, 30);
  SetDlgItemInt(IDC_EDIT_STACKS, 30);
}

void COGLDrawSphereDlg::getData() {
  CString str1, str2, str3,str4;
  GetDlgItemText(IDC_EDIT_SPHEREX, str1);
  ::_stscanf_s(str1, _T("%lf"), &x);
  GetDlgItemText(IDC_EDIT_SPHEREY, str2);
  ::_stscanf_s(str2, _T("%lf"), &y);
  GetDlgItemText(IDC_EDIT_SPHEREZ, str3);
  ::_stscanf_s(str3, _T("%lf"), &z);
  GetDlgItemText(IDC_EDIT_SPHERE_RADIUS, str4);
  ::_stscanf_s(str4, _T("%lf"), &r);

  slice=GetDlgItemInt(IDC_EDIT_SLICE);
  stacks= GetDlgItemInt(IDC_EDIT_STACKS);
  f = true;
}