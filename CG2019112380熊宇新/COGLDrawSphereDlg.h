#pragma once

// COGLDrawSphereDlg 对话框

class COGLDrawSphereDlg : public CDialogEx {
  DECLARE_DYNAMIC(COGLDrawSphereDlg)

 public:
  COGLDrawSphereDlg(CWnd* pParent = nullptr);  // 标准构造函数
  virtual ~COGLDrawSphereDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_3DSPHERE };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持

  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
 public:
  void getData();
  double x, y, z,r;
  int slice, stacks;
  bool f = false;
  afx_msg void OnPaint();
};
