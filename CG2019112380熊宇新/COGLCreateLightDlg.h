#pragma once

// COGLCreateLightDlg 对话框

class COGLCreateLightDlg : public CDialogEx {
  DECLARE_DYNAMIC(COGLCreateLightDlg)

 public:
  COGLCreateLightDlg(CWnd* pParent = nullptr);  // 标准构造函数
  virtual ~COGLCreateLightDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_SET_LIGHTSOURCE };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV 支持
  void getData();
  DECLARE_MESSAGE_MAP()
 public:
  double ambient1, ambient2, ambient3;
  double diffuse1, diffuse2, diffuse3;
  double specular1, specular2, specular3;
  double pos1, pos2, pos3;
  bool f = false;
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  afx_msg void OnPaint();
  afx_msg void OnClose();
};
