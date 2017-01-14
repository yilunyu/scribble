// TestDLG.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "TestDLG.h"


// TestDLG dialog

IMPLEMENT_DYNAMIC(TestDLG, CDialog)

TestDLG::TestDLG(CWnd* pParent /*=NULL*/)
	: CDialog(TestDLG::IDD, pParent)
{

}

TestDLG::~TestDLG()
{
}

void TestDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestDLG, CDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &TestDLG::OnBnClickedButton1)
        ON_WM_PAINT()
END_MESSAGE_MAP()

void TestDLG::OnPaint()
{
    CDialog::OnPaint();
    CClientDC dc(this); 
    ////CBrush bru;
    ////bru.CreateSolidBrush(RGB(m_red,m_green,m_blue));
    ////CBrush *pOldPen=dc.SelectObject(&bru);//选到一个设备描述表中
    ////dc.Rectangle(200,30,250,150);
    ////dc.SelectObject(pOldPen);   //释放
    paint_bitmap(dc);
}

void TestDLG::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    if (test_bitmap.GetSafeHandle()) return;
    int w = 255; 
    int h = 255;
    int *pix = new int[w*h];
    for (int i = 0; i < w; i++) 
    {
        for (int j = 0; j < h; j++)
        {
            pix[i + j*w] = RGB(i, j, 0);
        }
    }

    CClientDC dc(this);
    test_bitmap.CreateBitmap(w, h, 1, 32, pix);
    delete[]pix;
    TestDLG::OnPaint();
}
void TestDLG::paint_bitmap(CDC &dc)
{
    if (!test_bitmap.GetSafeHandle()) return;
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);
    HBITMAP oldbitmap = (HBITMAP)memdc.SelectObject(test_bitmap);
    if(oldbitmap==NULL) return;
    BITMAP bm;
    test_bitmap.GetBitmap(&bm);

    dc.BitBlt(200, 50, bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY);
    memdc.SelectObject(oldbitmap);
}

// TestDLG message handlers
