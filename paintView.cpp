
// paintView.cpp: CpaintView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#endif

#include "paint.h"
#include "paintDoc.h"
#include "paintView.h"
#include "ToolValues.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpaintView

IMPLEMENT_DYNCREATE(CpaintView, CScrollView)

BEGIN_MESSAGE_MAP(CpaintView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

	ON_COMMAND(ID_FILE_NEW, &CpaintView::OnFileNew)
	ON_COMMAND(ID_VIEW_ZOOMIN, &CpaintView::OnZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &CpaintView::OnZoomOut)
	ON_COMMAND(ID_VIEW_ZOOMDEFAULT, &CpaintView::OnViewZoomdefault)

	ON_COMMAND(ID_PENCIL, &CpaintView::OnPencil)
	ON_COMMAND(ID_BEELINE, &CpaintView::OnBeeLine)
	ON_COMMAND(ID_ELLIPSE, &CpaintView::OnEllipse)
	ON_COMMAND(ID_RECTANGLE, &CpaintView::OnRectangle)


	ON_UPDATE_COMMAND_UI(ID_PENCIL, &CpaintView::OnUpdatePencil)
	ON_UPDATE_COMMAND_UI(ID_BEELINE, &CpaintView::OnUpdateBeeLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CpaintView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CpaintView::OnUpdateRectangle)

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_SETCURSOR()
	//ON_WM_SETFOCUS()
	//ON_WM_KILLFOCUS()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

// CpaintView 생성/소멸

CpaintView::CpaintView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	_bDrawMode = FALSE;
	_bDoing = FALSE;
	_nZoomRate = 100;
	_memDc = NULL;
	_bitmap = NULL;
	_oldRadius = 0;

	_rect.left = _rect.top = 0;
	_rect.bottom = 600;
	_rect.right = 800;
}

CpaintView::~CpaintView()
{
}

BOOL CpaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.x = _rect.top;
	cs.y = _rect.left;
	cs.cx = _rect.bottom;
	cs.cy = _rect.right;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return CWnd::PreCreateWindow(cs);
}

// CpaintView 그리기
//pencil
void CpaintView::OnPencil() {
	if (GetDocument()->CurDrawType == PENCIL) {
		GetDocument()->CurDrawType = DEFAULT;
	}
	else {
		GetDocument()->CurDrawType = PENCIL;
	}
	//setStatusBar();

	//AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}

void CpaintView::OnUpdatePencil(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == PENCIL);
}

void CpaintView::OnBeeLine() {
	if (GetDocument()->CurDrawType == BEELINE) {
		GetDocument()->CurDrawType = DEFAULT;
	}
	else {
		GetDocument()->CurDrawType = BEELINE;
	}
	//setStatusBar();

	//AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CpaintView::OnUpdateBeeLine(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == BEELINE);
}

void CpaintView::OnEllipse() {
	TRACE("OnEllipse");
	if (GetDocument()->CurDrawType == ELLIPSE) {
		GetDocument()->CurDrawType = DEFAULT;
	}
	else {
		GetDocument()->CurDrawType = ELLIPSE;
	}
	//setStatusBar();

	//AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CpaintView::OnUpdateEllipse(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == ELLIPSE);
}

void CpaintView::OnRectangle() {
	if (GetDocument()->CurDrawType == RECTANGLE) {
		GetDocument()->CurDrawType = DEFAULT;
	}
	else {
		GetDocument()->CurDrawType = RECTANGLE;
	}
	//setStatusBar();

	//AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CpaintView::OnUpdateRectangle(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == RECTANGLE);
}

void CpaintView::OnZoomIn() {
	_nZoomRate += 50;
	Invalidate(TRUE);
}

void CpaintView::OnViewZoomdefault() {
	TRACE("OnViewZoomdefault\n");
	_nZoomRate = 100;
	Invalidate(TRUE);
}

void CpaintView::OnZoomOut() {
	_nZoomRate -= 50;
	Invalidate(TRUE);
}

void CpaintView::OnFileNew() {
	GetDocument()->OnNewDocument();
	Invalidate(TRUE);
}

// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
void CpaintView::OnInitialUpdate() {
	//	GetClientRect(_rect);
	_memDc = new CDC();
	_bitmap = new CBitmap();

	_memDc->CreateCompatibleDC(GetDC());
	_bitmap->CreateCompatibleBitmap(GetDC(), _rect.Width(), _rect.Height());

	_oldBitmap = _memDc->SelectObject(_bitmap);
}

void CpaintView::OnDestroy() {
	_bitmap->DeleteObject();
	_memDc->DeleteDC();

	CView::OnDestroy();
}


void CpaintView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {

	CView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(_nZoomRate, _nZoomRate);
	pDC->SetWindowExt(100, 100);

	CGdiObject* old = pDC->SelectStockObject(GRAY_BRUSH);
	CRect rect;
	pDC->GetClipBox(&rect);
	pDC->PatBlt(_rect.right, rect.top, rect.Width() - _rect.Width(), rect.Height(), PATCOPY);
	pDC->PatBlt(rect.left, _rect.bottom, _rect.Width(), rect.Height() - _rect.Height(), PATCOPY);
	pDC->SelectObject(old);
}


