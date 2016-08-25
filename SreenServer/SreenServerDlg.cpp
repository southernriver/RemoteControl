// SreenServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SreenServer.h"
#include "SreenServerDlg.h"
#include"Shutdown.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSreenServerDlg dialog
//对话框的构造函数
CSreenServerDlg::CSreenServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSreenServerDlg::IDD, pParent)  //首先调用基类的构造函数
{
	//{{AFX_DATA_INIT(CSreenServerDlg)
	m_tport = 0;             //初始化端口为0 
	m_filename = _T("");     //初始化图片名字
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    //软件显示图标设置
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//重写对话框DoDataExchange函数
void CSreenServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSreenServerDlg)
	DDX_Text(pDX, IDC_EDIT_TCPPORT, m_tport);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSreenServerDlg, CDialog)
	//{{AFX_MSG_MAP(CSreenServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SAVEBMP, OnButtonSavebmp)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_STN_CLICKED(IDC_STATIC1, &CSreenServerDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSreenServerDlg message handlers

BOOL CSreenServerDlg::OnInitDialog()
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
    plisten=NULL;
	pclient=NULL;
	clientnum=1;
	m_tport=8000;
	islogin=0;
/*  进行数据的交换。
    BOOL UpdateData(BOOL bSaveAndValidate = TRUE);
    TRUE - 将数据从控件放置到变量
    FALSE - 将数据从变量放置到控件
*/
    GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//系统响应函数
//尤其是最大化和最小化窗口的时候
void CSreenServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	   
		CDialog::OnSysCommand(nID, lParam);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSreenServerDlg::OnPaint() 
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
HCURSOR CSreenServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSreenServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	CString name;

    /*
    1.2.4 实现过程（DDX_Text）
    1)UpdateData函数会调用DoDataExchange
    2)在DoDataExchange函数中调用相应的
    DDX_Text的函数
    3)在DDX_Text函数中，根据子控件ID，
    调用GetDlgItem函数获取子控件窗
    口句柄
    4)根据子控件窗口句柄使用GetWindowText
    函数，获取窗口数据。
   */
	UpdateData(TRUE);
	GetDlgItemText(IDC_BUTTON_START,name);  //获取Item上面的文字
	if(name=="开始服务")
	{
	  plisten=new CListenSock;
	  plisten->Create(m_tport);//创建用于监听的Socket,在本机的8000监听,等待客户端来连接
	  plisten->setdlg(this);
	  //点开始--程序--附件--命令提示符,打开一个终端窗口，
	  //输入命令netstat -an 就可看到有没有打开端口3009，也能看到所有的网络连接状态
	  plisten->Listen(10);//同时可连接10个客户端
	  SetDlgItemText(IDC_BUTTON_START,"停止服务");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_START,"开始服务");
		if(plisten!=NULL)
		{
           plisten->Close();//关闭监听
	       delete plisten;
		}
	    if(pclient!=NULL)
		{
           pclient->Close();
		   delete pclient;
		}
	   
	}

}

 

void CSreenServerDlg::CapSreen()
{
	HWND hWnd = ::GetDesktopWindow();//获得屏幕的HWND.
	HDC hScreenDC = ::GetDC(hWnd);   //获得屏幕的HDC.
	HDC MemDC = ::CreateCompatibleDC(hScreenDC);
	RECT rect; 
	::GetWindowRect(hWnd,&rect);
	SIZE screensize;
	screensize.cx=rect.right-rect.left;
	screensize.cy=rect.bottom-rect.top;
	hBitmap = ::CreateCompatibleBitmap(hScreenDC,screensize.cx,screensize.cy);
	HGDIOBJ hOldBMP = ::SelectObject(MemDC,hBitmap);
	::BitBlt(MemDC,0,0,screensize.cx,screensize.cy,hScreenDC,rect.left,rect.top,SRCCOPY);
	::SelectObject(MemDC,hOldBMP);
	::DeleteObject(MemDC);
	::ReleaseDC(hWnd,hScreenDC);

}

void CSreenServerDlg::OnButtonSavebmp() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="All files (*.*)|*.*|bmp files(*.bmp)|*.bmp||";


	CFileDialog fd(false,"bmp","aaa",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(IDOK==fd.DoModal())
	{
		m_filename=fd.GetPathName();
		CapSreen();
        WriteBmpToFile(hBitmap,m_filename);
		UpdateData(FALSE);
	}
}

