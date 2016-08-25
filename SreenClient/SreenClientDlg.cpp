// SreenClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SreenClient.h"
#include "SreenClientDlg.h"
#include"Shutdown.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSreenClientDlg dialog

CSreenClientDlg::CSreenClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSreenClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSreenClientDlg)
	m_ip = _T("");
	m_port = 0;
	m_usrpwd = _T("");
	m_usrname = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSreenClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSreenClientDlg)
	DDX_Control(pDX, IDC_SCROLLBAR2, m_hbar);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_vbar);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_PWD, m_usrpwd);
	DDX_Text(pDX, IDC_EDIT_USRNAME, m_usrname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSreenClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSreenClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL, OnButtonControl)
	ON_BN_CLICKED(IDC_BUTTON_GETCAP, OnButtonGetcap)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_KETINPUT, OnButtonKetinput)
	ON_BN_CLICKED(IDC_BUTTON_KEYCTRL, OnButtonKeyctrl)
	ON_BN_CLICKED(IDC_BUTTON_KEYSHIFT, OnButtonKeyshift)
	ON_BN_CLICKED(IDC_BUTTON_KEYENTER, OnButtonKeyenter)
	ON_BN_CLICKED(IDC_BUTTON_KETBACKSPACE, OnButtonKetbackspace)
	ON_BN_CLICKED(IDC_BUTTON_KEYTAB, OnButtonKeytab)
	ON_BN_CLICKED(IDC_BUTTON_KEYCAPSLOCK, OnButtonKeycapslock)
	//}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_EDIT_IP, &CSreenClientDlg::OnEnChangeEditIp)
    ON_BN_CLICKED(IDC_SHUTDOWN, &CSreenClientDlg::OnBnClickedShutdown)
    ON_BN_CLICKED(IDC_BUTTON2, &CSreenClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSreenClientDlg message handlers

BOOL CSreenClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	pclient=NULL;
	m_ip="192.168.1.110";
	m_port=8000;
	m_usrpwd="southernriver@163.com";
	m_usrname="chenliang";
	UpdateData(FALSE);
	m_pBIH=NULL;
    m_pDibBits=NULL;

    m_pDib=NULL;
    pklen=sizeof(NETPACKAGE);
	lbitsOffset=0;
    capflag=0;
	bcontrol=0;
    initDrawParam();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSreenClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSreenClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSreenClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSreenClientDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	CString name;
	
	GetDlgItemText(IDC_BUTTON_CONNECT,name);
	UpdateData(TRUE);
	if(name=="连接")
	{
    	pclient=new CClientSock;
	    pclient->Create();//创建普通的SOCKET
	    pklen=sizeof(NETPACKAGE);
	    pclient->setdlg(this,1,pklen);
		int rt=pclient->Connect(m_ip,m_port);//连接服务端
		if(rt==1)
		{
	    	strcpy(usrinfo.name,m_usrname.GetBuffer(0));
			strcpy(usrinfo.password,m_usrpwd.GetBuffer(0));
			usrinfo.uport=3100;
			pclient->SendCommandData(1,(char*)&usrinfo,sizeof(USERINFO));

		}
		else
             AfxMessageBox("connect server Faile!");
	    SetDlgItemText(IDC_BUTTON_CONNECT,"退出连接");
	}
	else
	{
		pclient->SendCommandData(2,(char*)&usrinfo,sizeof(USERINFO));
		pclient->Close();
		delete pclient;
		pclient=NULL;

        if(m_pDib!=NULL)
			delete[] m_pDib;
        m_pDib=NULL;
		SetDlgItemText(IDC_BUTTON_CONNECT,"连接");
	}

}

