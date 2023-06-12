
// MFCClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"
#include"CliFunction.h"
#include<iostream>
#include<string>
#include <tchar.h>
#include<WinSock2.h>
#include <Ws2tcpip.h>
#include<fstream>
#include"io.h"
#include"vector"
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClientDlg 对话框



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_tubiao);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, FilePath, FPath);
	DDX_Control(pDX, ChooseFile, ChoFile);
	DDX_Control(pDX, Connect, ConServer);
	DDX_Control(pDX, ServerEdit, SerEdit);
	DDX_Control(pDX, InputEdit, InEdit);
	DDX_Control(pDX, IP, IPText);
	DDX_Control(pDX, IPEdit, IpEdit);
	DDX_Control(pDX, TextPath, TxtPath);
	DDX_Control(pDX, SendFile, SendF);
	DDX_Control(pDX, Detection, DetectData);
	DDX_Control(pDX, CheckSF, CheckSaveF);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(ChooseFile, &CMFCClientDlg::OnBnClickedChoosefile)
	ON_BN_CLICKED(Connect, &CMFCClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(SendFile, &CMFCClientDlg::OnBnClickedSendfile)
	ON_BN_CLICKED(Detection, &CMFCClientDlg::OnBnClickedDetection)
END_MESSAGE_MAP()


// CMFCClientDlg 消息处理程序

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//获得初始的各个控件的数据

	CRect rect;
	GetWindowRect(&rect);
	m_listRect.AddTail(rect);//对话框的区域
	CWnd* pWnd = GetWindow(GW_CHILD);//获取子窗体
	while (pWnd)
	{
		pWnd->GetWindowRect(rect);//子窗体的区域
		m_listRect.AddTail(rect);
		pWnd = pWnd->GetNextWindow();
	}

	/*char abcd[10] = { '1','2','3' };
	CString abcde(abcd);
	SerStatus += abcde;
	SerEdit.SetWindowTextW(SerStatus);
	((CButton*)GetDlgItem(CheckSF))->SetCheck(1);
	int CSFstate = ((CButton*)GetDlgItem(CheckSF))->GetCheck();
	yesno = CSFstate + '0';
	CString abcde(yesno);
	SerStatus += abcde;
	SerEdit.SetWindowTextW(SerStatus);*/

	//初始化socket

	yesno = '0';


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		//添加代码对话框背景贴图
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);    //获取对话框长宽      
		CDC   dcBmp;             //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BGP);    //载入资源中图片
		BITMAP   m_bitmap;                         //图片变量               
		bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
												  //将位图选入临时内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//调用函数显示图片StretchBlt显示形状可变
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	Invalidate(FALSE);//擦除通知重新绘图
	if (m_listRect.GetCount() > 0)
	{
		CRect dlgNow;
		GetWindowRect(&dlgNow);
		POSITION pos = m_listRect.GetHeadPosition();//第一个保存的是对话框的Rect  

		CRect dlgSaved;
		dlgSaved = m_listRect.GetNext(pos);
		ScreenToClient(dlgNow);

		float x = dlgNow.Width() * 1.0 / dlgSaved.Width();
		float y = dlgNow.Height() * 1.0 / dlgSaved.Height();
		//获得变化的比例
		ClientToScreen(dlgNow);

		CRect childSaved;
		CWnd* pWnd = GetWindow(GW_CHILD);
		while (pWnd)
		{
			childSaved = m_listRect.GetNext(pos);
			childSaved.left = dlgNow.left + (childSaved.left - dlgSaved.left)*x;
			childSaved.right = dlgNow.right + (childSaved.right - dlgSaved.right) * x;
			childSaved.top = dlgNow.top + (childSaved.top - dlgSaved.top) * y;
			childSaved.bottom = dlgNow.bottom + (childSaved.bottom - dlgSaved.bottom) * y;
			//各个方向的等比例调整

			ScreenToClient(childSaved);
			pWnd->MoveWindow(childSaved);
			pWnd = pWnd->GetNextWindow();
		}
		
	}
}
//实现布局，通过窗口的比例变化等比例调整各个窗口，也即各个控件


void CMFCClientDlg::OnBnClickedChoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPCITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (!pidl)
		return;
	TCHAR szDisplayName[255];
	SHGetPathFromIDList(pidl, szDisplayName);
	CString str(szDisplayName);
	/*CFileDialog dlg(true, _T("*.*"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, _T("All Files (*.*) |*.*||"), NULL);
	dlg.m_ofn.lpstrTitle = _T("打开文件");
	if (dlg.DoModal() != IDOK) return;//模态对话框
	CString PathF = dlg.GetPathName();
	FPath.SetWindowTextW(PathF);*/
	FPath.SetWindowTextW(str);
}
//这里执行选择文件的操作并显示文件路径


void CMFCClientDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ConStatus;
	ConServer.GetWindowTextW(ConStatus);
	if ("连接至服务器"== ConStatus)//如果未连接则进行连接
	{
		WSAStartup(MAKEWORD(2, 2), &wsd);
		SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		CString SerIp;
		IpEdit.GetWindowTextW(SerIp);
		std::string Ip= CT2A(SerIp.GetString());
		char* ip = (char*)Ip.data();
		if (1)//是个合适的ip
		{
			//添加连接
			ClientAddr.sin_family = AF_INET;
			inet_pton(AF_INET, ip, &ClientAddr.sin_addr.S_un.S_addr);
			ClientAddr.sin_port = htons(PORT);
			k = connect(SocketClient, (struct sockaddr*)&ClientAddr, sizeof(ClientAddr));

			if (k == SOCKET_ERROR)//连接失败
			{
				SerStatus += "连接失败\r\n";
				SerEdit.SetWindowTextW(SerStatus);
				
			}
			else//连接成功，，并将按钮文本改为“连接中。。。”
			{
				SerStatus = SerStatus + "连接成功\r\n已经连接至ip：" + SerIp;
				SerStatus += "\r\n";
				SerEdit.SetWindowTextW(SerStatus);
				ConServer.SetWindowTextW((CString)"连接中（点击中断）");



				//cout << "发送用户标识符 :";
				SerStatus += "发送用户标识符 :";
				SerEdit.SetWindowTextW(SerStatus);
				for (int i = 0; i < 32; i++)
				{
					ida[i] = IDA2[i];
				}
				ida[32] = '\0';
				//for (int i = 0; i < 32; i++) 
				//{ 
					//cout << ida[i]; 
				//}
				CString strida(ida);
				SerStatus += strida;
				SerEdit.SetWindowTextW(SerStatus);
				k = send(SocketClient, ida, sizeof(ida), 0);
				//cout << endl;
				SerStatus += "\r\n";
				SerEdit.SetWindowTextW(SerStatus);
				k = recv(SocketClient, RecvBuff, sizeof(RecvBuff), 0);
				RecvBuff[256] = '\0';
				if (k > 0) {
					//cout << "接收到来自服务器的需要签名的数据为 ：  " << endl;
					SerStatus += "接收到来自服务器的需要签名的数据为 ：  \r\n";
					CString strRecvBuff(RecvBuff);
					SerStatus += RecvBuff;
					SerEdit.SetWindowTextW(SerStatus);
					//cout << RecvBuff << endl;
				}
				unsigned char sum[128] = "";
				sign_t(RecvBuff, sum, dk, x, y, IDA2);//SM2签名 
				for (int i = 0; i < 32; i++)
				{
					r[i] = sum[i];
					s[i] = sum[i + 32];
				}
				join(r, s, info);//签名值
				info[256] = '\0';
				//cout << "发送签名:  " << endl;
				//cout << info;
				SerStatus += "发送签名:  \r\n";
				CString strinfo(info);
				SerStatus += info;
				SerEdit.SetWindowTextW(SerStatus);
				memset(RecvBuff, 0, sizeof(RecvBuff));//收到powhash,重置RecvBuff

				//cout << endl;
				SerStatus += "\r\n";
				SerEdit.SetWindowTextW(SerStatus);
				strcpy_s(SendBuff, info);
				RecvBuff[256] = '\0';
				memset(info, 0, sizeof(info));
				k = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
				memset(SendBuff, 0, sizeof(SendBuff));
				if (k < 0) {
					//cout << "发送失败" << endl;
					SerStatus += "发送失败\r\n";
					SerEdit.SetWindowTextW(SerStatus);

				}                   //发送签名
				//yesno = '0';
				//cout << "是否允许主服务器存储文件：\n  1:是 0:否";
				//cin >> yesno;
				int CSFstate= ((CButton*)GetDlgItem(CheckSF))->GetCheck();
				yesno = CSFstate + '0';
				SendBuff[0] = yesno;
				SendBuff[256] = '\0';
				k = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
				memset(SendBuff, 0, sizeof(SendBuff));
				SendBuff[256] = '\0';
				if (k < 0) {
					//cout << "发送失败" << endl;
					SerStatus += "发送失败\r\n";
					SerEdit.SetWindowTextW(SerStatus);
				}
			}
		}
		else//ip地址不正确时
		{

			SerStatus += "请输入正确的ip地址\r\n";
			SerEdit.SetWindowTextW(SerStatus);
		}
	}
	else
	{
		//执行中断连接
		closesocket(SocketClient);
		WSACleanup();

		SerStatus += "已中断连接\r\n";
		SerEdit.SetWindowTextW(SerStatus);
		ConServer.SetWindowTextW((CString)"连接至服务器");
	}
}
//用于检验输入内容是否合适并连接至服务器以及中断的实现