void CpaintView::OnDraw(CDC* pDc) {
	CRect rec, rect;
	GetClientRect(rec);

	//TRACE("OnDraw Rect(%d, %d, %d, %d)\n", rec.top, rec.left, rec.bottom, rec.right);

	pDc->GetClipBox(&rect);
	//TRACE("OnDraw ClipBox(%d, %d, %d, %d)\n", rect.top, rect.left, rect.bottom, rect.right);

	CpaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	_oldBitmap = _memDc->SelectObject(_bitmap);
	CGdiObject* old = _memDc->SelectStockObject(WHITE_BRUSH);
	CGdiObject* oldPen = _memDc->SelectStockObject(WHITE_PEN);
	_memDc->Rectangle(rec);
	_memDc->SelectObject(oldPen);

	CPtrList *list = &pDoc->getDrawObjects();

	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		((CDrawObject*)list->GetNext(pos))->draw(_memDc);
	}


	//	pDc->SetBkColor(RGB(255, 0, 0));

	pDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _memDc, 0, 0, SRCCOPY);

	_memDc->SelectObject(old);
	_memDc->SelectObject(_oldBitmap);
}

void CpaintView::OnLButtonDown(UINT nFlags, CPoint point) {
	TRACE("OnButtonDown : %d [%d, %d]\n", nFlags, point.x, point.y);
	_bDrawMode = TRUE;
	CpaintDoc* doc = GetDocument();

	CClientDC dc(this);

	SetCapture();

	switch (doc->CurDrawType) {
	case PENCIL:
		doc->getPencilDraw(TRUE)->addPoint(point);
		doc->getPencilDraw()->setPencil(ToolValues::LineWidth, ToolValues::FgColor);
		break;
	case BEELINE:
		doc->getBeeLineDraw(TRUE);
		doc->getBeeLineDraw()->setBeeLine(ToolValues::LineWidth, ToolValues::FgColor);
		break;
	case RECTANGLE:
		doc->getRectangleDraw(TRUE);
		doc->getRectangleDraw()->setProps(ToolValues::FigureType, ToolValues::LineWidth, ToolValues::FgColor, ToolValues::BgColor);
		break;
	case ELLIPSE:
		doc->getEllipseDraw(TRUE);
		doc->getEllipseDraw()->setProps(ToolValues::FigureType, ToolValues::LineWidth, ToolValues::FgColor, ToolValues::BgColor);
		break;

		TEXTMETRIC txtKey;
		dc.GetTextMetrics(&txtKey);
		CreateSolidCaret(1, txtKey.tmHeight);
		SetCaretPos(point);
		ShowCaret();

		break;
	}

	_anchor = _drawTo = _oldPoint = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CpaintView::OnMouseMove(UINT nFlags, CPoint point) {
	CString str;
	str.Format(_T("마우스 좌표 (%4d, %4d)"), point.x, point.y);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//pMainFrame->m_wndStatusBar.SetPaneText(2, str);

	if (_bDrawMode) {
		int oldMode;
		int radius;

		CpaintDoc* doc = GetDocument();
		CClientDC dc(this);

		CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
		CBrush cbrush(ToolValues::BgColor);
		CPen* oldPen = dc.SelectObject(&cpen);
		CBrush* oldBrush = dc.SelectObject(&cbrush);

		switch (doc->CurDrawType) {
		case PENCIL:
			dc.MoveTo(_anchor);
			dc.LineTo(point);
			_anchor = point;
			doc->getPencilDraw()->addPoint(point);
			break;

		case BEELINE:
			oldMode = dc.SetROP2(R2_NOT);

			dc.MoveTo(_anchor);
			dc.LineTo(_oldPoint);

			dc.MoveTo(_anchor);
			dc.LineTo(point);
			_oldPoint = point;

			dc.SetROP2(oldMode);
			break;

		case ELLIPSE:
			oldMode = dc.SetROP2(R2_NOT);
			dc.SelectStockObject(NULL_BRUSH);

			radius = getOblique(_anchor, point);
			dc.Ellipse(_anchor.x - _oldRadius, _anchor.y - _oldRadius, _anchor.x + _oldRadius, _anchor.y + _oldRadius);
			dc.Ellipse(_anchor.x - radius, _anchor.y - radius, _anchor.x + radius, _anchor.y + radius);

			dc.SetROP2(oldMode);
			_oldRadius = radius;
			break;

		case RECTANGLE:
			oldMode = dc.SetROP2(R2_NOT);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(_oldPoint.x, _oldPoint.y, _anchor.x, _anchor.y);
			dc.Rectangle(_anchor.x, _anchor.y, point.x, point.y);
			_oldPoint = point;
			dc.SetROP2(oldMode);
			break;

		}

		dc.SelectObject(oldPen);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CpaintView::OnLButtonUp(UINT nFlags, CPoint point) {
	TRACE("OnButtonUp : %d\n", nFlags);

	if (_bDrawMode) {
		_bDrawMode = FALSE;
		CpaintDoc* doc = GetDocument();
		ASSERT_VALID(doc);

		::ReleaseCapture();

		switch (doc->CurDrawType) {
		case BEELINE:
			doc->getBeeLineDraw()->setPoint(_anchor, point);
			break;
		case RECTANGLE:
			doc->getRectangleDraw()->setRect(_anchor, point);
			break;
		case ELLIPSE:
			doc->getEllipseDraw()->setCircle(_anchor, _oldRadius);
			_oldRadius = 0;
			break;
		}

		Invalidate(FALSE);
	}

	CWnd::OnLButtonUp(nFlags, point);
}

int CpaintView::getOblique(CPoint& p1, CPoint& p2)
{
	int x, y;

	x = abs(p1.x - p2.x);
	y = abs(p1.y - p2.y);

	return (int)sqrt((double)x * x + y * y);
}

void CpaintView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACE("OnVScroll(%d, %d)\n", nSBCode, nPos);

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CpaintView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TRACE("OnHScroll(%d, %d)\n", nSBCode, nPos);

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


// CpaintView 인쇄


void CpaintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CpaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CpaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CpaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpaintView 진단

#ifdef _DEBUG
void CpaintView::AssertValid() const
{
	CView::AssertValid();
}

void CpaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpaintDoc* CpaintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpaintDoc)));
	return (CpaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CpaintView 메시지 처리기
