
// paintView.h: CpaintView 클래스의 인터페이스
//
#pragma once
#include "paintDoc.h"

class CpaintView : public CScrollView
{
	DECLARE_DYNCREATE(CpaintView)
private:
	//View의 깜빡임 방지를 위한 메모리DC와 메모리bitmap 객체
	CDC* _memDc;
	CBitmap* _bitmap, * _oldBitmap;
	CRect _rect;

	//현재 그려지는 GDIObject의 속성들
	CPen m_curPen;

	BOOL _bDrawMode;
	CPoint _anchor, _drawTo, _oldPoint;
	BOOL _bDoing;

	int _nZoomRate;
	int _oldRadius;		//원 그리기 이전 반지름

	int getOblique(CPoint& p1, CPoint& p2);
	void setStatusBar();

protected: // serialization에서만 만들어집니다.
	CpaintView();

// 특성입니다.
public:
	CpaintDoc *GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CpaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	virtual void OnInitialUpdate();

	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();

	afx_msg void OnFileNew();
	afx_msg void OnPencil();
	afx_msg void OnUpdatePencil(CCmdUI* pCmdUI);
	afx_msg void OnBeeLine();
	afx_msg void OnUpdateBeeLine(CCmdUI* pCmdUI);
	afx_msg void OnEllipse();
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnRectangle();
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnViewZoomdefault();

	afx_msg void OnDestroy();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

public:
	//afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};



#ifndef _DEBUG  // paintView.cpp의 디버그 버전
inline CpaintDoc* CpaintView::GetDocument() const
   { return reinterpret_cast<CpaintDoc*>(m_pDocument); }
#endif

