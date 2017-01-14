// ScribVw.cpp : implementation of the CScribbleView class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "Scribble.h"

#include "ScribDoc.h"
#include "ScribVw.h"
#include "ColorTest.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CScrollView)

BEGIN_MESSAGE_MAP(CScribbleView, CScrollView)
	//{{AFX_MSG_MAP(CScribbleView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	////ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	////ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ////ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ////ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    //ON_COMMAND(ID_COLOR_CHANGECOLOR, OnChangeColor)
    ON_COMMAND(ID_FILE_SAVE,OnSave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleView construction/destruction

CScribbleView::CScribbleView()
{
	SetScrollSizes(MM_TEXT, CSize(0, 0));
}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing

void CScribbleView::OnDraw(CDC* pDC)
{
    
	CScribbleDoc* pDoc = GetDocument();
	if(pDoc->firstTime)
    {
        pDoc->firstTime = FALSE;
        initializeOnce();
    }
    else
    {
        //GetClientRect(&m_rect);
        int oldwidth = m_rect.Width();
        int oldheight = m_rect.Height();
        CClientDC dc(this);
        CDC tempDC;
        tempDC.CreateCompatibleDC(&dc);
        CBitmap tempMap;
        tempMap.CreateCompatibleBitmap(&m_memdc,oldwidth,oldheight);
        CBitmap *oldMap = (CBitmap*)tempDC.SelectObject(&tempMap);
        tempDC.BitBlt(0,0,oldwidth,oldheight,&m_memdc,0,0,SRCCOPY);
        
        GetClientRect(&m_rect);
        m_bitmap.DeleteObject();
        int z = m_bitmap.CreateCompatibleBitmap(&dc, m_rect.Width(), m_rect.Height());
        CBitmap *x = (CBitmap*)m_memdc.SelectObject(&m_bitmap);
        m_memdc.FillSolidRect(&m_rect,RGB(255,255,255));
        m_memdc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&tempDC,0,0,SRCCOPY);
        dc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
        tempDC.SelectObject(oldMap);
        tempDC.DeleteDC();
        tempMap.DeleteObject();

    }
 ////   ASSERT_VALID(pDoc);

	////// Get the invalidated rectangle of the view, or in the case
	////// of printing, the clipping region of the printer dc.
	////CRect rectClip;
	////CRect rectStroke;
	////pDC->GetClipBox(&rectClip);
	////pDC->LPtoDP(&rectClip);
	////rectClip.InflateRect(1, 1); // avoid rounding to nothing

	////// Note: CScrollView::OnPaint() will have already adjusted the
	////// viewport origin before calling OnDraw(), to reflect the
	////// currently scrolled position.

	////// The view delegates the drawing of individual strokes to
	////// CStroke::DrawStroke().
	////CTypedPtrList<CObList,CStroke*>& strokeList = pDoc->m_strokeList;
	////POSITION pos = strokeList.GetHeadPosition();
	////while (pos != NULL)
	////{
	////	CStroke* pStroke = strokeList.GetNext(pos);
	////	rectStroke = pStroke->GetBoundingRect();
	////	pDC->LPtoDP(&rectStroke);
	////	rectStroke.InflateRect(1, 1); // avoid rounding to nothing
	////	if (!rectStroke.IntersectRect(&rectStroke, &rectClip))
	////		continue;
	////	pStroke->DrawStroke(pDC);
	////}
}
void CScribbleView::initializeOnce()
{
    ASSERT(IsWindow(m_hWnd));
    GetClientRect(&m_rect);
    //create memdc
    int y = m_memdc.CreateCompatibleDC(0);
    //CBitmap bitmap;
    CClientDC dc(this);
    int z = m_bitmap.CreateCompatibleBitmap(&dc, m_rect.Width(), m_rect.Height());
    CBitmap *x = (CBitmap*)m_memdc.SelectObject(&m_bitmap);
    //initialize memdc background color
    m_memdc.FillSolidRect(&m_rect, RGB(255,255,255));
    //SaveFile(TEXT("C:\\Users\\kingsoft\\Desktop\\test.bmp"), (HBITMAP)(m_bitmap) ,m_memdc.m_hDC);
    //m_memdc.SelectObject(x);
}
/////////////////////////////////////////////////////////////////////////////
// CScribbleView printing

////BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
////{
////	pInfo->SetMaxPage(2);   // the document is two pages long:
////							// the first page is the title page
////							// the second is the drawing
////	BOOL bRet = DoPreparePrinting(pInfo);	// default preparation
////	pInfo->m_nNumPreviewPages = 2;  // Preview 2 pages at a time
////	// Set this value after calling DoPreparePrinting to override
////	// value read from .INI file
////	return bRet;
////}

////void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
////{
////	// TODO: add extra initialization before printing
////}
////
////void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
////{
////	// TODO: add cleanup after printing
////}

/////////////////////////////////////////////////////////////////////////////
// CScribbleView diagnostics

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleView message handlers

void CScribbleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
 ////   // Pressing the mouse button in the view window starts a new stroke

	////// CScrollView changes the viewport origin and mapping mode.
	////// It's necessary to convert the point from device coordinates
	////// to logical coordinates, such as are stored in the document.
	////CClientDC dc(this);
	////OnPrepareDC(&dc);
	////dc.DPtoLP(&point);

	////m_pStrokeCur = GetDocument()->NewStroke();
	////// Add first point to the new stroke
	////m_pStrokeCur->m_pointArray.Add(point);

	////SetCapture();       // Capture the mouse until button up.
	////m_ptPrev = point;   // Serves as the MoveTo() anchor point for the
	////					// LineTo() the next point, as the user drags the
	////					// mouse.

	////return;
    SetCapture();
    __super::OnLButtonDown(nFlags, point);
    m_point = point;
    m_memdc.MoveTo(point);
    CScribbleDoc* pDoc = GetDocument();
    if(pDoc->currDevice == MOUSE_SELECT &&
        pDoc->selectedRect.right>point.x && point.x>pDoc->selectedRect.left
        && pDoc->selectedRect.bottom>point.y && point.y>pDoc->selectedRect.top)
    {
        
        
        
            //pDoc->selectedRect.InflateRect(1,1);
            pDoc->movingSelectedRect = TRUE;
        
    }
    else if(!pDoc->printedRect){
        pDoc->printedRect = TRUE;
        pDoc->isRectSelected = FALSE;
        HBRUSH oBrush = (HBRUSH)m_memdc.SelectObject(GetStockObject(WHITE_BRUSH));
        HPEN oPen = (HPEN)m_memdc.SelectObject(GetStockObject(WHITE_PEN));
        m_memdc.Rectangle(&pDoc->whiteRect);
        int xshift = point.x-m_point.x;
        int yshift = point.y-m_point.y;
        CDC tDC2;
        tDC2.CreateCompatibleDC(&m_memdc);
        CBitmap* oldmap = (CBitmap*)tDC2.SelectObject(&(pDoc->selectedMap));
        m_memdc.BitBlt(pDoc->selectedRect.left+xshift,pDoc->selectedRect.top+yshift,pDoc->selectedRect.right-pDoc->selectedRect.left,
            pDoc->selectedRect.bottom-pDoc->selectedRect.top,&tDC2,0,0,SRCCOPY);
        tDC2.SelectObject(oldmap);
        tDC2.DeleteDC();
        m_memdc.SelectObject(oBrush);
        m_memdc.SelectObject(oPen);
    }
}
void CScribbleView:: SetRectangle(CRect* r, int x1, int x2, int y1, int y2)
{
    r->left = min(x1,x2);
    r->right = max(x1,x2);
    r->top = min(y1,y2);
    r->bottom = max(y1,y2);
}
void CScribbleView::OnLButtonUp(UINT, CPoint point) 
{
	// Mouse button up is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by dragging
	// the captured mouse.

	if (GetCapture() != this)
		return; // If this window (view) didn't capture the mouse,
				// then the user isn't drawing in this window.
    ReleaseCapture();
	////CScribbleDoc* pDoc = GetDocument();

	CClientDC dc(this);
    CScribbleDoc *pDoc = GetDocument();
    if(pDoc->currDevice!=MOUSE_SELECT)
    {
        m_memdc.SelectObject(GetStockObject(NULL_BRUSH));
        m_memdc.SelectObject(pDoc->GetCurrentPen());
        if(pDoc->currDevice==RECTANGLE)
        {
            m_memdc.Rectangle(m_point.x,m_point.y,point.x,point.y);
        }
        if(pDoc->currDevice==CIRCLE)
        {
            m_memdc.Ellipse(m_point.x,m_point.y,point.x,point.y);
        }
        if(pDoc->currDevice == LINE)
        {
            m_memdc.LineTo(point);
        }
        dc.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
    }
    
    if(pDoc->currDevice == MOUSE_SELECT)
    {
        /*POINT curs;
        GetCursorPos(&curs);
        ScreenToClient(&curs);*/
        if(!pDoc->movingSelectedRect)
        {
            pDoc->printedRect = FALSE;
            CPen tempPen;
            tempPen.CreatePen(PS_DASH,1,RGB(0,0,0));
            dc.SelectObject(&tempPen);
            dc.SelectObject(GetStockObject(NULL_BRUSH));
            dc.Rectangle(m_point.x,m_point.y,point.x,point.y);
            //SetRectangle(&pDoc->selectedRect,point,m_point);
            SetRectangle(&(pDoc->selectedRect),point.x,m_point.x,point.y,m_point.y);
            SetRectangle(&(pDoc->whiteRect),point.x,m_point.x,point.y,m_point.y);
            pDoc->isRectSelected = TRUE; //change this thing somewhere
            //pDoc->releasedPos.x = point.x;
            //pDoc->releasedPos.y = point.y;
            CDC tDC;
            tDC.CreateCompatibleDC(&m_memdc);
            if(pDoc->selectedMap.m_hObject!=NULL)  
                pDoc->selectedMap.DeleteObject();
            pDoc->selectedMap.CreateCompatibleBitmap(&m_memdc,pDoc->selectedRect.Width(),
                pDoc->selectedRect.Height());
           // tDC.SelectObject()
            //tDC.SelectObject()
            CBitmap* oldMap = (CBitmap*)tDC.SelectObject(&(pDoc->selectedMap));
            tDC.BitBlt(0,0,pDoc->selectedRect.Width(),pDoc->selectedRect.Height(),
                &m_memdc,pDoc->selectedRect.left,pDoc->selectedRect.top,SRCCOPY);
            tDC.SelectObject(oldMap);
            tDC.DeleteDC();
            
        }
        else{
        /*    pDoc->selectedRect.left = point.x-pDoc->selectedRect.Width();
            pDoc->selectedRect.top = point.y-pDoc->selectedRect.Height();
            pDoc->selectedRect.bottom = point.y;
            pDoc->selectedRect.right = point.x;*/
            pDoc->printedRect = FALSE;
            int xshift = point.x-m_point.x;
            int yshift = point.y-m_point.y;
            SetRectangle(&(pDoc->selectedRect),pDoc->selectedRect.left+xshift,
                pDoc->selectedRect.right+xshift,pDoc->selectedRect.top+yshift,
                pDoc->selectedRect.bottom+yshift);
            pDoc->movingSelectedRect=FALSE;
        }
    }
    
	////// CScrollView changes the viewport origin and mapping mode.
	////// It's necessary to convert the point from device coordinates
	////// to logical coordinates, such as are stored in the document.
	////OnPrepareDC(&dc);  // set up mapping mode and viewport origin
	////dc.DPtoLP(&point);

	////CPen* pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
	////dc.MoveTo(m_ptPrev);
	////dc.LineTo(point);
	////dc.SelectObject(pOldPen);
	////m_pStrokeCur->m_pointArray.Add(point);

	////// Tell the stroke item that we're done adding points to it.
	////// This is so it can finish computing its bounding rectangle.
	////m_pStrokeCur->FinishStroke();

	////// Tell the other views that this stroke has been added
	////// so that they can invalidate this stroke's area in their
	////// client area.
	////pDoc->UpdateAllViews(this, 0L, m_pStrokeCur);

	////ReleaseCapture();   // Release the mouse capture established at
	////					// the beginning of the mouse drag.
	////pDoc->NotifyChanged();
	return;
}

