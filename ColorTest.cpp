// ColorTest.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "ColorTest.h"



// CColorTest dialog

IMPLEMENT_DYNAMIC(CColorTest, CDialog)


CColorTest::~CColorTest()
{
}

void CColorTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCPCBTESTDlg)
    DDX_Control(pDX, IDC_COLORCONTROL, colorControl);
    //}}AFX_DATA_MAP
}
 
// CColorTest message handlers
BEGIN_MESSAGE_MAP(CColorTest, CDialog)
    //{{AFX_MSG_MAP(CCPCBTESTDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
   // ON_COMMAND(ID_COLOR_CHANGECOLOR, &CColorTest::OnChangecolor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCPCBTESTDlg message handlers


//////CColorTest::CColorTest(CWnd* pParent /*=NULL*/)
//////: CDialog(CColorTest::IDD, pParent)
//////{
//////    //{{AFX_DATA_INIT(CCPCBTESTDlg)
//////    // NOTE: the ClassWizard will add member initialization here
//////    //}}AFX_DATA_INIT
//////    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//////    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//////}

BOOL CColorTest::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    /////*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ////ASSERT(IDM_ABOUTBOX < 0xF000);

    ////CMenu* pSysMenu = GetSystemMenu(FALSE);
    ////if (pSysMenu != NULL)
    ////{
    ////    CString strAboutMenu;
    ////    strAboutMenu.LoadString(IDS_ABOUTBOX);
    ////    if (!strAboutMenu.IsEmpty())
    ////    {
    ////        pSysMenu->AppendMenu(MF_SEPARATOR);
    ////        pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    ////    }
    ////}*/

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    colorControl.InitializeDefaultColors();

    srand( time( NULL ) + clock() );

    colorControl.SetCurSel( rand() % 139 );

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorTest::OnSysCommand(UINT nID, LPARAM lParam)
{
   /////* if ((nID & 0xFFF0) == IDM_ABOUTBOX)
   //// {
   ////     CAboutDlg dlgAbout;
   ////     dlgAbout.DoModal();
   //// }
   //// else
   //// {
   ////    
   //// }*/ 
   CDialog::OnSysCommand(nID, lParam);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorTest::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

CColorTest::CColorTest( CWnd* pParent /*= NULL*/ )
{

}

