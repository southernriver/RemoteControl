#if !defined(AFX_LISTENSOCK_H__92F863DC_F7A2_47D3_8028_E4B92DECBACC__INCLUDED_)
#define AFX_LISTENSOCK_H__92F863DC_F7A2_47D3_8028_E4B92DECBACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSock.h : header file
//

#include "SreenServerDlg.h"
class CSreenServerDlg;


/////////////////////////////////////////////////////////////////////////////
// CListenSock command target

class CListenSock : public CSocket
{
// Attributes
public:
    CSreenServerDlg *dlg;
// Operations
public:
	CListenSock();
	virtual ~CListenSock();

// Overrides
public:
	void setdlg(CSreenServerDlg *d);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSock)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCK_H__92F863DC_F7A2_47D3_8028_E4B92DECBACC__INCLUDED_)