void CMFCClientDlg::OnBnClickedSendfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ConStatus;
	ConServer.GetWindowTextW(ConStatus);
	if ("连接中（点击中断）" == ConStatus)
	{
		//发送文件
		CString StrPath;
		FPath.GetWindowTextW(StrPath);
		SerStatus += "正在发送文件。。。\r\n";
		SerStatus += StrPath;
		SerEdit.SetWindowTextW(SerStatus);
		//开始发送



		std::string path = CT2A(StrPath.GetString());
		if (path == "")path = "D:\\实验库";
		path += "\\";
		//std::string path("D:\\实验库\\");
		std::string g;
		long go;
		struct _finddata_t fileinfo;
		int ts = 0;
		char keys[257];
		go = _findfirst(g.assign(path).append("*").c_str(), &fileinfo);
		memset(keys, 0, sizeof(keys));
		keys[256] = '1';
		while (1) {
			if (_findnext(go, &fileinfo)) { 
				//cout << "发送已结束" << endl; 
				SerStatus += "发送已结束\r\n";
				SerEdit.SetWindowTextW(SerStatus);
				break; }
			if (fileinfo.attrib != 16) {
				k = send(SocketClient, keys, 257, 0);
				memset(SendBuff, 0, sizeof(SendBuff));
				strcpy(SendBuff, fileinfo.name);
				SendBuff[256] = '\0';
				k = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
				//cout << "发送文件";
				//cout << fileinfo.name << endl;
				//cout << "发送中..." << endl;
				fstream out((path + std::string(fileinfo.name)).c_str(), ios::in | ios::binary);//存放发送的信息，发送给sever
				while (!out.eof()) {
					/*此处需要做修改以文本形式存储需要发送的数据然后将文本发送给服务器*/
					/*cout << "请输入要发送的数据按回车结束发送：" << endl;//改为直接发送文件*/
					out.read(info, 256);
					info[256] = '\0';
					/*if (info[0] == '\0')
						break;
						out << info << '\n';*/
					k = send(SocketClient, info, 257, 0);
				}
				out.close();
				ts++;
				k = send(SocketClient, keys, 257, 0);
				if (k > 0) {
					//	cout << "发送第" << ts << "文件结束" << endl; 
					SerStatus += "发送第";
					CString s;
					s.Format(TEXT("%d"), ts);
					SerStatus += s;
					SerStatus += "文件结束\r\n";
					SerEdit.SetWindowTextW(SerStatus);
				}
				else { 
					//	cout << "文件传输异常" << endl; 
					SerStatus += "文件传输异常\r\n";
					SerEdit.SetWindowTextW(SerStatus);
				}
				//system((string("del /q ") + path + string(fileinfo.name)).c_str());
			}

			Sleep(500);

		}
		_findclose(go);

		keys[256] = '0';
		k = send(SocketClient, keys, 257, 0);//结尾标识


		if (k>0) //发送成功
		{
			SerStatus += "发送完成\r\n";
			SerEdit.SetWindowTextW(SerStatus);
		}
		else
		{
			SerStatus += "发送失败\r\n";
			SerEdit.SetWindowTextW(SerStatus);
		}
	}
	else
	{
		SerStatus += "请先连接至服务器\r\n";
		SerEdit.SetWindowTextW(SerStatus);
	}
}
//用于发送文件

void CMFCClientDlg::OnBnClickedDetection()
{
	// TODO: 在此添加控件通知处理程序代码
	SerStatus += "检测中。。。\r\n";
	SerEdit.SetWindowTextW(SerStatus);
	//检测


	if (1)//检测是否符合要求
	{
		SerStatus += "检测完成，环境正常\r\n";
		SerEdit.SetWindowTextW(SerStatus);
	}
	else
	{
		SerStatus += "检测完成，缺失文件，正在初始化\r\n";
		SerEdit.SetWindowTextW(SerStatus);
		//初始化代码


		if (1)//初始化中
		{
			SerStatus += "初始化完成\r\n";
			SerEdit.SetWindowTextW(SerStatus);
		}
		else
		{
			SerStatus += "初始化失败请重新检测\r\n";
			SerEdit.SetWindowTextW(SerStatus);
		}
	}

}
//用于检查环境