void CScribbleView::OnMouseMove(UINT nFlags, CPoint point) 
{
	////// Mouse movement is interesting in the Scribble application
	////// only if the user is currently drawing a new stroke by dragging
	////// the captured mouse.

	////if (GetCapture() != this)
	////	return; // If this window (view) didn't capture the mouse,
	////			// then the user isn't drawing in this window.

	////CClientDC dc(this);
	////// CScrollView changes the viewport origin and mapping mode.
	////// It's necessary to convert the point from device coordinates
	////// to logical coordinates, such as are stored in the document.
	////OnPrepareDC(&dc);
	////dc.DPtoLP(&point);

	////m_pStrokeCur->m_pointArray.Add(point);

	////// Draw a line from the previous detected point in the mouse
	////// drag to the current point.
	////CPen* pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());
	////dc.MoveTo(m_ptPrev);
	////dc.LineTo(point);
	////dc.SelectObject(pOldPen);
	////m_ptPrev = point;
	////return;
     //if (GetCapture() != this) return;
    __super::OnMouseMove(nFlags, point);
    if (!(nFlags & MK_LBUTTON)) return;
    if (GetCapture() != this) return;
   /* m_point = point;
    m_memdc.LineTo(point);*/
    CScribbleDoc *pDoc = GetDocument();
    if(pDoc->currDevice == RECTANGLE)
    {
        CBitmap tMap;
        tMap.CreateCompatibleBitmap(&m_memdc,m_rect.Width(),m_rect.Height());
        CDC tDC;
        tDC.CreateCompatibleDC(&m_memdc);
        tDC.SelectObject(&tMap);
        tDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
        HBRUSH oldBrush = (HBRUSH)tDC.SelectObject(GetStockObject(NULL_BRUSH));
        tDC.SelectObject(pDoc->GetCurrentPen());
        tDC.Rectangle(m_point.x,m_point.y,point.x,point.y);
        CClientDC dc(this);
        dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &tDC, 0, 0, SRCCOPY);
        tDC.SelectObject(oldBrush);
        tMap.DeleteObject();
        tDC.DeleteDC();
    }
    else if(pDoc->currDevice== PENCIL)
    {
        __super::OnMouseMove(nFlags, point);
        if (!(nFlags & MK_LBUTTON)) return;
        m_point = point;
        m_memdc.SelectObject(pDoc->GetCurrentPen());
        m_memdc.LineTo(point);
        CClientDC dc(this);
        dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &m_memdc, 0, 0, SRCCOPY);
    }
    else if(pDoc->currDevice==ERASER)
    {
        __super::OnMouseMove(nFlags, point);
        if (!(nFlags & MK_LBUTTON)) return;
        m_point = point;
        CPen tempPen;
            tempPen.CreatePen(PS_SOLID, pDoc->m_nPenWidth, RGB(255,255,255));
         m_memdc.SelectObject(&tempPen);
        m_memdc.LineTo(point);
        CClientDC dc(this);
        dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &m_memdc, 0, 0, SRCCOPY);
    }
    else if(pDoc->currDevice == CIRCLE)
    {
        CBitmap tMap;
        tMap.CreateCompatibleBitmap(&m_memdc,m_rect.Width(),m_rect.Height());
        CDC tDC;
        tDC.CreateCompatibleDC(&m_memdc);
        tDC.SelectObject(&tMap);
        tDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
        HBRUSH oldBrush = (HBRUSH)tDC.SelectObject(GetStockObject(NULL_BRUSH));
        tDC.SelectObject(pDoc->GetCurrentPen());
        tDC.Ellipse(m_point.x,m_point.y,point.x,point.y);
        CClientDC dc(this);
        dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &tDC, 0, 0, SRCCOPY);
        tDC.SelectObject(oldBrush);
        tMap.DeleteObject();
        tDC.DeleteDC();
    }
    else if(pDoc->currDevice == LINE)
    {
        CBitmap tMap;
        tMap.CreateCompatibleBitmap(&m_memdc,m_rect.Width(),m_rect.Height());
        CDC tDC;
        tDC.CreateCompatibleDC(&m_memdc);
        tDC.SelectObject(&tMap);
        tDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
        //HBRUSH oldBrush = (HBRUSH)tDC.SelectObject(GetStockObject(NULL_BRUSH));
        //tDC.SelectObject(pDoc->GetCurrentPen());
        tDC.SelectObject(pDoc->GetCurrentPen());
       // tDC.Ellipse(m_point.x,m_point.y,point.x,point.y);
        tDC.MoveTo(m_point);
        tDC.LineTo(point);
        CClientDC dc(this);
        dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &tDC, 0, 0, SRCCOPY);
        //tDC.SelectObject(oldBrush);
        tMap.DeleteObject();
        tDC.DeleteDC();
    }
    else if(pDoc->currDevice == MOUSE_SELECT)
    {
        if(!(pDoc->movingSelectedRect))
        {
            CBitmap tMap;
            tMap.CreateCompatibleBitmap(&m_memdc,m_rect.Width(),m_rect.Height());
            CDC tDC;
            tDC.CreateCompatibleDC(&m_memdc);
            tDC.SelectObject(&tMap);
            tDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
            HBRUSH oldBrush = (HBRUSH)tDC.SelectObject(GetStockObject(NULL_BRUSH));
            CPen tempPen;
            tempPen.CreatePen(PS_DASH,1,RGB(0,0,0));
            tDC.SelectObject(&tempPen);
            tDC.Rectangle(m_point.x,m_point.y,point.x,point.y);
            CClientDC dc(this);
            dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &tDC, 0, 0, SRCCOPY);
            tDC.SelectObject(oldBrush);
            tMap.DeleteObject();
            tDC.DeleteDC();
        }
        else
        {
            CBitmap tMap;
            tMap.CreateCompatibleBitmap(&m_memdc,m_rect.Width(),m_rect.Height());
            CDC tDC;
            tDC.CreateCompatibleDC(&m_memdc);
            tDC.SelectObject(&tMap);
            tDC.BitBlt(0,0,m_rect.Width(),m_rect.Height(),&m_memdc,0,0,SRCCOPY);
            HBRUSH oldBrush = (HBRUSH)tDC.SelectObject(GetStockObject(WHITE_BRUSH));
            HPEN oldPen = (HPEN)tDC.SelectObject(GetStockObject(WHITE_PEN));
            //CRect tRect;
            //SetRectangle(&tRect,pDoc->selectedRect.left,pDoc->selectedRect.right,pDoc->selectedRect.bottom,pDoc->selectedRect.top);
            tDC.Rectangle(&(pDoc->whiteRect));
            int xshift = point.x-m_point.x;
            int yshift = point.y-m_point.y;
            CDC tDC2;
            tDC2.CreateCompatibleDC(&tDC);
            CBitmap* oldmap = (CBitmap*)tDC2.SelectObject(&(pDoc->selectedMap));
            tDC.BitBlt(pDoc->selectedRect.left+xshift,pDoc->selectedRect.top+yshift,pDoc->selectedRect.right-pDoc->selectedRect.left,
                pDoc->selectedRect.bottom-pDoc->selectedRect.top,&tDC2,0,0,SRCCOPY);
            CClientDC dc(this);
            dc.BitBlt(0, 0, m_rect.Width(), m_rect.Height(), &tDC, 0, 0, SRCCOPY);
            tDC.SelectObject(oldBrush);
            tDC2.SelectObject(oldmap);
            tDC2.DeleteDC();
            tDC.SelectObject(oldPen);
            tMap.DeleteObject();
            
            tDC.DeleteDC();
        }
    }
}
BOOL CScribbleView::OnSetCursor(CWnd* cwnd, UINT , UINT )
{
    CScribbleDoc* pDoc=GetDocument();
    if(pDoc->isRectSelected) {
        POINT curs;
        GetCursorPos(&curs);
        cwnd->ScreenToClient(&curs);
        if(pDoc->selectedRect.right>curs.x&&curs.x>pDoc->selectedRect.left
            &&pDoc->selectedRect.bottom>curs.y&&curs.y>pDoc->selectedRect.top)
        {
            
            HCURSOR nCurs = LoadCursor(NULL,IDC_SIZEALL);
            SetCursor(nCurs);
        }
        else
        {
            HCURSOR nCurs = LoadCursor(NULL,IDC_ARROW);
            SetCursor(nCurs);
        }
    }
    else
    {
        
        HCURSOR nCurs = LoadCursor(NULL,IDC_ARROW);
        SetCursor(nCurs);
    }
    return TRUE;
    
}
void CScribbleView::OnUpdate(CView* /* pSender */, LPARAM /* lHint */, 
	CObject* pHint) 
{
	// The document has informed this view that some data has changed.

	////if (pHint != NULL)
	////{
	////	if (pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
	////	{
	////		// The hint is that a stroke as been added (or changed).
	////		// So, invalidate its rectangle.
	////		CStroke* pStroke = (CStroke*)pHint;
	////		CClientDC dc(this);
	////		OnPrepareDC(&dc);
	////		CRect rectInvalid = pStroke->GetBoundingRect();
	////		dc.LPtoDP(&rectInvalid);
	////		InvalidateRect(&rectInvalid);
	////		return;
	////	}
	////}
	// We can't interpret the hint, so assume that anything might
	// have been updated.
	Invalidate(TRUE);
	return;
}

