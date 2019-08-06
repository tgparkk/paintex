#pragma once
#include "DrawObject.h"
#include <afxtempl.h>
#include <atltypes.h>
#include <afxwin.h>
class CRectangleDraw : public CDrawObject
{
private:
	CPoint m_topLeft, m_bottomRight;
	FIGURETYPE m_type;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;

public:
	CRectangleDraw();
	virtual ~CRectangleDraw();
	void draw(CDC* pDc);
	int drawType();
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);
};
