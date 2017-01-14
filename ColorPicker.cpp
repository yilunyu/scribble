// ColorPicker.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "ColorPicker.h"


// CColorPicker dialog

IMPLEMENT_DYNAMIC(CColorPicker, CDialog)

CColorPicker::CColorPicker(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPicker::IDD, pParent)
{

}

CColorPicker::~CColorPicker()
{
}

void CColorPicker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColorPicker, CDialog)
END_MESSAGE_MAP()


// CColorPicker message handlers