void CScribbleView::OnInitialUpdate() 
{
        ResyncScrollSizes();
	CScrollView::OnInitialUpdate();
}

void CScribbleView::ResyncScrollSizes()
{
	CClientDC dc(NULL);
	OnPrepareDC(&dc);
	CSize sizeDoc = GetDocument()->GetDocSize();
	dc.LPtoDP(&sizeDoc);
	SetScrollSizes(MM_TEXT, sizeDoc);
}

////void CScribbleView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
////{
////	if (pInfo->m_nCurPage == 1)  // page no. 1 is the title page
////	{
////		PrintTitlePage(pDC, pInfo);
////		return; // nothing else to print on page 1 but the page title
////	}
////	CString strHeader = GetDocument()->GetTitle();
////
////	PrintPageHeader(pDC, pInfo, strHeader);
////	// PrintPageHeader() subtracts out from the pInfo->m_rectDraw the
////	// amount of the page used for the header.
////
////	pDC->SetWindowOrg(pInfo->m_rectDraw.left,-pInfo->m_rectDraw.top);
////
////	// Now print the rest of the page
////	OnDraw(pDC);
////}

////void CScribbleView::PrintTitlePage(CDC* pDC, CPrintInfo* pInfo)
////{
////	// Prepare a font size for displaying the file name
////	LOGFONT logFont;
////	memset(&logFont, 0, sizeof(LOGFONT));
////	logFont.lfHeight = 75;  //  3/4th inch high in MM_LOENGLISH
////							// (1/100th inch)
////	CFont font;
////	CFont* pOldFont = NULL;
////	if (font.CreateFontIndirect(&logFont))
////		pOldFont = pDC->SelectObject(&font);
////
////	// Get the file name, to be displayed on title page
////	CString strPageTitle = GetDocument()->GetTitle();
////
////	// Display the file name 1 inch below top of the page,
////	// centered horizontally
////	pDC->SetTextAlign(TA_CENTER);
////	pDC->TextOut(pInfo->m_rectDraw.right/2, -100, strPageTitle);
////
////	if (pOldFont != NULL)
////		pDC->SelectObject(pOldFont);
////}

