#include "pch.h"
#include "EllipseDraw.h"

CEllipseDraw::CEllipseDraw(void)
{
}

CEllipseDraw::~CEllipseDraw(void)
{
}

void CEllipseDraw::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_Thickness, m_lineColor);

	CPen* oldPen = pDc->SelectObject(&pen);
	CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

	pDc->Ellipse(m_topLeft.x, m_topLeft.y, m_bottomRight.x, m_bottomRight.y);

	pDc->SelectObject(oldBrush);
	pDc->SelectObject(oldPen);
}

int CEllipseDraw::drawType(void) {
	return ELLIPSE;
}

void CEllipseDraw::setRect(CPoint& topLeft, CPoint& bottomRight) {
	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

void CEllipseDraw::setCircle(CPoint& center, int radius)
{
	m_topLeft.x = center.x - radius;
	m_topLeft.y = center.y - radius;

	m_bottomRight.x = center.x + radius;
	m_bottomRight.y = center.y + radius;
}

void CEllipseDraw::setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = lineWidth;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}

void CEllipseDraw::serialize(CArchive& ar) {
	int type = m_type;
	ar << drawType();
	ar << m_topLeft << m_bottomRight << type << m_Thickness << m_lineColor << m_fillColor;
}

void CEllipseDraw::deserialize(CArchive& ar) {
	int type;

	ar >> m_topLeft >> m_bottomRight >> type >> m_Thickness >> m_lineColor >> m_fillColor;
	m_type = (FIGURETYPE)type;
}