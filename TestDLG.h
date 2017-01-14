#pragma once


// TestDLG dialog

class TestDLG : public CDialog
{
	DECLARE_DYNAMIC(TestDLG)

public:
	TestDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestDLG();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
    CBitmap test_bitmap;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void paint_bitmap(CDC &dc);
    void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
};
