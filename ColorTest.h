#pragma once
#include "ColorPickerCB.h"


// CColorTest dialog

class CColorTest : public CDialog
{
	DECLARE_DYNAMIC(CColorTest)

public:
	CColorTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorTest();

    
// Dialog Data
    //{{AFX_DATA(CCPCBTESTDlg)
	enum { IDD = IDD_DIALOG1 };
    CColorPickerCB	colorControl;
    //}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CCPCBTESTDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg HCURSOR OnQueryDragIcon();
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    //afx_msg void OnChangecolor();
};
