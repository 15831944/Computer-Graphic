// COGLCreateLightDlg.cpp: 实现文件
//

#include "pch.h"
#include "CG2019112380熊宇新.h"
#include "COGLCreateLightDlg.h"
#include "afxdialogex.h"


// COGLCreateLightDlg 对话框

IMPLEMENT_DYNAMIC(COGLCreateLightDlg, CDialogEx)

COGLCreateLightDlg::COGLCreateLightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SET_LIGHTSOURCE, pParent)
{

}

COGLCreateLightDlg::~COGLCreateLightDlg()
{
}

void COGLCreateLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COGLCreateLightDlg, CDialogEx)
ON_BN_CLICKED(IDOK, &COGLCreateLightDlg::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &COGLCreateLightDlg::OnBnClickedCancel)
ON_WM_PAINT()
ON_WM_CLOSE()
END_MESSAGE_MAP()


// COGLCreateLightDlg 消息处理程序

void COGLCreateLightDlg::OnBnClickedOk() {
  // TODO: 在此添加控件通知处理程序代码
  getData();
  CDialogEx::OnOK();
  f = true;
}

void COGLCreateLightDlg::OnBnClickedCancel() {
  // TODO: 在此添加控件通知处理程序代码
  f = false;
  CDialogEx::OnCancel();
}

void COGLCreateLightDlg::OnPaint() {
  CPaintDC dc(this);  // device context for painting
                      // TODO: 在此处添加消息处理程序代码
                      // 不为绘图消息调用 CDialogEx::OnPaint()
  SetDlgItemInt(IDC_EDIT_AMBIENT1, 1.0);
  SetDlgItemInt(IDC_EDIT_AMBIENT2, 1.0);
  SetDlgItemInt(IDC_EDIT_AMBIENT3, 1.0);
  SetDlgItemInt(IDC_EDIT_DIFFUSE1, 1.0);
  SetDlgItemInt(IDC_EDIT_DIFFUSE2, 1.0);
  SetDlgItemInt(IDC_EDIT_DIFFUSE3, 1.0);
  SetDlgItemInt(IDC_EDIT_SPECULAR1, 1.0);
  SetDlgItemInt(IDC_EDIT_SPECULAR2, 1.0);
  SetDlgItemInt(IDC_EDIT_SPECULAR3, 1.0);
  SetDlgItemInt(IDC_EDIT_POSITION1, 0.0);
  SetDlgItemInt(IDC_EDIT_POSITION2, 0.0);
  SetDlgItemInt(IDC_EDIT_POSITION3, -1000.0);
}
void COGLCreateLightDlg::getData() {
  CString str;
  GetDlgItemText(IDC_EDIT_AMBIENT1, str);
  ::_stscanf_s(str, _T("%lf"), &ambient1);
  GetDlgItemText(IDC_EDIT_AMBIENT2, str);
  ::_stscanf_s(str, _T("%lf"), &ambient2);
  GetDlgItemText(IDC_EDIT_AMBIENT3, str);
  ::_stscanf_s(str, _T("%lf"), &ambient3);
  if (ambient1 > 1.0 || ambient1 < 0.0 || ambient2 > 1.0 || ambient2 < 0.0 ||
      ambient3 > 1.0 || ambient3 < 0.0) {
    AfxMessageBox(_T("数据错误"));
    f = false;
  }
  GetDlgItemText(IDC_EDIT_DIFFUSE1, str);
  ::_stscanf_s(str, _T("%lf"), &diffuse1);
  GetDlgItemText(IDC_EDIT_DIFFUSE2, str);
  ::_stscanf_s(str, _T("%lf"), &diffuse2);
  GetDlgItemText(IDC_EDIT_DIFFUSE3, str);
  ::_stscanf_s(str, _T("%lf"), &diffuse3);
  if (diffuse1 > 1.0 || diffuse1 < 0.0 || diffuse2 > 1.0 || diffuse2 < 0.0 ||
      diffuse3 > 1.0 || diffuse3 < 0.0) {
    AfxMessageBox(_T("数据错误"));
    f = false;
  }
  GetDlgItemText(IDC_EDIT_SPECULAR1, str);
  ::_stscanf_s(str, _T("%lf"), &specular1);
  GetDlgItemText(IDC_EDIT_SPECULAR2, str);
  ::_stscanf_s(str, _T("%lf"), &specular2);
  GetDlgItemText(IDC_EDIT_SPECULAR3, str);
  ::_stscanf_s(str, _T("%lf"), &specular3);
  if (specular1 > 1.0 || specular1 < 0.0 || specular2 > 1.0 || specular2 < 0.0 ||
      specular3 > 1.0 || specular3 < 0.0) {
    AfxMessageBox(_T("数据错误"));
    f = false;
  }
  GetDlgItemText(IDC_EDIT_POSITION1, str);
  ::_stscanf_s(str, _T("%lf"), &pos1);
  GetDlgItemText(IDC_EDIT_POSITION2, str);
  ::_stscanf_s(str, _T("%lf"), &pos2);
  GetDlgItemText(IDC_EDIT_POSITION3, str);
  ::_stscanf_s(str, _T("%lf"), &pos3);
}

void COGLCreateLightDlg::OnClose() {
  // TODO: 在此添加消息处理程序代码和/或调用默认值

  CDialogEx::OnClose();
}