void CSreenServerDlg::WriteBmpToFile(HBITMAP hBitmap, CString strFileName)
{
	HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//当前分辨率下每个像素所占字节数  
    ::DeleteDC(hDC);

    WORD   wBitCount;   //位图中每个像素所占字节数    
    if (iBits <= 1)
		wBitCount = 1;
    else if (iBits <= 4)
		wBitCount = 4;
    else if (iBits <= 8)
		wBitCount = 8;
    else if (iBits <= 24)
		wBitCount = 24;
    else
		wBitCount = iBits;
		    
	DWORD   dwPaletteSize=0;	//调色板大小， 位图中像素字节大小 
    if (wBitCount <= 8)		
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);	
	

	BITMAP  bm;        //位图属性结构
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  

    
	BITMAPINFOHEADER   bi,bi1;       //位图信息头结构     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB; //BI_RGB表示位图没有压缩
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	bi1=bi;
	bi1.biBitCount=24;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //为位图内容分配内存
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // 处理调色板 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
	int nOutputBytes = 0;
   
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// 获取该调色板下新的像素值
    if (hOldPal)//恢复调色板
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    }
   
	BITMAPFILEHEADER   bmfHdr; //位图文件头结构     
	bmfHdr.bfType = 0x4D42;  // "BM"  	// 设置位图文件头
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	HANDLE hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//创建位图文件   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);	// 写入位图文件头
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// 写入位图文件其余内容


	GlobalUnlock(hDib);   //清除   
	GlobalFree(hDib);
	CloseHandle(hFile); 
   

}
//Accept接收客户的连接
void CSreenServerDlg::myAccept(CListenSock *pl)//如果客户端来连接8000,就会调用这个函数
{
	SOCKADDR_IN clientaddr; //
	int addrlen=sizeof(clientaddr);
	pclient=new CClientSock;
	int plen=sizeof(NETPACKAGE);
	pclient->setdlg(this,clientnum,plen);
    pl->Accept(*pclient,(LPSOCKADDR)&clientaddr,&addrlen);//接收这个客户连接
	clientnum++;
	CString str;
    str.Format("client ip:%s,port:%d",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	//看到对方的IP地址和端口,也可用命令netstat -an
 //   AfxMessageBox(str);
    CString  s ;
    GetDlgItem(IDC_STATIC1)->GetWindowText(s);
    GetDlgItem(IDC_STATIC1)->SetWindowText(s+_T("\r\n"+str));
    
}

void CSreenServerDlg::myRecvData(CClientSock *pc)//如果某一个客户发过来数据,就会调用这个函数
{
    
    NETPACKAGE pack;
	USERINFO usrinfo;
	MYMOUSEINFO mparam;
    CString tstr;
	pc->GetPackage((char*)&pack);
	switch(pack.type)
	{
	case 1://用户登录
          memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		  //tstr.Format("User Login:%s,%s,%d",usrinfo.name,usrinfo.password,usrinfo.uport);
		 // AfxMessageBox(tstr);
		  tstr=usrinfo.password;
		  if(tstr=="southernriver@163.com")
		  {
			  strcpy(usrinfo.password,"passwork ok");//密码正确
			  //SetTimer(1,1000,NULL);
			  islogin=1;
		  }
		  else
		  {
              strcpy(usrinfo.password,"passwork error");////密码错误
		  }
          GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		  pc->SendCommandData(1,(char *)&usrinfo,sizeof(usrinfo));//回复用户密码是否正确
		  break;
	case 2://用户退出
          memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		  //tstr.Format("User Logoff:%s,%s,%d",usrinfo.name,usrinfo.password,usrinfo.uport);
		 // AfxMessageBox(tstr);
		  //KillTimer(1);
		  pc->SendCommandData(2,(char *)&usrinfo,sizeof(usrinfo));//回复退出
		  break;
    case 3://屏幕发送命令
		memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		SendSreenToClient();
		break;
	case 5://控制命令
		 memcpy(&mparam,pack.buf,sizeof(mparam));
		  if(mparam.type==1)
		  {
				SetCursorPos (mparam.x, mparam.y);
				mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
		  }
	      if(mparam.type==2)
		  {
			 SetCursorPos (mparam.x, mparam.y);
             mouse_event (MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
             mouse_event (MOUSEEVENTF_RIGHTUP, 0,0,0,0);
		  }
	      if(mparam.type==3)
		  {
				SetCursorPos (mparam.x, mparam.y);
                mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
                mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
                Sleep(100);
	            mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
                mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
		  }
		 if(mparam.type==8)
		 {
			 if(mparam.keytype==1)//按下键
			    ::keybd_event(mparam.keyct1,0,0,0);
			 if(mparam.keytype==2)//放开键
			    ::keybd_event(mparam.keyct1,0,KEYEVENTF_KEYUP,0);
		 }
        break;
    case 110:
        ReSetWindow(EWX_SHUTDOWN, TRUE);   //关机
        break;
	}
 

        
}

void CSreenServerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(pclient!=NULL)
	{
	  CapSreen();
      SentSreen(hBitmap,pclient);
	}
	CDialog::OnTimer(nIDEvent);
}

//发送截屏命令
void CSreenServerDlg::SentSreen(HBITMAP hBitmap, CClientSock *pc)
{
	 HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//当前分辨率下每个像素所占字节数  
    ::DeleteDC(hDC);

    WORD   wBitCount;   //位图中每个像素所占字节数    
    if (iBits <= 1)
		wBitCount = 1;
    else if (iBits <= 4)
		wBitCount = 4;
    else if (iBits <= 8)
		wBitCount = 8;
    else if (iBits <= 24)
		wBitCount = 24;
    else
		wBitCount = iBits;
		    
	DWORD   dwPaletteSize=0;	//调色板大小， 位图中像素字节大小 
    if (wBitCount <= 8)		
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);	
	

	BITMAP  bm;        //位图属性结构
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  

    
	BITMAPINFOHEADER   bi,bi1;       //位图信息头结构     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB; //BI_RGB表示位图没有压缩
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	bi1=bi;
	bi1.biBitCount=24;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //为位图内容分配内存
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // 处理调色板 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
	int nOutputBytes = 0;
	unsigned char *m_pDibBits;
	m_pDibBits = new unsigned char [dwBmBitsSize];
    //::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,m_pDibBits,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// 获取该调色板下新的像素值
    if (hOldPal)//恢复调色板
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    }
	int i=0,j=0;
     unsigned char* pcolor;
     pcolor=(unsigned char*)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	//得到像素值
	for(j=0;j<dwBmBitsSize;j++)
	{
		if(j%4==3)
			j++;
        m_pDibBits[i]=pcolor[j];		
		i++;
	}
     
  


 //////////////////////// //发送图像头信息 /////////////////////////////
	   	CapSreenHeader cheader;
        cheader.factlen=i; //图像长度
	    NETPACKAGE pack;
       long filestep=0;
	   long fileend=0;
	   long lFileSize=i;//图像长度
	 
       	int end = 0;	 
	    int len=0;
		int dtlen=50000;//数据块长度

		int plen=sizeof(NETPACKAGE);//数据包长度50008

	    filestep=lFileSize/dtlen;//数据块数
        fileend=lFileSize%dtlen;//最后一块数据长度

		cheader.filelength=lFileSize;////图像文件长度
        cheader.blocklen=dtlen;//数据块长度
        cheader.width=bm.bmWidth;//图像宽度
        cheader.height=bm.bmHeight;//图像高度

         pack.type=3; //图像头命令
         pack.len=sizeof(cheader);//图像头信息长度
         memset(pack.buf,7,dtlen);
		 memcpy(pack.buf,(char*)&cheader,pack.len);
	     pc->Send((unsigned char*)&pack,plen,0);//发送图像头信息
	     Sleep(100);

        ////////////////////发送图像内容///////////////// 
	
	     pack.type=4; //图像内容命令
         pack.len=dtlen;//图像块长度

		for(j=0;j<filestep;j++)
		{
			memcpy(pack.buf,&m_pDibBits[j*dtlen],dtlen);
	        pc->Send((unsigned char*)&pack,plen,0);//发送图像信息 
		}   
		 pack.type=5; ////最后一块数据命令
         pack.len=fileend;//最后一块数据长度
         memset(pack.buf,7,dtlen);
		 memcpy(pack.buf,&m_pDibBits[filestep*dtlen],fileend);//发送最后一块数据
	     pc->Send((unsigned char*)&pack,plen,0);//发送图像头信息
   
    GlobalUnlock(hDib);   //清除   
	GlobalFree(hDib);
	delete []m_pDibBits;


}

void CSreenServerDlg::SendSreenToClient()
{
   	if(pclient!=NULL&&islogin==1)
	{
	  CapSreen();
      SentSreen(hBitmap,pclient);
	}
}


void CSreenServerDlg::OnStnClickedStatic1()
{
    // TODO:  在此添加控件通知处理程序代码
}
