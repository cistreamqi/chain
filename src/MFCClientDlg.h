
// MFCClientDlg.h: 头文件
//

#pragma once


// CMFCClientDlg 对话框
class CMFCClientDlg : public CDialogEx
{
// 构造
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//调整布局
	CString SerStatus;
	CList<CRect, CRect&>m_listRect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEdit FPath;
	CButton ChoFile;
	CButton ConServer;
	CEdit SerEdit;
	CButton SendBtn;
	CEdit InEdit;
	CStatic IPText;
	CEdit IpEdit;
	CStatic TxtPath;
	CButton SendF;
	CButton DetectData;
	CButton CheckSaveF;
	afx_msg void OnBnClickedChoosefile();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSendfile();
	afx_msg void OnBnClickedDetection();


private:
	int k = 0;
	const int PORT = 8000;
#define MaxBufSize 1024
#define _CRT_SECURE_NO_WARINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
	//存放私钥
	unsigned char dk[32] = { 0xef, 0x00, 0x00, 0x1d, 0xda, 0x00, 0x00, 0x0e, 0x60, 0x00, 0x00, 0x0e, 0xb4, 0x00, 0x00, 0x17, 0xca, 0xc5, 0xe8, 0xc5, 0xea, 0x65, 0xb2, 0x85, 0xdb, 0xfc, 0xb3, 0x86, 0x71, 0x81, 0x2e, 0xf3 };
	//存放公钥
	unsigned char x[32];
	unsigned char y[32];
	//用户标识符
	unsigned char IDA2[32] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33,
	0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33,
	0x34, 0x35, 0x36, 0x37, 0x38 };
	//存放签名
	unsigned char r[32];
	unsigned char s[32];
	//存放用户自由因子
	unsigned char fr[256];
	//结束条件
	char key[257];

	WSADATA wsd;
	SOCKET SocketClient;
	SOCKADDR_IN  ClientAddr;
	char info[257], SendBuff[257], RecvBuff[257];
	char ida[33];
	char yesno;


public:
	afx_msg void OnBnClickedChecksf();
};
