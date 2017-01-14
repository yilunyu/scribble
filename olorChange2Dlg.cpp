// olorChange2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "olorChange2Dlg.h"
#include "ColorChange2Dlg.h"


// ColorChange2Dlg dialog

IMPLEMENT_DYNAMIC(ColorChange2Dlg, CDialog)

ColorChange2Dlg::ColorChange2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(ColorChange2Dlg::IDD, pParent)
{

}

ColorChange2Dlg::~ColorChange2Dlg()
{
}

void ColorChange2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPenWidthsDlg)
    DDX_Text(pDX, IDC_BLUE, m_blue);
    DDX_Text(pDX, IDC_GREEN, m_green);
    DDX_Text(pDX, IDC_RED, m_green);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorChange2Dlg, CDialog)
    ON_EN_CHANGE(IDC_EDIT3, &ColorChange2Dlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// ColorChange2Dlg message handlers

void ColorChange2Dlg::OnEnChangeEdit3()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}
