// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "SreenClient.h"
#include "ClientSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	pkbuf=NULL;
	bufoffset=0;
}

CClientSock::~CClientSock()
{
	if(pkbuf!=NULL)
		delete []pkbuf;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::setdlg(CSreenClientDlg *d,int cid,int plen)
{
   dlg=d;
   id=cid;
   pklen=plen;//数据包长度为固定,处理比较方便,一般为1000到65000之间.
   bufoffset=0;
   pkbuf=new char[plen*2];

}

void CClientSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	dlg->myRecvData(this);
	CSocket::OnReceive(nErrorCode);
}

void CClientSock::GetPackage(char *buf)//接收一个长度为pklen的完整数据包
{
	do{
         recvlen=Receive(pkbuf+bufoffset,pklen,0);
	     if(recvlen>0)
		 {
           bufoffset+=recvlen;
		 }
	   }while(bufoffset<pklen);//有可能(%1可能性)只接收到部分数据,就再接收一次
	   memcpy(buf,pkbuf,pklen);
       bufoffset=bufoffset-pklen;
	   if(bufoffset>0)//有%99的可能性,bufoffset=0
	      memcpy(pkbuf,pkbuf+pklen,bufoffset);  
}

void CClientSock::SendCommandData(int type, char *buf, int len)
{
   NETPACKAGE pack;
   pack.type=type;
   pack.len=len;
   memset(pack.buf,7,pklen-8);
   memcpy(pack.buf,buf,len);
   Send((char*)&pack,pklen,0);
}
