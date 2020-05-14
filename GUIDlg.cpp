// GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AboutDlg.h"
#include "GUIDlg.h"
#include "GUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg

IMPLEMENT_DYNAMIC(CGUIDlg, CPropertySheet)

CGUIDlg::CGUIDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CGUIDlg::CGUIDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CGUIDlg::~CGUIDlg()
{
}


BEGIN_MESSAGE_MAP(CGUIDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CGUIDlg)
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
void CGUIDlg::SetLogoText(CString Text)
{
	m_LogoText = Text;
}

void CGUIDlg::SetLogoFont(CString Name, int nHeight/* = 24*/,
	int nWeight/* = FW_BOLD*/, BYTE bItalic/* = true*/, BYTE bUnderline/* = false*/)
{
	if(m_fontLogo.m_hObject)
	{
		m_fontLogo.Detach();
	}
	m_fontLogo.CreateFont(nHeight, 0, 0, 0, nWeight, bItalic, bUnderline,0,0,0,0,0,0, Name);
}

/////////////////////////////////////////////////////////////////////////////
// CGUIDlg message handlers

void CGUIDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(m_LogoText.IsEmpty())
		return;

	CRect rectTabCtrl;
	GetTabControl()->GetWindowRect(rectTabCtrl);
	ScreenToClient(rectTabCtrl);

	CRect rectOk;
	GetDlgItem(IDOK)->GetWindowRect(rectOk);
	ScreenToClient(rectOk);

	dc.SetBkMode(TRANSPARENT);

	CRect rectText;
	rectText.left = rectTabCtrl.left;
	rectText.top = rectOk.top;
	rectText.bottom = rectOk.bottom;
	rectText.right = rectOk.left;

	CFont * OldFont = dc.SelectObject(&m_fontLogo);

	// draw text in DC
	COLORREF OldColor = dc.SetTextColor( ::GetSysColor( COLOR_3DHILIGHT));

	dc.DrawText( m_LogoText, rectText + CPoint(1,1), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	dc.SetTextColor( ::GetSysColor( COLOR_3DSHADOW));
	dc.DrawText( m_LogoText, rectText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

	// restore old text color
	dc.SetTextColor( OldColor);
	// restore old font
	dc.SelectObject(OldFont);
	
	// Do not call CPropertySheet::OnPaint() for painting messages
}

BOOL CGUIDlg::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	GetDlgItem( IDOK )->ShowWindow( FALSE );
	GetDlgItem( IDCANCEL )->SetWindowText( "Quit" );
	//GetDlgItem( IDCANCEL )->SetWindowText( "Create" );
	GetDlgItem( ID_APPLY_NOW )->SetWindowText( "Listen" );
	GetDlgItem( IDHELP )->ShowWindow( FALSE );

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{

		// Remove the unwanted items of the system menu
		pSysMenu->EnableMenuItem(SC_MAXIMIZE, MF_GRAYED);
		pSysMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
		//pSysMenu->RemoveMenu(SC_RESTORE, MF_BYCOMMAND);

		CString strAboutMenu;
		//strAboutMenu.LoadString(IDS_ABOUTBOX);
		strAboutMenu.Format("&About Pipe Modeler...");
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Load the app icons
	SetIcon( AfxGetApp()->LoadIcon( IDR_MAINFRAME ), FALSE);
	SetIcon( AfxGetApp()->LoadIcon( IDR_MAINFRAME ), TRUE);

	// add the minimize button to the window
	::SetWindowLong( m_hWnd, GWL_STYLE, GetStyle() | WS_MINIMIZEBOX );

	// add the minimize command to the system menu
	GetSystemMenu( FALSE )->InsertMenu( -1, MF_BYPOSITION | MF_STRING,
							   SC_ICON, "Minimize" );

	// activate the new sysmenu
	DrawMenuBar();
	
	AutoArrangeButtons();

	m_imageTab.Create( IDB_TABIMAGES, 13, 1, RGB(255,255,255) );
	CTabCtrl *pTab = GetTabControl();
	pTab->SetImageList( &m_imageTab );
	TC_ITEM tcItem;
	tcItem.mask = TCIF_IMAGE;
	for( int i = 0; i < 7; i++ )
	{
		tcItem.iImage = i;
		pTab->SetItem( i, &tcItem );
	}
	
	SetLogoFont("Arial");
	m_fontEdit.CreateFont( -8, 0, 0, 0, 700, 0, 0, 0, 1, 
		0, 0, 0, 0, _T("MS Sans Serif") );
	GetTabControl()->SetFont( &m_fontEdit);

	//SetWindowText("PC-Based Flute Modeling"); // (LPCTSTR) m_pstrCaption
	SetWindowText("Pipe Modeler"); // (LPCTSTR) m_pstrCaption

	return bResult;
}

// Automaticaly arange visible controls below the tab control - Michael Brannan (1998/08/06) 
// http://www.codeguru.com/propertysheet/AutoArrangeControls.shtml

void CGUIDlg::AutoArrangeButtons()
{
	CWnd* pWnd = GetDlgItem(ID_APPLY_NOW);

	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		// Get the last control in the tab order - (tab order is the same as creation order)
		pWnd = pWnd->GetWindow(GW_HWNDLAST);

		// Get the tab control
		CTabCtrl* pTabCtrl = GetTabControl();

		// Get the child identifier of the tab control
		int nTabControlID = ::GetWindowLong(pTabCtrl->m_hWnd, GWL_ID);

		// Child control identifier
		int nControlID = 0;

		// The window rect of the tab control.
		CRect rcTAB(0, 0, 0, 0);

		pTabCtrl->GetWindowRect(rcTAB);

		ScreenToClient(rcTAB);

		CRect rcTemp(0, 0, 0, 0);

		GetClientRect(rcTemp);

		int nLeft = rcTemp.right;
		int nSpacing = rcTemp.right - rcTAB.right;

		// do this bit while we have a control to do something with
		while(pWnd)
		{
			// Get the ID of the current child control
			nControlID = ::GetWindowLong(pWnd->m_hWnd, GWL_ID);

			// Do not make changes to the tab control!!
			if (nControlID != nTabControlID)
			{
				// do some stuff
				pWnd->GetWindowRect(rcTemp);

				ScreenToClient(rcTemp);

				// Is the child control visible? - Don't use IsWindowVisible as the parent
				// also has to be visible for that to return TRUE;
				BOOL bChildIsVisible = ((pWnd->GetStyle() & WS_VISIBLE) == WS_VISIBLE);

				// Make sure we are below the TAB control
				if ((rcTemp.top > rcTAB.bottom) && bChildIsVisible)
				{
					// Move each control
					nLeft -= nSpacing + rcTemp.Width();

					pWnd->MoveWindow(nLeft, rcTemp.top, rcTemp.Width(), rcTemp.Height());
				}
			}

			// Go back in the TAB order again
			pWnd = pWnd->GetWindow(GW_HWNDPREV);
		}
	}
}

// Using Shortcut Keys for Property Pages - Zafir Anjum (1998/08/06)
// http://www.codeguru.com/propertysheet/shortcut_keys.shtml

BOOL CGUIDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
   if( pMsg->message == WM_SYSKEYDOWN && pMsg->wParam > 32 )
    {
            CTabCtrl *pTab = GetTabControl();
            int n = pTab->GetItemCount();

            TCHAR buf[80], shortcut[3];
            TC_ITEM tcItem;
            tcItem.mask = TCIF_TEXT;
            tcItem.pszText = buf;
            shortcut[0] = _T('&');
            shortcut[2] = _T('\0');
            for( int i = 0; i < n; i++ )
            {
                    tcItem.cchTextMax = 79;
                    pTab->GetItem( i, &tcItem );
                    shortcut[1] = (TCHAR) pMsg->wParam;
                    if( _tcsstr( buf, shortcut ) )
                    {
                            SetActivePage( i );
                            return TRUE;
                    }
            }
    }
	return CPropertySheet::PreTranslateMessage(pMsg);
}

void CGUIDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertySheet::OnSysCommand(nID, lParam);
	}
}
