// ScribVw.h : interface of the CScribbleView class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
/////////////////////////////////////////////////////////////////////////////

class CScribbleView : public CScrollView
{
protected: // create from serialization only
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)

// Attributes
public:
	CScribbleDoc* GetDocument();
    CDC m_memdc;
    CBitmap m_bitmap;
    CRect m_rect;
    CPoint m_point;
    CPalette m_palette;
   // BOOL firstTime;

protected:
	CStroke*    m_pStrokeCur;   // the stroke in progress
	CPoint      m_ptPrev;       // the last mouse pt in the stroke in progress

// Operations
public:
        void ResyncScrollSizes();       // ensure scroll info is up-to-date
        void initializeOnce();
        void SetRectangle(CRect* r, int x1, int x2, int y1, int y2);
        BOOL Save(HDC hDC,HBITMAP hBitmap,char* szPath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScribbleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	////virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	////virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	////virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	////virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void PrintTitlePage(CDC* pDC, CPrintInfo* pInfo);
	void PrintPageHeader(CDC* pDC, CPrintInfo* pInfo, CString& strHeader);
    HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );
    void CreatePalette();
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScribbleView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnSize(UINT nType, int cx, int cy);
   // afx_msg void OnChangeColor();
    afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    BOOL SaveFile(TCHAR szFilePath[1024], HBITMAP hBMP,  HDC hdc);
    PBITMAPINFO _CreateBitmapInfoStruct(HBITMAP m_hLastCompatibleBMP);
};

#ifndef _DEBUG  // debug version in ScribVw.cpp
inline CScribbleDoc* CScribbleView::GetDocument()
   { return (CScribbleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
