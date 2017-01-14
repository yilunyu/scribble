// olorChange2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "ColorChange2Dlg.h"


// ColorChange2Dlg dialog

IMPLEMENT_DYNAMIC(ColorChange2Dlg, CDialog)

ColorChange2Dlg::ColorChange2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(ColorChange2Dlg::IDD, pParent)
{
    m_blue = 0;
    m_red = 0;
    m_green = 0;
    m_init = TRUE;
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
    DDX_Text(pDX, IDC_RED, m_red);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorChange2Dlg, CDialog)
    ON_WM_PAINT()
    //{{AFX_MSG_MAP(ColorChange2Dlg)
    ON_WM_LBUTTONUP()
    ON_WM_SETCURSOR()
    //}}AFX_MSG_MAP
   // ON_EN_CHANGE(IDC_BLUE, &ColorChange2Dlg::OnEnChangeEdit3)
    //ON_BN_CLICKED(IDC_BUTTON3, &ColorChange2Dlg::OnBnClickedButton3)
   // ON_BN_CLICKED(IDC_SETCOLOR, &ColorChange2Dlg::OnBnClickedSetcolor)
    ON_EN_CHANGE(IDC_GREEN, &ColorChange2Dlg::OnEnChangeGreen)
    ON_EN_CHANGE(IDC_RED, &ColorChange2Dlg::OnEnChangeRed)
    ON_EN_CHANGE(IDC_BLUE, &ColorChange2Dlg::OnEnChangeBlue)
    

    //ON_WM_LBUTTONDOWN()
    ON_BN_CLICKED(IDC_BUTTON1, &ColorChange2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ColorChange2Dlg message handlers

void ColorChange2Dlg::OnPaint()
{
    CClientDC dc(this); 
    CBrush bru;
    bru.CreateSolidBrush(RGB(m_red,m_green,m_blue));
    CBrush *pOldPen=dc.SelectObject(&bru);//选到一个设备描述表中
    dc.Rectangle(25,275,175,300);
    dc.SelectObject(pOldPen);   //释放

    BOOL flag = TRUE;
    if(m_init){
        if (test_bitmap.GetSafeHandle()) flag = FALSE;
        if(flag)
        {    int w = 255; 
            int h = 255;
            int *pix = new int[w*h];
            for (int i = 0; i < w; i++) 
            {
                for (int j = 0; j < h; j++)
                {
                    pix[i + j*w] = RGB(i, j, 0);
                }
            }

            test_bitmap.CreateBitmap(w, h, 1, 32, pix);
            delete[]pix;

            paint_bitmap(dc,200,50,&test_bitmap);
         }
    }
    int width = 25;
    int height = 255;
    int *pix2 = new int[width*height];
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            pix2[j+i*width] = RGB(m_blue,m_green,i);
        }
    }
    CBitmap variableMap;
    variableMap.CreateBitmap(width, height, 1, 32, pix2);
    delete[]pix2;

    paint_bitmap(dc,500,50,&variableMap);
    variableMap.DeleteObject();
    ///*CBitmap panel;
    //panel.CreateCompatibleBitmap(&dc,255,255);*/
   
    
    
   
    //CDC memDC;
    //memDC.CreateCompatibleDC(&dc);
    //CDIBSectionLite DIBsect;
    //DIBsect.SetBitmap(HBITMAP(panel));
    //CPen pen;
    //pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
    ///////*if( memDC.GetDeviceCaps(RASTERCAPS)!=RC_BITBLT){
    //////    return;
    //////}
    //////for(int i=0;i<255;i++)
    //////{
    //////    for(int j=0;j<255;j++)
    //////    {
    //////        COLORREF col = RGB(i,j,0);
    //////        if(memDC.SetPixel(CPoint(i,j),col)==-1)
    //////        {
    //////            return;
    //////        }
    //////    }
    //////}*/
    //dc.BitBlt(225,50,255,255,&memDC,0,0,SRCCOPY);
    //memDC.DeleteDC();
}



////void ColorChange2Dlg::OnBnClickedSetcolor()
////{
////    
////    ColorChange2Dlg::OnPaint();
////    // TODO: Add your control notification handler code here
////}
BOOL ColorChange2Dlg::OnSetCursor(CWnd* cwnd, UINT , UINT )
{
    POINT curs;
    GetCursorPos(&curs);
    cwnd->ScreenToClient(&curs);
    if(( 455>curs.x && curs.x>200 && 305>curs.y && curs.y>50 )||
        ( 525>curs.x && curs.x>500 && 305>curs.y && curs.y>50 ))
    {

        HCURSOR nCurs = LoadCursor(NULL,IDC_CROSS);
        SetCursor(nCurs);
    }
    else
    {
        HCURSOR nCurs = LoadCursor(NULL,IDC_ARROW);
        SetCursor(nCurs);
    }


    return TRUE;

}
void ColorChange2Dlg::OnEnChangeGreen()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
}

