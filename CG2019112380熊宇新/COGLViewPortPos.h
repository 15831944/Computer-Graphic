#pragma once

// COGLViewPortPos 对话框

class COGLViewPortPos : public CDialogEx {
  DECLARE_DYNAMIC(COGLViewPortPos)

 public:
  COGLViewPortPos(CWnd* pParent = nullptr);  // 标准构造函数
  virtual ~COGLViewPortPos();

// 对话框数据
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_SETVIEWPORT };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持
  void getXYZ();

  DECLARE_MESSAGE_MAP()
 public:
  double x=0, y=0, z=1000;
  bool f=false;
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  afx_msg void OnPaint();

};