////void CScribbleView::PrintPageHeader(CDC* pDC, CPrintInfo* pInfo,
////	CString& strHeader)
////{
////	// Print a page header consisting of the name of
////	// the document and a horizontal line
////	pDC->SetTextAlign(TA_LEFT);
////	pDC->TextOut(0,-25, strHeader);  // 1/4 inch down
////
////	// Draw a line across the page, below the header
////	TEXTMETRIC textMetric;
////	pDC->GetTextMetrics(&textMetric);
////	int y = -35 - textMetric.tmHeight;          // line 1/10th inch below text
////	pDC->MoveTo(0, y);                          // from left margin
////	pDC->LineTo(pInfo->m_rectDraw.right, y);    // to right margin
////
////	// Subtract out from the drawing rectange the space used by the header.
////	y -= 25;    // space 1/4 inch below (top of) line
////	pInfo->m_rectDraw.top += y;
////}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
////void CScribbleView::OnCancelEditSrvr() 
////{
////	GetDocument()->OnDeactivateUI(FALSE);
////}

void CScribbleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
    CScribbleDoc* pDoc = GetDocument();
    CScrollView::OnPrepareDC(pDC, pInfo);

    pDC->SetMapMode(MM_ANISOTROPIC);
    CSize sizeDoc = pDoc->GetDocSize();
    sizeDoc.cy = -sizeDoc.cy;
    pDC->SetWindowExt(sizeDoc);

    CSize sizeNum, sizeDenom;
    pDoc->GetZoomFactor(&sizeNum, &sizeDenom);

    int xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
    int yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);

    long xExt = (long)sizeDoc.cx * xLogPixPerInch * sizeNum.cx;
    xExt /= 100 * (long)sizeDenom.cx;
    long yExt = (long)sizeDoc.cy * yLogPixPerInch * sizeNum.cy;
    yExt /= 100 * (long)sizeDenom.cy;
    pDC->SetViewportExt((int)xExt, (int)-yExt);
}

void CScribbleView::OnSize(UINT nType, int cx, int cy) 
{
    ResyncScrollSizes();        // ensure that scroll info is up-to-date
    CScrollView::OnSize(nType, cx, cy);
}

