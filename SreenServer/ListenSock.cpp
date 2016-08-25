// ListenSock.cpp : implementation file
//

#include "stdafx.h"
#include "SreenServer.h"
#include "ListenSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSock

CListenSock::CListenSock()
{
}

CListenSock::~CListenSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSock, CSocket)
	//{{AFX_MSG_MAP(CListenSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSock member functions

void CListenSock::setdlg(CSreenServerDlg *d)
{
   dlg=d;
}

void CListenSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	dlg->myAccept(this);

	CSocket::OnAccept(nErrorCode);
}

 
