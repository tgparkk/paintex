#include "pch.h"
#include "RectangleDraw.h"
CRectangleDraw::CRectangleDraw() {}

CRectangleDraw::~CRectangleDraw() {}

void CRectangleDraw::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_Thickness, m_lineColor);

	CPen* oldPen = pDc->SelectObject(&pen);
	CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

	pDc->Rectangle(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

	pDc->SelectObject(oldBrush);
	pDc->SelectObject(oldPen);
}

int CRectangleDraw::drawType(void) {
	return RECTANGLE;
}

void CRectangleDraw::serialize(CArchive& ar) {
	int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight << m_type << m_Thickness << m_lineColor << m_fillColor;
}

void CRectangleDraw::deserialize(CArchive& ar) {
	int type;
	ar >> m_topLeft >> m_bottomRight >> type >> m_Thickness >> m_lineColor >> m_fillColor;
	m_type = (FIGURETYPE)type;
}

void CRectangleDraw::setRect(CPoint& topLeft, CPoint& bottomRight)
{
	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

void CRectangleDraw::setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}