void CSreenClientDlg::myRecvData(CClientSock *pc)
{
    CString tstr;
	pc->GetPackage((char*)&usrpack);
	switch(usrpack.type)
	{
	case 1://用户登录
          memcpy(&usrinfo,usrpack.buf,sizeof(usrinfo));
		 // tstr.Format("Ack Login:%s,%s,%d",usrinfo.name,usrinfo.password,usrinfo.uport);
		//  AfxMessageBox(tstr);
		  tstr=usrinfo.password;
		  if(tstr=="passwork ok")
			  AfxMessageBox("Login OK!");//密码正确
		  else
              AfxMessageBox("Your Passwor Error!");////密码错误
		  break;
	case 2://用户退出
          memcpy(&usrinfo,usrpack.buf,sizeof(usrinfo));
		  tstr.Format("OK Logoff",usrinfo.name,usrinfo.password,usrinfo.uport);
		  AfxMessageBox(tstr);
		  break;
    case 3://获得屏幕
		 memcpy(&cheader,usrpack.buf,sizeof(cheader));
		 if(m_pDib==NULL)
		 {
	         int m_dwDibSize = cheader.filelength + sizeof( BITMAPINFOHEADER )+1000;
	         m_pDib = new unsigned char[m_dwDibSize];   
	         m_pDibBits=&m_pDib[sizeof(BITMAPINFOHEADER )];
		 }
		 lbitsOffset=0;
   //      AfxMessageBox("接收到了截屏数据");
		 break;
    case 4:
		  if(m_pDibBits!=NULL&&usrpack.len==50000)
			{ 
			   memcpy(&m_pDibBits[lbitsOffset],usrpack.buf,usrpack.len);
			   lbitsOffset=lbitsOffset+usrpack.len;
			}
		  break;
    case 5:
          if(m_pDibBits!=NULL)
			{ 
			   memcpy(&m_pDibBits[lbitsOffset],usrpack.buf,usrpack.len);
			   lbitsOffset=lbitsOffset+usrpack.len;
			}
		    if(lbitsOffset!=cheader.filelength)//接收错误
			{
				tstr.Format("Error:%d!=%d",lbitsOffset,cheader.filelength);
		        AfxMessageBox(tstr);
				return;
			}
			 m_pBIH = (BITMAPINFOHEADER*)m_pDib;
	         m_pBIH->biSize= sizeof(BITMAPINFOHEADER);
	         m_pBIH->biWidth	= cheader.width;
	         m_pBIH->biHeight= cheader.height;
	         m_pBIH->biPlanes= 1;
	         m_pBIH->biBitCount= 24;
	         m_pBIH->biCompression= BI_RGB;
	         m_pBIH->biSizeImage	= 0;
	         m_pBIH->biXPelsPerMeter	= 0;
	         m_pBIH->biYPelsPerMeter	= 0;
	         m_pBIH->biClrUsed= 0;
	         m_pBIH->biClrImportant= 0;
             initDrawSreen();
             break;  
	}

}

void CSreenClientDlg::OnButtonControl() 
{
	// TODO: Add your control notification handler code here
	 
	

	if(bcontrol==1)
	{
		bcontrol=0;
		SetDlgItemText(IDC_BUTTON_CONTROL,"鼠键控制");
		GetDlgItem(IDC_BUTTON_KETINPUT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_KEYCTRL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_KEYSHIFT)->ShowWindow(SW_HIDE);
		GetDlgItem(	IDC_BUTTON_KEYENTER)->ShowWindow(SW_HIDE);

		GetDlgItem(	IDC_BUTTON_KETBACKSPACE)->ShowWindow(SW_HIDE);
		GetDlgItem(	IDC_BUTTON_KEYTAB)->ShowWindow(SW_HIDE);
		GetDlgItem(	IDC_BUTTON_KEYCAPSLOCK)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_USRNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_USRNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PWD)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_STATIC_IP,"IP地址");
	}
	else
	{
		bcontrol=1;
		SetDlgItemText(IDC_BUTTON_CONTROL,"停止控制");
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_USRNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_USRNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PWD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PWD)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_KETINPUT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_KEYCTRL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_KEYSHIFT)->ShowWindow(SW_SHOW);
		GetDlgItem(	IDC_BUTTON_KEYENTER)->ShowWindow(SW_SHOW);

			GetDlgItem(	IDC_BUTTON_KETBACKSPACE)->ShowWindow(SW_SHOW);
			GetDlgItem(	IDC_BUTTON_KEYTAB)->ShowWindow(SW_SHOW);
			GetDlgItem(	IDC_BUTTON_KEYCAPSLOCK)->ShowWindow(SW_SHOW);
		
		SetDlgItemText(IDC_STATIC_IP,"字符串");
        CString s = "";
        GetDlgItem(IDC_EDIT_IP)->SetWindowText(s);
	}
}
//获得屏幕
void CSreenClientDlg::OnButtonGetcap() 
{
	// TODO: Add your control notification handler code here

	if(pclient!=NULL)
    	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));

/*	CClientDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
    int w=rect.Width();
	int h=rect.Height();
	CRect rect1,rect2;
    GetDlgItem(IDC_SCROLLBAR1)->GetClientRect(&rect1);
    GetDlgItem(IDC_SCROLLBAR2)->GetClientRect(&rect2);
    w=w-rect1.Width()-15;
	h=h-rect2.Height()-15;
	dc.MoveTo(0,75);
	dc.LineTo(w,75);
	dc.LineTo(w,h);
	dc.LineTo(0,h);
	dc.LineTo(0,75);*/

}