void CScribbleView::OnSave()
{
    ////CClientDC dc(this);
    ////CBitmap dummyMap;/*
    ////CDC* cdc = GetDC();*/
    ////dummyMap.CreateCompatibleBitmap(cdc,m_rect.Width(),m_rect.Height());
    ////CBitmap *embeddedMap = (CBitmap*)cdc->SelectObject(&dummyMap);

    //::GetClientRect(DeskWnd,&DeskRC);//获取窗口大小
    //HDC DeskDC=GetDC(DeskWnd);//获取窗口DC
    //HBITMAP DeskBmp=::CreateCompatibleBitmap(DeskDC,DeskRC.right,DeskRC.bottom);//兼容位图
    //HDC memDC=::CreateCompatibleDC(DeskDC);//兼容DC
    //SelectObject(memDC,DeskBmp);//把兼容位图选入兼容DC中
    //BitBlt(memDC,0,0,DeskRC.right,DeskRC.bottom,DeskDC,0,0,SRCCOPY);//拷贝DC

    SaveFile(TEXT("C:\\Users\\kingsoft\\Desktop\\test.bmp"), (HBITMAP)(m_bitmap) ,m_memdc);
    //int res = Save(m_memdc.m_hDC,(HBITMAP)(*embeddedMap),"C:\\Users\\kingsoft\\Desktop\\test.bmp");
    ////m_memdc.SelectObject(embeddedMap);
    ////dummyMap.DeleteObject();
}
//BOOL CScribbleView::Save(HDC hDC,HBITMAP hBitmap,char* szPath)
//{
//    DWORD error;
//    FILE * fp= NULL;
//    fp = fopen(szPath,"wb");
//    if(fp == NULL)
//    {
//        OutputDebugString((LPCSTR)L"Error Unable to Create File ");
//        return false;
//    }
//    BITMAP Bm;
//    BITMAPINFO BitInfo;
//    ZeroMemory(&BitInfo, sizeof(BITMAPINFO));
//    BitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    BitInfo.bmiHeader.biBitCount = 0;
//
//    if(!::GetDIBits(hDC, hBitmap, 0, 0, NULL, &BitInfo, DIB_RGB_COLORS))
//    {
//        OutputDebugString((LPCSTR)L"Error GetDIBits Fail");
//        return (false);
//    }
//    Bm.bmHeight = BitInfo.bmiHeader.biHeight;
//    Bm.bmWidth  = BitInfo.bmiHeader.biWidth;
//
//    BITMAPFILEHEADER    BmHdr;
//
//    BmHdr.bfType        = 0x4d42;   // 'BM' WINDOWS_BITMAP_SIGNATURE
//    BmHdr.bfSize        = (((3 * Bm.bmWidth + 3) & ~3) * Bm.bmHeight) 
//        + sizeof(BITMAPFILEHEADER) 
//        + sizeof(BITMAPINFOHEADER);
//    BmHdr.bfReserved1    = BmHdr.bfReserved2 = 0;
//    BmHdr.bfOffBits      = (DWORD) sizeof(BITMAPFILEHEADER) 
//        + sizeof(BITMAPINFOHEADER);
//
//    BitInfo.bmiHeader.biCompression = 0;
//    // Writing Bitmap File Header ////
//    size_t size = fwrite(&BmHdr,sizeof(BITMAPFILEHEADER),1,fp);
//    if(size < 1)
//    {
//        OutputDebugString((LPCSTR)L"Error  Header Write");
//        error = GetLastError();
//    }
//    size = fwrite(&BitInfo.bmiHeader,sizeof(BITMAPINFOHEADER),1,fp);
//    if(size < 1)
//    {		
//        OutputDebugString((LPCSTR)L"Error  Write");
//        error = GetLastError();
//    }
//    BYTE *pData = new BYTE[BitInfo.bmiHeader.biSizeImage + 5];
//    if(!::GetDIBits(hDC, hBitmap, 0, Bm.bmHeight, 
//        pData, &BitInfo, DIB_RGB_COLORS))
//        return (false);
//    if(pData != NULL)
//        fwrite(pData,1,BitInfo.bmiHeader.biSizeImage,fp);
//
//    fclose(fp);
//    delete (pData);
//
//    return (true);
//}

//void CScribbleView::OnChangeColor()
//{
//    return;
//}



BOOL CScribbleView::SaveFile(TCHAR szFilePath[1024], HBITMAP hBMP, HDC hdc)
{
    LPTSTR pszFile = szFilePath;
    BOOL bRet = FALSE;
    PBITMAPINFO pbiBitMapInfo = _CreateBitmapInfoStruct(hBMP);
    HANDLE hFile = NULL;
    BITMAPFILEHEADER hBitMapFile = {0};
    PBITMAPINFOHEADER pbihBitMap = {0};
    LPBYTE lpBits = NULL;
    DWORD dwTotal = 0;
    DWORD dwCB = 0;
    BYTE* pbyByte = NULL;
    DWORD dwTemp = 0; 

    //    pszFile = _T("MyPaint.bmp");
    pbihBitMap = (PBITMAPINFOHEADER) pbiBitMapInfo; 
    if(pbihBitMap == NULL)
    {
        goto EXIT0;
    }
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbihBitMap->biSizeImage);

    if (!lpBits) 
    {
        goto EXIT0;
    }

    if (!GetDIBits(hdc, hBMP, 0, (WORD) pbihBitMap->biHeight, lpBits, pbiBitMapInfo, 
        DIB_RGB_COLORS)) 
    {
        goto EXIT0;
    }

    hFile = CreateFile(pszFile, 
        GENERIC_READ | GENERIC_WRITE, 
        (DWORD) 0, 
        NULL, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        (HANDLE) NULL); 
    if (hFile == INVALID_HANDLE_VALUE)
    {
        goto EXIT0;
    } 
    hBitMapFile.bfType = 0x4d42; 

    hBitMapFile.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
        pbihBitMap->biSize + pbihBitMap->biClrUsed 
        * sizeof(RGBQUAD) + pbihBitMap->biSizeImage); 
    hBitMapFile.bfReserved1 = 0; 
    hBitMapFile.bfReserved2 = 0; 

    hBitMapFile.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
        pbihBitMap->biSize + pbihBitMap->biClrUsed 
        * sizeof (RGBQUAD); 

    if (!WriteFile(hFile, (LPVOID) &hBitMapFile, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTemp,  NULL)) 
    {
        goto EXIT0; 
    }

    if (!WriteFile(hFile, (LPVOID) pbihBitMap, sizeof(BITMAPINFOHEADER) 
        + pbihBitMap->biClrUsed * sizeof (RGBQUAD), 
        (LPDWORD) &dwTemp, ( NULL)))
    {
        goto EXIT0; 
    }

    dwTotal = dwCB = pbihBitMap->biSizeImage; 
    pbyByte = lpBits; 
    if (!WriteFile(hFile, (LPSTR) pbyByte, (int) dwCB, (LPDWORD) &dwTemp,NULL)) 
    {
        goto EXIT0; 
    }
    bRet = TRUE;

