#pragma once


// ColorChange2Dlg dialog

class ColorChange2Dlg : public CDialog
{
	DECLARE_DYNAMIC(ColorChange2Dlg)

public:
	ColorChange2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ColorChange2Dlg();

// Dialog Data
	enum { IDD = IDD_OLORCHANGE2DLG };
    int m_red;
    int m_green;
    int m_blue;
    CBitmap m_curColor;
    BOOL m_init;
protected:
    CBitmap test_bitmap;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void OnPaint();
    //HBITMAP DIBToDDB( HANDLE hDIB, CDC& dc ) ;
   //  HBITMAP CreateBitmapFromPixels( HDC hDC,
        //UINT uWidth, UINT uHeight, UINT uBitsPerPixel, LPVOID pBits);
     //HBITMAP Create8bppBitmap(HDC hdc, int width, int height, LPVOID pBits );
    void paint_bitmap(CDC &dc,int clientx,int clienty,CBitmap* bmp);
	DECLARE_MESSAGE_MAP()
public:
   // afx_msg void OnLButtonDown();
   // afx_msg void OnEnChangeEdit3();
 // afx_msg void OnBnClickedButton3();
 //   afx_msg void OnBnClickedSetcolor();
    afx_msg void OnEnChangeGreen();
    afx_msg void OnEnChangeRed();
    afx_msg void OnEnChangeBlue();
    afx_msg void OnBnClickedButton1();
    BOOL OnSetCursor(CWnd* cwnd, UINT , UINT );
    void OnLButtonUp(UINT, CPoint upPoint);
};