void CSreenClientDlg::initDrawSreen()
{
    m_width=m_pBIH->biWidth;;
	m_height=m_pBIH->biHeight;

	scrylm=m_height-cheight;
	if(scrylm<0)
		scrylm=0;
    scrxlm=m_width-cwidth;
	if(scrxlm<0)
		scrxlm=0;

//	scrx=0;
//	scry=0;

	m_vbar.SetScrollRange(0,scrylm,TRUE);
	m_vbar.SetScrollPos(scry,TRUE);
	m_hbar.SetScrollRange(0,scrxlm,TRUE);
	m_hbar.SetScrollPos(scrx,TRUE);
	UpdateData(FALSE);
	capflag=1;
	drawSreen();

}

void CSreenClientDlg::initDrawParam()
{
	CRect rect;
	GetClientRect(&rect);
    int w=rect.Width();
	int h=rect.Height();
	CRect rect1,rect2;
    GetDlgItem(IDC_SCROLLBAR1)->GetClientRect(&rect1);
    GetDlgItem(IDC_SCROLLBAR2)->GetClientRect(&rect2);
     cwidth=w-rect1.Width()-15;
	cheight=h-rect2.Height()-90;
//	 cwidth=655-15;
//	 cheight=570-90;
	scrx=0;
	scry=0;
	scrylm=1000;
    scrxlm=1000;
	m_vbar.SetScrollRange(0,scrylm,TRUE);
	m_vbar.SetScrollPos(0,TRUE);
	m_hbar.SetScrollRange(0,scrxlm,TRUE);
	m_hbar.SetScrollPos(0,TRUE);
	UpdateData(FALSE);

}

void CSreenClientDlg::drawSreen()
{
	if(m_pBIH==NULL||m_pDibBits==NULL)
		return;
    if(capflag==0)
		return;
	 CDC *pdc=GetDC();
	// Use StretchDIBits to draw the Dib.
	 StretchDIBits( pdc->m_hDC, 0, 75,
		cwidth, cheight,
		scrx, scry,
		cwidth, cheight,
		m_pDibBits,
		(BITMAPINFO *)m_pBIH,
		BI_RGB, SRCCOPY );
	 ReleaseDC(pdc);

	
}

void CSreenClientDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	    int nPos1=m_vbar.GetScrollPos();
		if(nSBCode==SB_LINEDOWN)
		{
			scry=scry+10;
			if(scry>scrylm)
				scry=scrylm;
			nPos1=scry;
			drawSreen();
			 
		}
		if(nSBCode==SB_LINEUP)
		{
			scry=scry-10;
			if(scry<0)
				scry=0;
			nPos1=scry;
			drawSreen();
		
		}
		if(nSBCode==SB_THUMBTRACK)
		{
			scry=nPos;
			nPos1=nPos;
			if(nPos1>scrylm)
                nPos1=scrylm;
			if(scry<0)
				scry=0;
			if(scry>scrylm)
				scry=scrylm;
			nPos1=scry;
			drawSreen();
			
		}
         m_vbar.SetScrollPos(nPos1);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSreenClientDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nPos1=m_hbar.GetScrollPos();
		if(nSBCode==SB_LINERIGHT)
		{
			scrx=scrx+10;
			if(scrx>scrxlm)
				scrx=scrxlm;
		     nPos1=scrx;
			 drawSreen();
		}
		if(nSBCode==SB_LINELEFT)
		{
			scrx=scrx-10;
			if(scrx<0)
				scrx=0;
			 nPos1=scrx;
			 drawSreen();
		}
		if(nSBCode==SB_THUMBTRACK)
		{
			scrx=nPos;
			nPos1=nPos;
			if(scrx<0)
				scrx=0;
			if(scrx>scrxlm)
				scrx=scrxlm;
			 nPos1=scrx;
			drawSreen();
		
		}
		m_hbar.SetScrollPos(nPos1,TRUE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSreenClientDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MYMOUSEINFO mparam;
	if(bcontrol==1)
	{
		mparam.x=point.x+scrx;
	    mparam.y=point.y+scrylm-scry-75;
		mparam.type=2;
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		Sleep(100);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
	    
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CSreenClientDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	MYMOUSEINFO mparam;
	if(bcontrol==1)
	{
		mparam.x=point.x+scrx;
	    mparam.y=point.y+scrylm-scry-75;
	//	CString str;
	//	str.Format("%d,%d--%d,%d",mparam.x,mparam.y,scrx,scry);
	//	AfxMessageBox(str);
		mparam.type=1;
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		Sleep(100);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
			
	    
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CSreenClientDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MYMOUSEINFO mparam;
	if(bcontrol==1)
	{
		mparam.x=point.x+scrx;
	    mparam.y=point.y+scrylm-scry-75;
		mparam.type=3;
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		Sleep(100);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
	    
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CSreenClientDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format("%d",nChar);
	AfxMessageBox(str);
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSreenClientDlg::OnButtonKetinput() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;
	UpdateData();
	if(bcontrol==1)
	{
		int i=0;
		int len=m_ip.GetLength();
		 m_ip.MakeUpper();
		for(i=0;i<len;i++)
		{
		mparam.keyct1=m_ip.GetAt(i);
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		mparam.keytype=1;
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		Sleep(10);
		mparam.keytype=2;
		if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));

		}

		Sleep(1000);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
			
	   m_ip.MakeLower();
	}
}

void CSreenClientDlg::OnButtonKeyctrl() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;
	CString name;
	GetDlgItemText(IDC_BUTTON_KEYCTRL,name);
    
	if(bcontrol==1)
	{
		mparam.keyct1=VK_CONTROL;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		if(name=="按下Ctrl")
		{
		   mparam.keytype=1;
		   SetDlgItemText(IDC_BUTTON_KEYCTRL,"放开Ctrl");
		}
		else
		{
           mparam.keytype=2;
		    SetDlgItemText(IDC_BUTTON_KEYCTRL,"按下Ctrl");
		}
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
	}
}

