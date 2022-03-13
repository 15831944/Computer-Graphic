// COGLCreateSpotDlg.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLCreateSpotDlg.h"
#include "afxdialogex.h"


// COGLCreateSpotDlg 对话框

IMPLEMENT_DYNAMIC(COGLCreateSpotDlg, CDialogEx)

COGLCreateSpotDlg::COGLCreateSpotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SPOTDATA, pParent)
{

}

COGLCreateSpotDlg::~COGLCreateSpotDlg()
{
}

void COGLCreateSpotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COGLCreateSpotDlg, CDialogEx)
ON_WM_CLOSE()
ON_WM_PAINT()
ON_BN_CLICKED(IDOK, &COGLCreateSpotDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLCreateSpotDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// COGLCreateSpotDlg 消息处理程序

void COGLCreateSpotDlg::OnClose() {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CDialogEx::OnClose();
}

void COGLCreateSpotDlg::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
}

void COGLCreateSpotDlg::OnBnClickedOk() {
  // TODO: 在此添加控件通知处理程序代码
  CDialogEx::OnOK();
}

void COGLCreateSpotDlg::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  CDialogEx::OnCancel();
}

void COGLCreateSpotDlg::getData() {
  CString str;
  GetDlgItemText(IDC_EDIT_SPOTDIREC1, str);
  ::_stscanf_s(str, _T("%lf"), &direction1);
  GetDlgItemText(IDC_EDIT_SPOTDIREC2, str);
  ::_stscanf_s(str, _T("%lf"), &direction2);
  GetDlgItemText(IDC_EDIT_SPOTDIREC3, str);
  ::_stscanf_s(str, _T("%lf"), &direction3);
  if (direction1 > 1.0 || direction1 < 0.0 || direction2 > 1.0 ||
      direction2 < 0.0 || direction3 > 1.0 || direction3 < 0.0) {
    AfxMessageBox(_T("数据错误"));
    f = false;
  }
  GetDlgItemText(IDC_EDIT_SPOTANGLE, str);
  ::_stscanf_s(str, _T("%lf"), &angle);
  GetDlgItemText(IDC_EDIT_SPOTEXPONENT, str);
  ::_stscanf_s(str, _T("%lf"), &exponent);
  f = true;
}