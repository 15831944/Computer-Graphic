#pragma once

// COGLDrawLinesegDlg 对话框

class COGLDrawLinesegDlg : public CDialogEx {
  DECLARE_DYNAMIC(COGLDrawLinesegDlg)

 public:
  COGLDrawLinesegDlg(CWnd* pParent = nullptr);  // 标准构造函数
  virtual ~COGLDrawLinesegDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_3DLINESEGMENT };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持

  DECLARE_MESSAGE_MAP()
 public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  afx_msg void OnPaint();

 public:
  void getV1V2();
  double x1, x2, y1, y2, z1, z2;
  bool f = false;
};
