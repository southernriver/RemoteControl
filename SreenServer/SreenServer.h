// SreenServer.h : main header file for the SREENSERVER application
//

#if !defined(AFX_SREENSERVER_H__F2744058_17D5_4E72_BF41_C9BF9DE87CBF__INCLUDED_)
#define AFX_SREENSERVER_H__F2744058_17D5_4E72_BF41_C9BF9DE87CBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSreenServerApp:
// See SreenServer.cpp for the implementation of this class
//

class CSreenServerApp : public CWinApp
{
public:
	CSreenServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSreenServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSreenServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SREENSERVER_H__F2744058_17D5_4E72_BF41_C9BF9DE87CBF__INCLUDED_)
