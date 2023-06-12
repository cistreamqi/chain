// LoginUI.cpp: 实现文件
//

#include "pch.h"
#include "MFCClient.h"
#include "LoginUI.h"
#include "afxdialogex.h"


// LoginUI 对话框

IMPLEMENT_DYNAMIC(LoginUI, CDialogEx)

LoginUI::LoginUI(CWnd* pParent /*=nullptr*/)
	: CDialogEx(LOGIN, pParent)
{
	Cli_hIcon = AfxGetApp()->LoadIcon(IDI_tubiao);
}

BOOL LoginUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(Cli_hIcon, TRUE);			// 设置大图标
	SetIcon(Cli_hIcon, FALSE);		// 设置小图标
	return TRUE;
}
LoginUI::~LoginUI()
{
}

void LoginUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, UserTxt, TUser);
	DDX_Control(pDX, PassWordTxt, TPassWord);
	DDX_Control(pDX, UserName, C_User);
	DDX_Control(pDX, PassWord, C_PassWord);
	DDX_Control(pDX, LOGBTN, LogBtn);
	DDX_Control(pDX, CANCEL, Cancel);
}


BEGIN_MESSAGE_MAP(LoginUI, CDialogEx)
	ON_BN_CLICKED(LOGBTN, &LoginUI::OnBnClickedLogbtn)
	ON_BN_CLICKED(CANCEL, &LoginUI::OnBnClickedCancel)
END_MESSAGE_MAP()


// LoginUI 消息处理程序


void LoginUI::OnBnClickedLogbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
	CString User_Name;
	C_User.GetWindowTextW(User_Name);
	CString Pass_Word;
	C_PassWord.GetWindowTextW(Pass_Word);

	if (User_Name.IsEmpty()|| Pass_Word.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空，请重新输入！"), _T("用户登录信息"), MB_ICONINFORMATION);
		return;
	}
	else if (1)//验证通过
	{
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("用户名或密码不正确，请重新输入！"), _T("登录失败"), MB_ICONERROR);
		return;
	}
}
//登录

void LoginUI::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}
