// SreenServerDlg.h : header file
//

#if !defined(AFX_SREENSERVERDLG_H__4419CFA3_C4DB_4934_B4B4_1BD5A7F93CB2__INCLUDED_)
#define AFX_SREENSERVERDLG_H__4419CFA3_C4DB_4934_B4B4_1BD5A7F93CB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSreenServerDlg dialog
#include "ListenSock.h"
#include "ClientSock.h"
struct USERINFO{//用户信息
	char name[30];
	char password[20];
    int uport;
};
struct CapSreenHeader//图像头信息
{
	long filelength;
	int width;
	int height;
	int blocklen;
	long factlen;
};
struct MYMOUSEINFO
{
	int x;
	int y;
	int type; //1,2,3,8 左按下,右按下,双击,键盘
	unsigned char keyct1;//键值
	unsigned char keyct2;
	int keytype;//UP或DOWN 1,2
};

class CClientSock;
class CListenSock;
class CSreenServerDlg	 : public CDialog
{
// Construction
public:
	void CapSreen();
	CSreenServerDlg(CWnd* pParent = NULL);	// standard constructor
public:
	void SendSreenToClient();
	void SentSreen(HBITMAP hBitmap,CClientSock* pc);
	void myRecvData(CClientSock* pc);
	void myAccept(CListenSock* pl);
	void WriteBmpToFile(HBITMAP hBitmap,CString strFileName);

	
		HBITMAP hBitmap;
		CListenSock* plisten;
		CClientSock* pclient;
		int clientnum;//统计客户数量
		int islogin;
// Dialog Data
	//{{AFX_DATA(CSreenServerDlg)
	enum { IDD = IDD_SREENSERVER_DIALOG };
	int		m_tport;
	CString	m_filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSreenServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSreenServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonSavebmp();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStatic1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SREENSERVERDLG_H__4419CFA3_C4DB_4934_B4B4_1BD5A7F93CB2__INCLUDED_)
