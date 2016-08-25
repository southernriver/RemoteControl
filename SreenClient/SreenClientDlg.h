// SreenClientDlg.h : header file
//

#if !defined(AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_)
#define AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ClientSock.h"
/////////////////////////////////////////////////////////////////////////////
// CSreenClientDlg dialog
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

class CSreenClientDlg : public CDialog
{
// Construction
public:
	CSreenClientDlg(CWnd* pParent = NULL);	// standard constructor
public:
	void drawSreen();
	void initDrawParam();
	void initDrawSreen();
	void myRecvData(CClientSock *pc);
	CClientSock *pclient;

	USERINFO usrinfo;
	NETPACKAGE usrpack;//用户信息
	int pklen;//数据长度

	BITMAPINFOHEADER *m_pBIH;//位图头
	unsigned char *m_pDibBits;//指向解压后图像数据起点
	unsigned char *m_pDib;//图像数据缓冲
	long lbitsOffset;//接收图像数据偏移
	CapSreenHeader cheader;//图像头信息
	
	int scrx;//远程屏幕水平起点
	int scry;//远程屏幕垂直起点
	int scrxlm;//水平移动最大值
	int scrylm;//垂直移动最大值
	int capflag;//是否捕获成功
	int m_width;//远程屏幕的宽度
	int m_height;//远程屏幕的高度
	int cwidth;//绘制区域的宽度
    int cheight;////绘制区域的高度
	int bcontrol;//控制有效

    
// Dialog Data
	//{{AFX_DATA(CSreenClientDlg)
	enum { IDD = IDD_SREENCLIENT_DIALOG };
	CScrollBar	m_hbar;
	CScrollBar	m_vbar;
	CString	m_ip;
	int		m_port;
	CString	m_usrpwd;
	CString	m_usrname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSreenClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSreenClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonControl();
	afx_msg void OnButtonGetcap();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButtonKetinput();
	afx_msg void OnButtonKeyctrl();
	afx_msg void OnButtonKeyshift();
	afx_msg void OnButtonKeyenter();
	afx_msg void OnButtonKetbackspace();
	afx_msg void OnButtonKeytab();
	afx_msg void OnButtonKeycapslock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEditIp();
    afx_msg void OnBnClickedShutdown();
    afx_msg void OnBnClickedButton2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_)
