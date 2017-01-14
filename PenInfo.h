#pragma once


// CPenInfo dialog

class CPenInfo : public CDialog
{
	DECLARE_DYNAMIC(CPenInfo)

public:
	CPenInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenInfo();

// Dialog Data
	enum { IDD = IDD_PEN_WIDTHS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