EXIT0:
    if(hFile != NULL)
    {
        CloseHandle(hFile);
    }
    if(lpBits != NULL)
    {
        GlobalFree((HGLOBAL)lpBits);
    }
    return bRet;
}

//创建一个BMP文件头对象
PBITMAPINFO CScribbleView::_CreateBitmapInfoStruct(HBITMAP m_hLastCompatibleBMP)
{
    BITMAP bmBmp = {0}; 
    PBITMAPINFO pbmiBitMapInfo = NULL; 
    WORD    wClrBits = 0; 

    if (!GetObject(m_hLastCompatibleBMP, sizeof(BITMAP), (LPSTR)&bmBmp)) 
    {
        goto EXIT0;
    }

    wClrBits = (WORD)(bmBmp.bmPlanes * bmBmp.bmBitsPixel); 
    if (wClrBits == 1) 
        wClrBits = 1; 
    else if (wClrBits <= 4) 
        wClrBits = 4; 
    else if (wClrBits <= 8) 
        wClrBits = 8; 
    else if (wClrBits <= 16) 
        wClrBits = 16; 
    else if (wClrBits <= 24) 
        wClrBits = 24; 
    else wClrBits = 32; 

    if (wClrBits != 24) 
    {
        pbmiBitMapInfo = (PBITMAPINFO) LocalAlloc(LPTR, 
            sizeof(BITMAPINFOHEADER) + 
            sizeof(RGBQUAD) * (1<< wClrBits)); 
    }
    else 
    {
        pbmiBitMapInfo = (PBITMAPINFO) LocalAlloc(LPTR, 
            sizeof(BITMAPINFOHEADER)); 
    }

    pbmiBitMapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmiBitMapInfo->bmiHeader.biWidth = bmBmp.bmWidth; 
    pbmiBitMapInfo->bmiHeader.biHeight = bmBmp.bmHeight; 
    pbmiBitMapInfo->bmiHeader.biPlanes = bmBmp.bmPlanes; 
    pbmiBitMapInfo->bmiHeader.biBitCount = bmBmp.bmBitsPixel; 
    if (wClrBits < 24) 
    {
        pbmiBitMapInfo->bmiHeader.biClrUsed = (1<<wClrBits); 
    }

    pbmiBitMapInfo->bmiHeader.biCompression = BI_RGB; 

    pbmiBitMapInfo->bmiHeader.biSizeImage = ((pbmiBitMapInfo->bmiHeader.biWidth * wClrBits +31) & ~31) /8
        * pbmiBitMapInfo->bmiHeader.biHeight; 
    pbmiBitMapInfo->bmiHeader.biClrImportant = 0; 
EXIT0:
    return pbmiBitMapInfo; 
}

