#pragma once


// LoginUI 对话框

class LoginUI : public CDialogEx
{
	DECLARE_DYNAMIC(LoginUI)

public:
	LoginUI(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LoginUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = LOGIN };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON Cli_hIcon;
	CStatic TUser;
	CStatic TPassWord;
	CEdit C_User;
	CEdit C_PassWord;
	CButton LogBtn;
	CButton Cancel;
	afx_msg void OnBnClickedLogbtn();
	afx_msg void OnBnClickedCancel();
};