void CSreenClientDlg::OnButtonKeyshift() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;
	CString name;
	GetDlgItemText(IDC_BUTTON_KEYSHIFT,name);
    
	if(bcontrol==1)
	{
		mparam.keyct1=VK_SHIFT;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		if(name=="按下Shift")
		{
		   mparam.keytype=1;
		   SetDlgItemText(IDC_BUTTON_KEYSHIFT,"放开Shift");
		}
		else
		{
           mparam.keytype=2;
		    SetDlgItemText(IDC_BUTTON_KEYSHIFT,"按下Shift");
		}
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
	}
}

void CSreenClientDlg::OnButtonKeyenter() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;
 
    
	if(bcontrol==1)
	{
		mparam.keyct1=VK_RETURN;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		mparam.keytype=1;
	    if(pclient!=NULL)
           pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
        mparam.keytype=2; 
		Sleep(100);
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
	   Sleep(1000);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
	}
}

void CSreenClientDlg::OnButtonKetbackspace() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;

	if(bcontrol==1)
	{
		mparam.keyct1=VK_BACK;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		mparam.keytype=1;
	    if(pclient!=NULL)
           pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
        mparam.keytype=2; 
		Sleep(100);
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		 Sleep(1000);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
	}
}

void CSreenClientDlg::OnButtonKeytab() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;

	if(bcontrol==1)
	{
		mparam.keyct1=VK_TAB;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		mparam.keytype=1;
	    if(pclient!=NULL)
           pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
        mparam.keytype=2; 
		Sleep(100);
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
		Sleep(1000);
       if(pclient!=NULL)
        	pclient->SendCommandData(3,(char*)&usrinfo,sizeof(USERINFO));
	}
}

void CSreenClientDlg::OnButtonKeycapslock() 
{
	// TODO: Add your control notification handler code here
	MYMOUSEINFO mparam;

	if(bcontrol==1)
	{
		mparam.keyct1=VK_CAPITAL;
	    mparam.y=10;
		mparam.x=10;
		mparam.type=8;
		mparam.keytype=1;
	    if(pclient!=NULL)
           pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
        mparam.keytype=2; 
		Sleep(100);
        if(pclient!=NULL)
        	pclient->SendCommandData(5,(char*)&mparam,sizeof(MYMOUSEINFO));
	}
}


void CSreenClientDlg::OnEnChangeEditIp()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialog::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}


void CSreenClientDlg::OnBnClickedShutdown()
{
    // TODO:  在此添加控件通知处理程序代码
    if (bcontrol==1)
        pclient->SendCommandData(110, (char*)&usrinfo, sizeof(USERINFO));
}


void CSreenClientDlg::OnBnClickedButton2()
{
    // TODO:  在此添加控件通知处理程序代码
    ReSetWindow(EWX_SHUTDOWN, TRUE);   //关机
}
