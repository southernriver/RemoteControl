// SreenClient.h : main header file for the SREENCLIENT application
//

#if !defined(AFX_SREENCLIENT_H__151A93B3_7736_4995_8373_E7AE71B74304__INCLUDED_)
#define AFX_SREENCLIENT_H__151A93B3_7736_4995_8373_E7AE71B74304__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSreenClientApp:
// See SreenClient.cpp for the implementation of this class
//

class CSreenClientApp : public CWinApp
{
public:
	CSreenClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSreenClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSreenClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SREENCLIENT_H__151A93B3_7736_4995_8373_E7AE71B74304__INCLUDED_)
