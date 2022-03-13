#pragma once

// COGLDrawPointDlg 对话框

class COGLDrawPointDlg : public CDialogEx {
  DECLARE_DYNAMIC(COGLDrawPointDlg)

 public:
  COGLDrawPointDlg(CWnd* pParent = nullptr);  // 标准构造函数
  virtual ~COGLDrawPointDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_3DDOT };
#endif												  

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持

  DECLARE_MESSAGE_MAP()
 public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  void getXYZ();
  double x, y, z;
  bool f = false;
  afx_msg void OnPaint();
};