void CScribbleView::CreatePalette()
{
    DIBSECTION ds;
    m_bitmap.GetObject(sizeof(DIBSECTION),&ds);

    //计算颜色数
    int nColors;
    if(ds.dsBmih.biClrUsed!=0)
    {
        nColors=ds.dsBmih.biClrUsed;
    }
    else
    {
        nColors=1<<ds.dsBmih.biBitCount;
    }        
    CClientDC dc(this);
    //创建调色板
    if(nColors>256)
        m_palette.CreateHalftonePalette(&dc);
    else
    {
        RGBQUAD *pRGB=new RGBQUAD[nColors];

        //得到位图颜色列表
        
        CDC memDC;
        memDC.CreateCompatibleDC(&dc);
        CBitmap *pOldBitmap=memDC.SelectObject(&m_bitmap);
        ::GetDIBColorTable((HDC)memDC,0,nColors,pRGB); //得到颜色列表
        memDC.SelectObject(pOldBitmap);

        //初始化逻辑调色板
        UINT nSize=sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY)*(nColors-1));
        LOGPALETTE *pLP=(LOGPALETTE*) new BYTE[nSize];
        pLP->palVersion=0x300;
        pLP->palNumEntries=nColors;
        for(int i=0;i<nColors;i++)
        {
            pLP->palPalEntry[i].peRed=pRGB[i].rgbRed;
            pLP->palPalEntry[i].peGreen=pRGB[i].rgbGreen;
            pLP->palPalEntry[i].peBlue=pRGB[i].rgbBlue;
            pLP->palPalEntry[i].peFlags=0;
        }

        //创建调色板
        m_palette.CreatePalette(pLP);
    }
}
//////HANDLE CScribbleView::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal ) 
//////{
//////    BITMAP          bm;
//////    BITMAPINFOHEADER    bi;
//////    LPBITMAPINFOHEADER  lpbi;
//////    DWORD           dwLen;
//////    HANDLE          hDIB;
//////    HANDLE          handle;
//////    HDC             hDC;
//////    HPALETTE        hPal;
//////    ASSERT( bitmap.GetSafeHandle() );
//////    // The function has no arg for bitfields
//////    if( dwCompression == BI_BITFIELDS )
//////        return NULL;
//////    // If a palette has not been supplied use defaul palette
//////    hPal = (HPALETTE) pPal->GetSafeHandle();
//////    if (hPal==NULL)
//////        hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
//////    // Get bitmap information
//////    bitmap.GetObject(sizeof(bm),(LPSTR)&bm);
//////    // Initialize the bitmapinfoheader
//////    bi.biSize       = sizeof(BITMAPINFOHEADER);
//////    bi.biWidth      = bm.bmWidth;
//////    bi.biHeight         = bm.bmHeight;
//////    bi.biPlanes         = 1;
//////    bi.biBitCount       = bm.bmPlanes * bm.bmBitsPixel;
//////    bi.biCompression    = dwCompression;
//////    bi.biSizeImage      = 0;
//////    bi.biXPelsPerMeter  = 0;
//////    bi.biYPelsPerMeter  = 0;
//////    bi.biClrUsed        = 0;
//////    bi.biClrImportant   = 0;
//////    // Compute the size of the  infoheader and the color table
//////    int nColors = (1 << bi.biBitCount);
//////    if( nColors > 256 ) 
//////        nColors = 0;
//////    dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);
//////    // We need a device context to get the DIB from
//////    hDC = GetDC(NULL);
//////    hPal = SelectPalette(hDC,hPal,FALSE);
//////    RealizePalette(hDC);
//////    // Allocate enough memory to hold bitmapinfoheader and color table
//////    hDIB = GlobalAlloc(GMEM_FIXED,dwLen);
//////    if (!hDIB){
//////        SelectPalette(hDC,hPal,FALSE);
//////        ReleaseDC(NULL,hDC);
//////        return NULL;
//////    }
//////    lpbi = (LPBITMAPINFOHEADER)hDIB;
//////    *lpbi = bi;
//////    // Call GetDIBits with a NULL lpBits param, so the device driver 
//////    // will calculate the biSizeImage field 
//////    GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
//////        (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);
//////    bi = *lpbi;
//////    // If the driver did not fill in the biSizeImage field, then compute it
//////    // Each scan line of the image is aligned on a DWORD (32bit) boundary
//////    if (bi.biSizeImage == 0){
//////        bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
//////            * bi.biHeight;
//////        // If a compression scheme is used the result may infact be larger
//////        // Increase the size to account for this.
//////        if (dwCompression != BI_RGB)
//////            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
//////    }
//////    // Realloc the buffer so that it can hold all the bits
//////    dwLen += bi.biSizeImage;
//////    if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
//////        hDIB = handle;
//////    else{
//////        GlobalFree(hDIB);
//////        // Reselect the original palette
//////        SelectPalette(hDC,hPal,FALSE);
//////        ReleaseDC(NULL,hDC);
//////        return NULL;
//////    }
//////    // Get the bitmap bits
//////    lpbi = (LPBITMAPINFOHEADER)hDIB;
//////    // FINALLY get the DIB
//////    BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
//////        0L,             // Start scan line
//////        (DWORD)bi.biHeight,     // # of scan lines
//////        (LPBYTE)lpbi            // address for bitmap bits
//////        + (bi.biSize + nColors * sizeof(RGBQUAD)),
//////        (LPBITMAPINFO)lpbi,     // address of bitmapinfo
//////        (DWORD)DIB_RGB_COLORS);     // Use RGB for color table
//////    if( !bGotBits )
//////    {
//////        GlobalFree(hDIB);
//////
//////        SelectPalette(hDC,hPal,FALSE);
//////        ReleaseDC(NULL,hDC);
//////        return NULL;
//////    }
//////    SelectPalette(hDC,hPal,FALSE);
//////    ReleaseDC(NULL,hDC);
//////    return hDIB;
//////}
//////
//////HBITMAP DIBToDDB( HANDLE hDIB ) 
//////{ 
//////    LPBITMAPINFOHEADER lpbi; 
//////    HBITMAP hbm; 
//////    CPalette pal; 
//////    CPalette* pOldPal; 
//////    CClientDC dc(NULL); 
//////    if (hDIB == NULL) 
//////        return NULL; 
//////    lpbi = (LPBITMAPINFOHEADER)hDIB; 
//////    int nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 
//////        1 << lpbi->biBitCount; 
//////    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ; 
//////    LPVOID lpDIBBits; 
//////    if( bmInfo.bmiHeader.biBitCount > 8 ) 
//////        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + 
//////        bmInfo.bmiHeader.biClrUsed) + 
//////        ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0)); 
//////    else 
//////        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors); 
//////    // Create and select a logical palette if needed 
//////    if( nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE) 
//////    { 
//////        UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors); 
//////        LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize]; 
//////        pLP->palVersion = 0x300; 
//////        pLP->palNumEntries = nColors; 
//////        for( int i=0; i < nColors; i++) 
//////        { 
//////            pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed; 
//////            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen; 
//////            pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue; 
//////            pLP->palPalEntry[i].peFlags = 0; 
//////        } 
//////        pal.CreatePalette( pLP ); 
//////        delete[] pLP; 
//////        // Select and realize the palette 
//////        pOldPal = dc.SelectPalette( &pal, FALSE ); 
//////        dc.RealizePalette(); 
//////    } 
//////    hbm = CreateDIBitmap(dc.GetSafeHdc(), // handle to device context 
//////        (LPBITMAPINFOHEADER)lpbi, // pointer to bitmap info header 
//////        (LONG)CBM_INIT, // initialization flag 
//////        lpDIBBits, // pointer to initialization data 
//////        (LPBITMAPINFO)lpbi, // pointer to bitmap info 
//////        DIB_RGB_COLORS ); // color-data usage 
//////    if (pal.GetSafeHandle()) 
//////        dc.SelectPalette(pOldPal,FALSE); 
//////    return hbm; 
//////} 