#pragma once


// COGLCreateSpotDlg 对话框

class COGLCreateSpotDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COGLCreateSpotDlg)

public:
	COGLCreateSpotDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COGLCreateSpotDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPOTDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
       public:
        afx_msg void OnClose();
        afx_msg void OnPaint();
        afx_msg void OnBnClickedOk();
        afx_msg void OnBnClickedCancel();
        double direction1,direction2,direction3;
        double angle,exponent;
        bool f = false;
        void getData();
};
