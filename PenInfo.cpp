// PenInfo.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "PenInfo.h"


// CPenInfo dialog

IMPLEMENT_DYNAMIC(CPenInfo, CDialog)

CPenInfo::CPenInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CPenInfo::IDD, pParent)
{

}

CPenInfo::~CPenInfo()
{
}

void CPenInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenInfo, CDialog)
END_MESSAGE_MAP()


// CPenInfo message handlers