void ColorChange2Dlg::OnEnChangeRed()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);
}

void ColorChange2Dlg::OnEnChangeBlue()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    UpdateData(TRUE);

}
void ColorChange2Dlg::OnLButtonUp(UINT, CPoint upPoint)
{
    
    if( 455>upPoint.x && upPoint.x>200 && 305>upPoint.y && upPoint.y>50 )
    {
       m_blue = upPoint.x-200;
       m_green = upPoint.y-50;
    }
    else if( 525>upPoint.x && upPoint.x>500 && 305>upPoint.y && upPoint.y>50 )
    {
        m_red = upPoint.y-50;
    }
    CRect strip;
    strip.left = 500;
    strip.top= 50;
    strip.bottom = 305;
    strip.right = 755;
    InvalidateRect(&strip,FALSE);
}
void ColorChange2Dlg::OnBnClickedButton1()
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
    //ColorChange2Dlg::OnPaint();
}
void ColorChange2Dlg::paint_bitmap(CDC &dc,int clientx,int clienty,CBitmap* bmp)
{
    if (!bmp->GetSafeHandle()) return;
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);
    HBITMAP oldbitmap = (HBITMAP)memdc.SelectObject(bmp);
    if(oldbitmap==NULL) return;
    BITMAP bm;
    bmp->GetBitmap(&bm);

    dc.BitBlt(clientx, clienty, bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY);
    memdc.SelectObject(oldbitmap);
}
////void ColorChange2Dlg::OnLButtonDown()
////{
////    CClientDC dc(this);
////    COLORREF *pix = (COLORREF *)malloc(255*255*sizeof(COLORREF));
////    int x = 1;
////    if(pix!=NULL){
////        for(int i=0;i<255;i++)
////        {
////            for(int j=0;j<255;j++)
////            {
////                pix[i*255+j] = RGB(i,j,0);
////            }
////        }
////    }
////    CDC tempDC;
////    tempDC.CreateCompatibleDC(&dc);
////    HBITMAP dib = CreateBitmapFromPixels(tempDC.m_hDC,255,255,8*sizeof(COLORREF),(BYTE*)pix);
////    HBITMAP finalMap = DIBToDDB(dib,tempDC);
////    HBITMAP oldMap = (HBITMAP)tempDC.SelectObject(finalMap);
////    dc.BitBlt(201,50,255,255,&tempDC,0,0,SRCCOPY);
////    tempDC.SelectObject(oldMap);
////    tempDC.DeleteDC();
////}
//// HBITMAP ColorChange2Dlg::Create8bppBitmap(HDC hdc, int width, int height, LPVOID pBits)
////{
////    BITMAPINFO *bmi = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
////    BITMAPINFOHEADER &bih(bmi->bmiHeader);
////    bih.biSize = sizeof (BITMAPINFOHEADER);
////    bih.biWidth         = width;
////    bih.biHeight        = -height;
////    bih.biPlanes        = 1;
////    bih.biBitCount      = 8;
////    bih.biCompression   = BI_RGB;
////    bih.biSizeImage     = 0;
////    bih.biXPelsPerMeter = 14173;
////    bih.biYPelsPerMeter = 14173;
////    bih.biClrUsed       = 0;
////    bih.biClrImportant  = 0;
////    for (int I = 0; I <= 255; I++)
////    {
////        bmi->bmiColors[I].rgbBlue = bmi->bmiColors[I].rgbGreen = bmi->bmiColors[I].rgbRed = (BYTE)I;
////        bmi->bmiColors[I].rgbReserved = 0;
////    }
////
////    void *Pixels = NULL;
////    HBITMAP hbmp = CreateDIBSection(hdc, bmi, DIB_RGB_COLORS, &Pixels, NULL, 0);
////
////    if(pBits != NULL)
////    {
////        //fill the bitmap
////        BYTE* pbBits = (BYTE*)pBits;
////        BYTE *Pix = (BYTE *)Pixels;
////        memcpy(Pix, pbBits, width * height);
////    }
////
////    free(bmi);
////
////    return hbmp;
////}
////
////  HBITMAP ColorChange2Dlg::CreateBitmapFromPixels( HDC hDC,
////     UINT uWidth, UINT uHeight, UINT uBitsPerPixel, LPVOID pBits)
////{
////    if(uBitsPerPixel < 8) // NOT IMPLEMENTED YET
////        return NULL;
////
////    if(uBitsPerPixel == 8)
////        return Create8bppBitmap(hDC, uWidth, uHeight, pBits);
////
////    HBITMAP hBitmap = 0;
////    if ( !uWidth || !uHeight || !uBitsPerPixel )
////        return hBitmap;
////    LONG lBmpSize = uWidth * uHeight * (uBitsPerPixel/8) ;
////    BITMAPINFO bmpInfo = { 0 };
////    bmpInfo.bmiHeader.biBitCount = uBitsPerPixel;
////    bmpInfo.bmiHeader.biHeight = uHeight;
////    bmpInfo.bmiHeader.biWidth = uWidth;
////    bmpInfo.bmiHeader.biPlanes = 1;
////    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
////    if(bmpInfo.bmiHeader.biBitCount==32)  {
////        bmpInfo.bmiHeader.biCompression=BI_RGB;
////        //bmpInfo.bmiColors=NULL;
////    }
////        // Pointer to access the pixels of bitmap
////    UINT * pPixels = 0;
////    hBitmap = CreateDIBSection( hDC, (BITMAPINFO *)&
////        bmpInfo, DIB_RGB_COLORS, (void **)&
////        pPixels , NULL, 0);
////
////    if ( !hBitmap )
////        return hBitmap; // return if invalid bitmaps
////
////    //SetBitmapBits( hBitmap, lBmpSize, pBits);
////    // Directly Write
////    memcpy(pPixels, pBits, lBmpSize );
////   // LPBITMAPINFOHEADER lpbi; 
////    //*lpbi = *(LPBITMAPINFOHEADER)hBitmap; 
////    return hBitmap;
////}
////
////HBITMAP ColorChange2Dlg::DIBToDDB( HANDLE hDIB, CDC& dc ) 
////{ 
////    LPBITMAPINFOHEADER lpbi; 
////    HBITMAP hbm; 
////    CPalette pal; 
////    CPalette* pOldPal; 
////    //CClientDC dc(NULL); 
////    if (hDIB == NULL) 
////        return NULL; 
////    lpbi = (LPBITMAPINFOHEADER)hDIB; 
////    int nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 1 << lpbi->biBitCount; 
////    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ; 
////    LPVOID lpDIBBits; 
////    if( bmInfo.bmiHeader.biBitCount > 8 ) 
////        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + 
////        bmInfo.bmiHeader.biClrUsed) + 
////        ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0)); 
////    else 
////        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors); 
////    // Create and select a logical palette if needed 
////    if( nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE) 
////    { 
////        UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors); 
////        LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize]; 
////        pLP->palVersion = 0x300; 
////        pLP->palNumEntries = nColors; 
////        for( int i=0; i < nColors; i++) 
////        { 
////            pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed; 
////            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen; 
////            pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue; 
////            pLP->palPalEntry[i].peFlags = 0; 
////        } 
////        pal.CreatePalette( pLP ); 
////        delete[] pLP; 
////        // Select and realize the palette 
////        pOldPal = dc.SelectPalette( &pal, FALSE ); 
////        dc.RealizePalette(); 
////    } 
////    hbm = CreateDIBitmap(dc.GetSafeHdc(), // handle to device context 
////        (LPBITMAPINFOHEADER)lpbi, // pointer to bitmap info header 
////        (LONG)CBM_INIT, // initialization flag 
////        lpDIBBits, // pointer to initialization data 
////        (LPBITMAPINFO)lpbi, // pointer to bitmap info 
////        DIB_RGB_COLORS ); // color-data usage 
////    if (pal.GetSafeHandle()) 
////        dc.SelectPalette(pOldPal,FALSE); 
////    return hbm; 
////} 
////void ColorChange2Dlg::OnBnClickedButton1()
////{
////    // TODO: Add your control notification handler code here
////    CClientDC dc(this);
////    COLORREF *pix = (COLORREF *)malloc(255*255*sizeof(COLORREF));
////    //int x = 1;
////    if(pix!=NULL){
////        for(int i=0;i<255;i++)
////        {
////            for(int j=0;j<255;j++)
////            {
////                pix[i*255+j] = RGB(i,j,0);
////            }
////        }
////    }
////    CDC tempDC;
////    tempDC.CreateCompatibleDC(&dc);
////    HBITMAP dib = CreateBitmapFromPixels(tempDC.m_hDC,255,255,8*sizeof(COLORREF),(BYTE*)pix);
////    HBITMAP finalMap = DIBToDDB(dib,tempDC);
////    HBITMAP oldMap = (HBITMAP)tempDC.SelectObject(finalMap);
////    dc.BitBlt(201,50,255,255,&tempDC,0,0,SRCCOPY);
////    tempDC.SelectObject(oldMap);
////    tempDC.DeleteDC();
////}
