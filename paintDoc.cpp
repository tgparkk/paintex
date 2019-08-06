
// paintDoc.cpp: CpaintDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "paint.h"
#endif

#include "paintDoc.h"

#include <propkey.h>
#include "BeeLineDraw.h"
#include "PencilDraw.h"
#include "EllipseDraw.h"
#include "RectangleDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CpaintDoc

IMPLEMENT_DYNCREATE(CpaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CpaintDoc, CDocument)
END_MESSAGE_MAP()


// CpaintDoc 생성/소멸

CpaintDoc::CpaintDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	CurDrawType = DEFAULT;
	m_DrawObj = NULL;

}

CpaintDoc::~CpaintDoc()
{
}

BOOL CpaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	CDrawObject* obj;
	POSITION pos = m_DrawObjs.GetHeadPosition();
	while (pos != NULL) {
		obj = (CDrawObject*)m_DrawObjs.GetNext(pos);
		delete obj;
	}
	m_DrawObjs.RemoveAll();

	return TRUE;
}




// CpaintDoc serialization

void CpaintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		POSITION pos = m_DrawObjs.GetHeadPosition();
		while (pos != NULL) {
			((CDrawObject*)m_DrawObjs.GetNext(pos))->serialize(ar);
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		int toolType;
		CDrawObject* obj=NULL;

		do {
			ar >> toolType;

			switch (toolType) {
			case BEELINE:
				obj = new CBeeLineDraw(); break;
			case PENCIL:
				obj = new CPencilDraw(); break;
			case ELLIPSE:
				obj = new CEllipseDraw(); break;
			case RECTANGLE:
				obj = new CRectangleDraw(); break;

			}

			obj->deserialize(ar);
			m_DrawObjs.AddTail(obj);

		} while (!ar.IsBufferEmpty());

		((CFrameWnd*)AfxGetMainWnd())->GetActiveView()->Invalidate(TRUE);
	}
}

CPtrList& CpaintDoc::getDrawObjects() {
	return m_DrawObjs;
}

CBeeLineDraw* CpaintDoc::getBeeLineDraw(bool bNew)
{
	if (bNew) {
		m_DrawObj = new CBeeLineDraw();
		m_DrawObjs.AddTail(m_DrawObj);

		return (CBeeLineDraw*)m_DrawObj;
	}
	if (m_DrawObj != NULL && m_DrawObj->drawType() == BEELINE) {
		return (CBeeLineDraw*)m_DrawObj;
	}
	return NULL;
}

CPencilDraw* CpaintDoc::getPencilDraw(bool bNew)
{
	if (bNew) {
		m_DrawObj = new CPencilDraw();
		m_DrawObjs.AddTail(m_DrawObj);

		return (CPencilDraw*)m_DrawObj;
	}
	if (m_DrawObj != NULL && m_DrawObj->drawType() == PENCIL) {
		return (CPencilDraw*)m_DrawObj;
	}
	return NULL;
}

CEllipseDraw* CpaintDoc::getEllipseDraw(bool bNew)
{
	if (bNew) {
		m_DrawObj = new CEllipseDraw();
		m_DrawObjs.AddTail(m_DrawObj);

		return (CEllipseDraw*)m_DrawObj;
	}
	if (m_DrawObj != NULL && m_DrawObj->drawType() == ELLIPSE) {
		return (CEllipseDraw*)m_DrawObj;
	}
	return NULL;
}

CRectangleDraw* CpaintDoc::getRectangleDraw(bool bNew)
{
	if (bNew) {
		m_DrawObj = new CRectangleDraw();
		m_DrawObjs.AddTail(m_DrawObj);

		return (CRectangleDraw*)m_DrawObj;
	}
	if (m_DrawObj != NULL && m_DrawObj->drawType() == RECTANGLE) {
		return (CRectangleDraw*)m_DrawObj;
	}
	return NULL;
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CpaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CpaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CpaintDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CpaintDoc 진단

#ifdef _DEBUG
void CpaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CpaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CpaintDoc 명령
