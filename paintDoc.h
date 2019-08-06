
// paintDoc.h: CpaintDoc 클래스의 인터페이스
//
#pragma once
#include "DrawObject.h"
#include "BeeLineDraw.h"
#include "PencilDraw.h"
#include "EllipseDraw.h"
#include "RectangleDraw.h"



class CpaintDoc : public CDocument
{

private:
	CPtrList m_DrawObjs;
	CDrawObject* m_DrawObj;

protected: // serialization에서만 만들어집니다.
	CpaintDoc();

// 특성입니다.
public:
	TOOLTYPE CurDrawType;	//현재 선택된 그리기 모드

	virtual ~CpaintDoc();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);   // 문서 입/출력을 위해 재정의되었습니다.

	CPtrList& getDrawObjects();

	CBeeLineDraw *getBeeLineDraw(bool bNew = FALSE);
	CPencilDraw *getPencilDraw(bool bNew = FALSE);
	CEllipseDraw *getEllipseDraw(bool bNew = FALSE);
	CRectangleDraw *getRectangleDraw(bool bNew = FALSE);

// 재정의입니다.
public:
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_DYNCREATE(CpaintDoc)
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
